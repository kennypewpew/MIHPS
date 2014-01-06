#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"

typedef int pt;		//point
int _largeur = 20;

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

// Add neighbors using A* algorithm
int A_find_voisin(pt current, pt* voisin, double* mesh, pt arrivee){
	int y = current/_largeur;
	int x = current%_largeur;
	int yy = arrivee/_largeur;
	int xx = arrivee%_largeur;
	int i = 0;
	// add valid neighbors (not edge && not obstacle)
	if(y != 0 && mesh[current-_largeur] != -1)	voisin[i++] = current-_largeur;
	if(x != 0 && mesh[current-1] != -1)	voisin[i++] = current-1;
	if(x != _largeur -1 && mesh[current+1] != -1) voisin[i++] = current+1;
	if(y != _largeur -1 && mesh[current+_largeur] != -1) voisin[i++] = current+_largeur;
	int j;
	for ( j = i ; j < 4 ; j++ ) { voisin[j] = 0; }/* ??+1 necessary??*/
	// calculate distance from each valid neighbor to endpoint
	int min_dist = (x-xx)*(x-xx) + (y-yy)*(y-yy);
	for ( j = 0 ; j < i ; j++ ) { 
	  if ( ( voisin[j]/_largeur - yy)*( voisin[j]/_largeur - yy) + ( voisin[j]%_largeur - xx)*( voisin[j]%_largeur - xx) < min_dist ) {
	    min_dist = (voisin[j]/_largeur - yy)*( voisin[j]/_largeur - yy) + ( voisin[j]%_largeur - xx)*( voisin[j]%_largeur - xx) ;
	  }
	}
	// invalidate neighbors which are not closer than current point
	for ( j = i ; j >= 0 ; j-- ) {
	  if ( ( voisin[j]/_largeur - yy)*( voisin[j]/_largeur - yy) + ( voisin[j]%_largeur - xx)*( voisin[j]%_largeur - xx) == min_dist ) {
	    int k;
	    for ( k = j ; k < 3 ; k++ ) {
	      voisin[k] = voisin[k+1]; // squash value to be removed
	    }
	    i--;
	  }
	}
	return i;
}

// Create and fill/calculate distance table
double* A_tab_distance(double* mesh, pt depart, pt arrivee){
        int i;
	int fin = _largeur*_largeur;
	double* dist = init_tab_dist(); // Create initialised distance array
	dist[depart] = 0;
	pt* liste = malloc(fin*sizeof(pt)); // Points in order to be checked
	int a_traiter = 0; // Positition in list[]
	int n_liste = 0; // Number of valid points in list[]
	pt current = depart; // Current position within list[]
	pt voisin[4]; // Array containing list of neighbors
	int n_voisin; // Number of valid neighbors to check
	while(a_traiter <= n_liste){ 
	  int diamond_size = 1;
	  n_voisin = A_find_voisin(current, voisin, mesh, arrivee);
	    if ( n_voisin != 0 ) {
		for(i=0; i<n_voisin; i++)
		        // If not obstacle && distance has not been checked yet,
		        // set neighbor's distance to current's + 1,
		        // add neighbors to search queue
			if(dist[voisin[i]] ==-1){
				dist[voisin[i]] = dist[current] + 1;
				liste[n_liste++] = voisin[i];
				/* NO DISTANCE COMPARISON CHECK */
			}
		current = liste[a_traiter++]; // Increment position in list[]
	    }
	    else{ /* add point near origin */ 
	      pt candidates[4*diamond_size][2];
	      int i_cand = 0;
	      int min_cand = _largeur*_largeur;
	      // right vertex -> bottom vertex
	      for ( i = 0 ; i < diamond_size ; i++ ) {
		int y = (current+i)/_largeur;
		int x = current%_largeur + (diamond_size - i);
		// if not obstacle && distance already set(point open to search)
		if ( mesh[x + _largeur * y] != -1 && dist[x + _largeur * y] != -1 ) {
		  candidates[i_cand][0] = (x-arrivee%_largeur)*(x-arrivee%_largeur) + (y-arrivee/_largeur)*(y-arrivee/_largeur);
		  candidates[i_cand][1] = x + y*_largeur;
		  if ( candidates[i_cand][0] < min_cand ) {
		    min_cand = candidates[i_cand][0];
		  }
		  i_cand++;
		} // end if: point is valid
	      } // end if: top right edge of diamond
	      /* ...other edges... */
	      for ( i = 0 ; i < 4*diamond_size ; i++ ) {
		/* add to list */
		if ( min_cand == candidates[i][0] ) {
		  liste[a_traiter++] = candidates[i][1];
		} // end if: closest candidate
	      } // end for: add neighbors to liste[a_traiter++]
	    } // end if: n_voisins == 0
	} // end while: table not completed
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


int main(){
	int i;
	pt debut = 0;
	pt fin = _largeur/2 +1;
	double* mesh = init_tab_mesh();
	obstacle(mesh);
	double bottom_left[2] = { 5, 5 };
	double top_right[2] = { 10, 10 };
	generate_rectangle(bottom_left, top_right, mesh);

	double* dist = A_tab_distance(mesh, debut, fin);
        save_dist(dist);
	
	pt* chemin = court_chemin_bis(dist, fin);
	save_path(dist, fin, chemin);
	
	free(mesh);
	free(dist);

	return 0;
}