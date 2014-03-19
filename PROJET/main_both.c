#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "mesh_functions.h"
#include "shortest_path.h"
#include "A_shortest_path.h"

int _largeur = SIZE;
int runs = RUN;

int main() {
  pt debut = 0;
  int i;
  FILE *out = fopen("data/hook/runtime.dat", "a");

  /* choose convenient endpoint */
  pt fin = /*_largeur*_largeur-1;//*/_largeur/2 + 1;

  double djik_time = 0;
  double A_time = 0;
  clock_t start, finish;

  for ( i = 0 ; i < runs ; i++ ) {
    double *mesh = init_tab_mesh();

    /* generate various obstacles */

    /* corner pointing towards start */
    double bottom_left1[] = { _largeur/2 + _largeur/5, _largeur/2 + _largeur/20 };
    double top_right1[] = { _largeur/2, _largeur/2 };
    double bottom_left2[] = { _largeur/2 + _largeur/20, _largeur/2 + _largeur/5 };
    double top_right2[] = { _largeur/2, _largeur/2 };
    //generate_rectangle(top_right1, bottom_left1, mesh);
    //generate_rectangle(top_right2, bottom_left2, mesh);


      /* corner pointing towards end */
    double bottom_left3[] = { _largeur/2 - _largeur/5, _largeur/2 - _largeur/20 };
    double top_right3[] = { _largeur/2, _largeur/2 };
    double bottom_left4[] = { _largeur/2 - _largeur/20, _largeur/2 - _largeur/5 };
    double top_right4[] = { _largeur/2, _largeur/2 };
    //generate_rectangle(bottom_left3, top_right3, mesh);
    //generate_rectangle(bottom_left4, top_right4, mesh);


    /* circle at center */
    double center[] = { _largeur/2, _largeur/2 };
    //generate_circle(center, _largeur/10, mesh);


    /* rectangle at center */
    double bottom_left[] = { _largeur/2 + _largeur/5, _largeur/2 + _largeur/20 };
    double top_right[] = { _largeur/2, _largeur/2 };
    //generate_rectangle(top_right, bottom_left, mesh);


    /* hook */
    obstacle(mesh);

    //save_mesh(mesh, "mesh.vtk");

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

    if ( _largeur == 20 ) {
      save_dist(dist_djik, "dist_djik.vtk");
      save_dist(dist_A, "dist_A.vtk");
      
      pt *path_djik = court_chemin_bis(dist_djik, fin);
      pt *path_A = court_chemin_bis(dist_A, fin);

      save_path(dist_djik, fin, path_djik, "path_djik.vtk");
      save_path(dist_A, fin, path_A, "path_A.vtk");

      free(path_djik);
      free(path_A);
    }


  free(dist_djik);
  free(dist_A);
  free(mesh);

  }

  printf("Average runtime of { Djikstra = %lfs ; A* = %lfs }\n", djik_time/runs, A_time/runs);
  fprintf(out, "%d %lf %lf\n", _largeur, djik_time/runs, A_time/runs);

  return 0;
}
