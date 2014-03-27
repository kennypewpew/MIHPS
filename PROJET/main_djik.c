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
	
	pt* chemin = court_chemin_bis(dist, fin);
	save_dist(dist, "distance.vtk");
	save_path(dist, fin, chemin, "path.vtk");
	
	free(mesh);
	free(dist);

	return 0;
}
