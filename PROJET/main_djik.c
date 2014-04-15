#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"
#include "shortest_path.h"
#include "time.h"
#include "mpi.h"

int _largeur;

int main(int argc, char **argv){
  MPI_Init(&argc, &argv);
  _largeur = atoi(argv[1]);
	int i;
	pt debut = 0;
	pt fin = _largeur/2 +1;
	double* mesh = init_tab_mesh();
	obstacle(mesh);
	FILE *out = fopen("times.dat", "a");
	//double bottom_left[2] = { 10, 10 };
	//double top_right[2] = { 15, 15 };
	//generate_rectangle(bottom_left, top_right, mesh);
	
	clock_t start = clock();
	double begin = MPI_Wtime();
	double* dist = tab_distance(mesh, debut, fin);
	clock_t finish = clock();
	double end = MPI_Wtime();

	double runtime = end - begin;
	  //(double)(finish-start)/CLOCKS_PER_SEC;
	fprintf(out, "%d\t%g\n", _largeur, runtime);
	fclose(out);

	//pt* chemin = court_chemin_bis(dist, fin);
	//save_dist(dist, "distance.vtk");
	//save_path(dist, fin, chemin, "path.vtk");
	
	free(mesh);
	free(dist);

	MPI_Finalize();

	return 0;
}
