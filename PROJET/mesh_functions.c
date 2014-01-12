#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"

//int largeur = 20;

// Generate a circle obstacle
// centre is passed as int[2] - centre[0]-> x, centre[1]-> y
void generate_circle(double *centre, int rayon, double *mesh) {
  int i;
  for ( i = 0 ; i < _largeur*_largeur ; i++ ) {
    int x = i%_largeur;
    int y = i/_largeur;

    // r^2 = x^2 + y^2
    int ray_curr = (x-centre[0])*(x-centre[0]) + (y-centre[1])*(y-centre[1]);
    if ( ray_curr <= rayon*rayon ) {
      mesh[i] = -1;
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
      mesh[i*_largeur + j] = -1;
    }
  }
}


// Saves distance array as vtk file
void save_dist(double* dist, char *file) {
  FILE *out = fopen(file, "w");
  int i, j;

  fprintf(out, "# vtk DataFile Version 3.0\n");
  fprintf(out, "Distance table\n");
  fprintf(out, "ASCII\n");
  fprintf(out, "DATASET RECTILINEAR_GRID\n");
  fprintf(out, "DIMENSIONS %d %d %d\n", _largeur, _largeur, 1);
  fprintf(out, "X_COORDINATES %d float\n", _largeur);
  for ( i = 0 ; i < _largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");

  fprintf(out, "Y_COORDINATES %d float\n", _largeur);
  for ( i = 0 ; i < _largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");

  fprintf(out, "Z_COORDINATES %d float\n", 1);
  fprintf(out, "%d\n", 0);

  fprintf(out, "POINT_DATA %d\n", _largeur*_largeur);
  fprintf(out, "SCALARS Distance float %d\n", 1);
  fprintf(out, "LOOKUP_TABLE default\n");
  for ( i = 0 ; i < _largeur ; i++ ) {
    for ( j = 0 ; j < _largeur ; j++ ) {
      fprintf(out, "%f\n", dist[j + _largeur*i]);
    } // end for j: -> columns
  } // end for i: \/ rows
  fclose(out);
}



void save_path(double* dist, pt arrivee, pt* path, char *file) {
  FILE *out = fopen(file, "w");
  int i, j;

  fprintf(out, "# vtk DataFile Version 3.0\n");
  fprintf(out, "Shortest path through distance table\n");
  fprintf(out, "ASCII\n");
  fprintf(out, "DATASET UNSTRUCTURED_GRID\n\n");

  fprintf(out, "POINTS %d float\n", (int)dist[arrivee]);
  for ( i = 0 ; i < dist[arrivee] ; i++ ) {
    fprintf(out, "%d %d %d\n", path[i]%_largeur, path[i]/_largeur, 0);
  }
  fprintf(out, "\n");

  fprintf(out, "CELLS 1 %d\n", (int)dist[arrivee]+1);
  fprintf(out, "%d ", (int)dist[arrivee]);
  for ( i = 0 ; i < dist[arrivee] ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");
  fprintf(out, "\n");

  fprintf(out, "CELL_TYPES 1\n");
  fprintf(out, "4\n");

  fclose(out);
}


// Saves obstacle array as vtk file
void save_mesh(double* mesh, char *file) {
  FILE *out = fopen(file, "w");
  int i, j;

  fprintf(out, "# vtk DataFile Version 3.0\n");
  fprintf(out, "Distance table\n");
  fprintf(out, "ASCII\n");
  fprintf(out, "DATASET RECTILINEAR_GRID\n");
  fprintf(out, "DIMENSIONS %d %d %d\n", _largeur, _largeur, 1);
  fprintf(out, "X_COORDINATES %d float\n", _largeur);
  for ( i = 0 ; i < _largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");

  fprintf(out, "Y_COORDINATES %d float\n", _largeur);
  for ( i = 0 ; i < _largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");

  fprintf(out, "Z_COORDINATES %d float\n", 1);
  fprintf(out, "%d\n", 0);

  fprintf(out, "POINT_DATA %d\n", _largeur*_largeur);
  fprintf(out, "SCALARS Distance float %d\n", 1);
  fprintf(out, "LOOKUP_TABLE default\n");
  for ( i = 0 ; i < _largeur ; i++ ) {
    for ( j = 0 ; j < _largeur ; j++ ) {
      fprintf(out, "%f\n", mesh[j + _largeur*i]);
    } // end for j: -> columns
  } // end for i: \/ rows
  fclose(out);
}

