#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"

typedef int pt;		//point
int _largeur = 100;

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
		mesh[demi + i*_largeur] = 0;
	for(i = demi+demi*_largeur ; i < demi*_largeur + _largeur-3 ; i++ ) {
	  mesh[i] = 0;
	}
} 

// Add neighbors to search priority queue
// Returns number of neighbors
// DOES NOT CHECK IF NEIGHBOR IS OPEN TO SEARCH(doesn't currently affect problem)
int find_voisin(pt current, pt* voisin){
	int y = current/_largeur;
	int x = current%_largeur;
	int i = 0;
	if(y != 0)	voisin[i++] = current-_largeur;
	if(x != 0)	voisin[i++] = current-1;
	if(x != _largeur -1) voisin[i++] = current+1;
	if(x != _largeur -1) voisin[i++] = current+_largeur;
	/* Should probably set rest of array to 0, just to be safe */
	int j;
	for ( j = i+1 ; j < 4 ; j++ ) { voisin[j] = 0; }
	return i;
}

// Create and fill/calculate distance table
// Stops upon reaching destination (ok for this problem, not generalizable)
double* tab_distance(double* mesh, pt depart, pt arrivee){
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
	while(a_traiter <= n_liste){ /* Changed while to treat whole domain */
		n_voisin = find_voisin(current, voisin);
		for(i=0; i<n_voisin; i++)
		        // If not obstacle && distance has not been checked yet,
		        // set neighbor's distance to current's + 1,
		        // add neighbors to search queue
			if(mesh[voisin[i]] == 1. && dist[voisin[i]] ==-1){
				dist[voisin[i]] = dist[current] + 1;
				liste[n_liste++] = voisin[i];
				/* on ne compare pas la distance 
				    mais je ne pense pas que c'est grave
				    pour ce probleme */
			}
		current = liste[a_traiter++]; // Increment position in list[]
	}	
	free(liste);
	return dist;
}

int main(){
	int i;
	pt debut = 0;
	pt fin = _largeur*_largeur - 1;
	double* mesh = init_tab_mesh();
	obstacle(mesh);
	double bottom_left[2] = { 8, 8 };
	double top_right[2] = { 15, 15 };
	double center[2] = { 30, 50 };
	generate_rectangle(bottom_left, top_right, mesh);
	generate_circle(center, 10, mesh);
	double center2[2] = { 25, 58 };
	generate_circle(center2, 10, mesh);
	double* dist = tab_distance(mesh, debut, fin);
	printf("\n");
	//for(i=0; i<fin+1;i++){
	//if(i%_largeur == 0)	printf("\n");
	//printf("%d\t", (int)dist[i]);
	//}	
	printf("\n");
	save_dist(dist);

	free(mesh);
	free(dist);

	return 0;
}
