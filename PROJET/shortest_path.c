#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"
#include "shortest_path.h"
#include "omp.h"

extern int _largeur;

// Create mesh, initialise all values to 1
double* init_tab_mesh(){
	int i;
	int fin = _largeur*_largeur;
	double* tab = malloc(fin*sizeof(double));
	for(i=0; i<fin; i++)
		tab[i] = 1.;
	return tab;
}

// Create distance table, initialise to -1
double* init_tab_dist(){
	int i;
	int fin = _largeur*_largeur;
	double* tab = malloc(fin*sizeof(double));
	for(i=0; i<fin; i++)
		tab[i] = -1.;
	return tab;
}

// Create obstacle
void obstacle(double* mesh){
	int i;
	int demi = _largeur/2;
	for(i =0; i<demi+1; i++)
		mesh[demi + i*_largeur] = -1;
	for(i = demi+demi*_largeur ; i < demi*_largeur + _largeur-3 ; i++ ) {
	  mesh[i] = -1;
	}
} 

// Add neighbors to search priority queue
// Returns number of neighbors
// DOES NOT CHECK IF NEIGHBOR IS OPEN TO SEARCH(doesn't currently affect problem)
int find_voisin(pt current, pt* voisin, double* mesh){
	int y = current/_largeur;
	int x = current%_largeur;
	int i = 0;
	if(y != 0 && mesh[current-_largeur] != -1)	voisin[i++] = current-_largeur;
	if(x != 0 && mesh[current-1] != -1)	voisin[i++] = current-1;
	if(x != _largeur -1 && mesh[current+1] != -1) voisin[i++] = current+1;
	if(y != _largeur -1 && mesh[current+_largeur] != -1) voisin[i++] = current+_largeur;
	// Should probably set rest of array to 0, just to be safe
	int j;
	for ( j = i+1 ; j < 4 ; j++ ) { voisin[j] = 0; }
	return i;
}

// Create and fill/calculate distance table
double* tab_distance(double* mesh, pt depart, pt arrivee){
  int i,j;
	int fin = _largeur*_largeur;
	double* dist = init_tab_dist(); // Create initialised distance array
	dist[depart] = 0;
	int a_traiter = 0; // Positition in list[]

	pt current; // Current position within list[]
	pt voisin[4]; // Array containing list of neighbors
	int n_voisin; // Number of valid neighbors to check
	int iteration;
	int steps;
	int finished = 0;

	/* Initialize so it works without openmp */
	int rank = 0;
	int nproc = 1;
	nproc = omp_get_max_threads();

	int n_liste[nproc+1]; // Number of valid points in list[]

	pt** liste = malloc((nproc+1)*sizeof(pt*));
	int *next_steps = malloc((nproc+1)*sizeof(int)); // would int** be better use of first touch allocation??
	next_steps[nproc] = 1;
	for ( i = 0 ; i <= nproc ; i++ ) {
	  liste[i] = malloc(fin*sizeof(pt));
	  n_liste[i] = 0;
	}
	liste[nproc][n_liste[nproc]++] = depart;

	/** Sequential initialization ( until parallel is worthwhile ) **/
	for ( iteration = 1 ; iteration < 10 /*!finished && next_steps < nproc*/ ; iteration++ ) {
	  steps = next_steps[nproc];
	  next_steps[nproc] = 0;
	  printf("%d steps: dist = %d\n", steps, iteration);
	  for ( j = 0 ; j < steps ; j++ ) {
		current = liste[nproc][a_traiter++];
		n_voisin = find_voisin(current, voisin, mesh);
		for(i=0; i<n_voisin; i++)
			if(dist[voisin[i]] ==-1){
			  dist[voisin[i]] = iteration;
				liste[nproc][n_liste[nproc]++] = voisin[i];
				next_steps[nproc]++;
			}
	  } // end for: steps in iteration
	  if ( a_traiter > n_liste[nproc] ) { finished = 1; }
	  printf("Completed %d of %d\n", a_traiter, n_liste);
	} // end for: iterations

	/** Partition the frontier **/
	int split = next_steps[nproc];
	int a_old = a_traiter;
	int thread_max = nproc;

#pragma omp parallel							\
  default(none)								\
  shared(split,a_old,fin,mesh,dist,liste,next_steps,thread_max,n_liste)	\
  private(iteration,rank,a_traiter,current,voisin,n_voisin,		\
	  steps,i,j,finished,nproc)
	{
	rank = omp_get_thread_num();
	nproc = omp_get_num_threads();
	int start = rank*split/nproc;
	int end = (rank+1)*split/nproc;
	n_liste[rank] = next_steps[rank] = end - start;
	for ( i = 0 ; i < next_steps[rank] ; i++ )
	  liste[rank][i] = liste[thread_max][a_old+i+start];
	a_traiter = 0;
	printf("Rank %d of %d treating %d to %d\n", rank, nproc, start, end);

#pragma omp barrier

	for ( iteration ;  iteration < fin ; iteration++ ) {
	  steps = next_steps[rank];
	  next_steps[rank] = 0;
	  printf("%d steps: dist = %d\n", steps, iteration);
	  for ( j = 0 ; j < steps ; j++ ) {
		current = liste[rank][a_traiter++];
		n_voisin = find_voisin(current, voisin, mesh);
		for(i=0; i<n_voisin; i++)
			if(dist[voisin[i]] ==-1){
			  dist[voisin[i]] = iteration;
				liste[rank][n_liste[rank]++] = voisin[i];
				next_steps[rank]++;
			}
	  } // end for: steps in iteration
	  if ( a_traiter >= n_liste[rank] ) { finished = 1; }
	  printf("Completed %d of %d\n", a_traiter, n_liste[rank]);

	  /* BORDER CONTROL */
	  for ( j = n_liste[rank]-next_steps[rank] ; j < n_liste[rank] ; j++ ) {
	    for ( i = n_liste[(rank+1)%nproc] - next_steps[(rank+1)%nproc] ;
		  i < n_liste[(rank+1)%nproc] ; i++ ) {
	      if ( liste[rank][j] == liste[(rank+1)%nproc][i] ) {
		int k;
		for ( k = j ; k < n_liste[rank] ; k++ ) {
		  liste[rank][k] = liste[rank][k+1];
		}
		n_liste[rank]--; // removed element
		i = n_liste[(rank+1)%nproc]; // exit i-loop
	      } // end if: match
	    } // end for: elements of neighbor's next
	  } // end for: elements of next
	  /* END BORDER CONTROL */

	} // end for: iterations
	/* Check performance differences between barrier and 'update to min' */

	}

	free(liste);
	return dist;
}

