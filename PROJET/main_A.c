#include "stdio.h"
#include "stdlib.h"
#include "shortest_path.h"
#include "A_shortest_path.h"

int _largeur = 20;

int main(){
	int i;
	pt debut = 0;//3*_largeur+3;
	pt fin = _largeur/2 +1;
	//pt fin = (_largeur-1)*_largeur -1;
	double* mesh = init_tab_mesh();
	obstacle(mesh);
	//double bottom_left[2] = { 4, 3 };
	//double top_right[2] = { 6, 7 };
        //generate_rectangle(bottom_left, top_right, mesh);

	double bottomleft[2] = { 3, 4 };
	double topright[2] = { 7, 6 };
        //generate_rectangle(bottomleft, topright, mesh);

	save_mesh(mesh);

	double* dist = A_tab_distance(mesh, debut, fin);

	save_dist(dist);

	pt* chemin = court_chemin_bis(dist, fin);
	save_path(dist, fin, chemin);
	
	free(chemin);
	free(mesh);
	free(dist);

	return 0;
}

