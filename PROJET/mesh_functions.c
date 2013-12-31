#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"

int largeur = 100;

// Generate a circle obstacle
// centre is passed as int[2] - centre[0]-> x, centre[1]-> y
void generate_circle(double *centre, int rayon, double *mesh) {
  int i;
  for ( i = 0 ; i < largeur*largeur ; i++ ) {
    int x = i%largeur;
    int y = i/largeur;

    // r^2 = x^2 + y^2
    int ray_curr = (x-centre[0])*(x-centre[0]) + (y-centre[1])*(y-centre[1]);
    if ( ray_curr <= rayon*rayon ) {
      mesh[i] = 0;
    }
  }
}

// Generate rectangle obstacle
// down_left and up_right are { x, y }
void generate_rectangle(double *down_left, double *up_right, double *mesh) {
  int i, j;

  int x_left = (int)(down_left[0]);
  int x_right = (int)(up_right[0]);
  int y_top = (int)(up_right[1]);
  int y_bot = (int)(down_left[1]);

  for ( i = y_bot ; i <= y_top ; i++ ) {
    for ( j = x_left ; j <= x_right ; j++ ) {
      mesh[i*largeur + j] = 0;
    }
  }
}


// Saves distance array as vtk file
void save_dist(double* dist) {
  FILE *out = fopen("sample.vtk", "w");
  int i, j;

  fprintf(out, "# vtk DataFile Version 3.0\n");
  fprintf(out, "Distance table\n");
  fprintf(out, "ASCII\n");
  fprintf(out, "DATASET RECTILINEAR_GRID\n");
  fprintf(out, "DIMENSIONS %d %d %d\n", largeur, largeur, 1);
  fprintf(out, "X_COORDINATES %d float\n", largeur);
  for ( i = 0 ; i < largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");

  fprintf(out, "Y_COORDINATES %d float\n", largeur);
  for ( i = 0 ; i < largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");

  fprintf(out, "Z_COORDINATES %d float\n", 1);
  fprintf(out, "%d\n", 0);

  fprintf(out, "POINT_DATA %d\n", largeur*largeur);
  fprintf(out, "SCALARS Distance float %d\n", 1);
  fprintf(out, "LOOKUP_TABLE default\n");
  for ( i = 0 ; i < largeur ; i++ ) {
    for ( j = 0 ; j < largeur ; j++ ) {
      fprintf(out, "%f\n", dist[j + largeur*i]);
    } // end for j: -> columns
  } // end for i: \/ rows
}