//créé un tableau décrivant le plus court chemin à partir du tableau de distance à un point (de départ) et d'un point d'arrivée
pt* court_chemin(double* dist, pt arrivee){
	if(dist[arrivee] == -1)	//le point d'arrivee n'est pas accessible
		return NULL;
	int i = 0, j;
	pt current = arrivee;									//on part de la fin
	pt voisin[4];
	pt voisin_dist_mini;
	int n_voisin = 0;
	int dist_arrivee = dist[arrivee];
	pt* chemin = malloc((dist_arrivee)*sizeof(double));
	while(dist[current] != 0){								//tant que le point de départ n'est pas atteint
		n_voisin = find_voisin(current, voisin, dist);		//on cherche parmi les voisins celui qui a la distance minimum au point de départ
		voisin_dist_mini = voisin[0];
		for(j = 1; j<n_voisin; j++)
			if(dist[voisin_dist_mini]>dist[voisin[j]])
				voisin_dist_mini = voisin[j];
		chemin[i++] = voisin_dist_mini;						//on l'ajoute à la liste
		current = voisin_dist_mini;							//et on recommence à partir de celui là 
	}
	return chemin;
}

//créé un tableau décrivant le plus court chemin à partir du tableau de distance à un point (de départ) et d'un point d'arrivée
//la fonction bis decris un chemin chemin aussi court mais en faisant autant de changement de direction que possible.
//en le traçant et avec un maillage fin, il se raprochera visiellement plus du plus court chemin réel
pt* court_chemin_bis(double* dist, pt arrivee){
	if(dist[arrivee] == -1)	//le point d'arrivee n'est pas accessible
		return NULL;
	int i = 0, j;
	int dir = 0;
	pt current = arrivee;									//on part de la fin
	pt voisin[4];
	pt voisin_dist_mini;
	int n_voisin = 0;
	int dist_arrivee = dist[arrivee];
	pt* chemin = malloc((dist_arrivee)*sizeof(double));
	while(dist[current] != 0){								//tant que le point de départ n'est pas atteint
		n_voisin = find_voisin(current, voisin, dist);		//on cherche parmi les voisins celui qui a la distance minimum au point de départ
		if(dir++ == 0){										//la différence de la bis est d'alterner l'ordre de test des voisins
			voisin_dist_mini = voisin[0];
			for(j = 1; j<n_voisin; j++)
				if(dist[voisin_dist_mini]>dist[voisin[j]])
					voisin_dist_mini = voisin[j];
			}
		else{
			voisin_dist_mini = voisin[n_voisin-1];
			for(j = n_voisin-2; j>=0; j--)
				if(dist[voisin_dist_mini]>dist[voisin[j]])
					voisin_dist_mini = voisin[j];
			dir = 0;
			}
		chemin[i++] = voisin_dist_mini;						//on l'ajoute à la liste
		current = voisin_dist_mini;							//et on recommence à partir de celui là 
	}
	return chemin;
}


