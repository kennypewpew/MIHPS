#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "mesh_functions.h"
#include "shortest_path.h"
#include "A_shortest_path.h"

int _largeur = 20;
int runs = 10;

int main() {
  pt debut = 0;
  int i;
  FILE *out = fopen("data/none/runtime.dat", "a");

  /* choose convenient endpoint */
  pt fin = _largeur*_largeur - 1;

  double djik_time = 0;
  double A_time = 0;
  clock_t start, finish;

  for ( i = 0 ; i < runs ; i++ ) {
    double *mesh = init_tab_mesh();
    /* generate various obstacles */

    if ( _largeur == 20 ) { save_mesh(mesh, "mesh.vtk"); }

    start = clock();
    double *dist_djik = tab_distance(mesh, debut, fin);
    finish = clock();
    djik_time += (double)(finish-start)/CLOCKS_PER_SEC;
    //printf("Djikstra finished\n");

    start = clock();
    double *dist_A = A_tab_distance(mesh, debut, fin);
    finish = clock();
    A_time += (double)(finish-start)/CLOCKS_PER_SEC;
    //printf("A* finished\n");

    //pt *path_djik = court_chemin_bis(dist_djik, fin);
    //pt *path_A = court_chemin_bis(dist_A, fin);

    if ( _largeur == 20 ) {
      save_dist(dist_djik, "dist_djik.vtk");
      save_dist(dist_A, "dist_A.vtk");
      
      //save_path(dist_djik, fin, path_djik, "path_djik.vtk");
      //save_path(dist_A, fin, path_A, "path_A.vtk");
    }


  free(dist_djik);
  free(dist_A);
  //free(path_djik);
  //free(path_A);
  free(mesh);

  }

  printf("Average runtime of { Djikstra = %lfs ; A* = %lfs }\n", djik_time, A_time);
  //fprintf(out, "%d %lf %lf\n", _largeur, djik_time, A_time);

  return 0;
}
