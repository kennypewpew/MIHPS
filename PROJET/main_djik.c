#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"
#include "shortest_path.h"

int _largeur = 20;

int main(){
	int i;
	pt debut = 0;
	pt fin = _largeur/2 +1;
	double* mesh = init_tab_mesh();
	obstacle(mesh);
	//double bottom_left[2] = { 10, 10 };
	//double top_right[2] = { 15, 15 };
	//generate_rectangle(bottom_left, top_right, mesh);

	double* dist = tab_distance(mesh, debut, fin);
	printf("\n");
	for(i=0; i<_largeur*_largeur;i++){
		if(i%_largeur == 0)	printf("\n");
		printf("%d\t", (int)dist[i]);
	}	
	printf("\n");
        save_dist(dist);
	
	pt* chemin = court_chemin_bis(dist, fin);
	save_path(dist, fin, chemin);
	
	printf("\n");
	for(i=0; i< dist[fin]; i++)
		printf("%d \t %d \n", chemin[i]/_largeur, chemin[i]%_largeur);

	free(mesh);
	free(dist);

	return 0;
}
