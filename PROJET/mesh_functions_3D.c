#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions_3D.h"

int largeur = 20;

// Generate a circle obstacle
// centre is passed as int[3] - centre[0]-> x, centre[1]-> y, centre[2]-> z
void generate_circle_3D(double *centre, int rayon, double *mesh) {
  int i;
  for ( i = 0 ; i < largeur*largeur*largeur ; i++ ) {
    int x = i%largeur;
    int y = i/largeur;
    int z = i/(largeur*largeur);

    // r^2 = x^2 + y^2 + z^2
    int ray_curr = (x-centre[0])*(x-centre[0]) + (y-centre[1])*(y-centre[1]) + (z-centre[2])*(z-centre[2]);
    if ( ray_curr <= rayon*rayon ) {
      mesh[i] = -1;
    }
  }
}

// Generate rectangle obstacle
// down_left and up_right are { x, y, z }
void generate_rectangle(double *down_left_front, double *up_right_back, double *mesh) {
  int i, j, k;

  int x_left = (int)(down_left_front[0]);
  int x_right = (int)(up_right_back[0]);
  int y_top = (int)(up_right_back[1]);
  int y_bot = (int)(down_left_front[1]);
  int z_front = (int)(down_left_front[2]);
  int z_back = (int)(up_right_back[2]);

  for ( k = z_front ; k <= z_back ; k++ ) {
    for ( i = y_bot ; i <= y_top ; i++ ) {
      for ( j = x_left ; j <= x_right ; j++ ) {
	mesh[k*(largeur*largeur) + i*largeur + j] = -1;
      }
    }
  }
}


// Saves distance array as vtk file
void save_dist_3D(double* dist) {
  FILE *out = fopen("distance.vtk", "w");
  int i, j, k;

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

  fprintf(out, "Z_COORDINATES %d float\n", largeur);
  for ( i = 0 ; i < largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "\n");

  fprintf(out, "POINT_DATA %d\n", largeur*largeur);
  fprintf(out, "SCALARS Distance float %d\n", 1);
  fprintf(out, "LOOKUP_TABLE default\n");
  for ( k = 0 ; k < largeur ; k++ ) {
    for ( i = 0 ; i < largeur ; i++ ) {
      for ( j = 0 ; j < largeur ; j++ ) {
	fprintf(out, "%f\n", dist[j + largeur*i + largeur*largeur*k]);
      } // end for j: -> columns
    } // end for i: \/ rows
  }// end for k: front->back
  fclose(out);
}



void save_path_3D(double* dist, pt arrivee, pt* path) {
  FILE *out = fopen("path.vtk", "w");
  int i;

  fprintf(out, "# vtk DataFile Version 3.0\n");
  fprintf(out, "Shortest path through distance table\n");
  fprintf(out, "ASCII\n");
  fprintf(out, "DATASET UNSTRUCTURED_GRID\n\n");

  fprintf(out, "POINTS %d float\n", (int)dist[arrivee]);
  for ( i = 0 ; i < dist[arrivee] ; i++ ) {
    fprintf(out, "%d %d %d\n", path[i]%largeur, path[i]/largeur, path[i]/(largeur*largeur));
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
void save_mesh_3D(double* mesh) {
  FILE *out = fopen("obstacles.vtk", "w");
  int i, j, k;

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
  for ( i = 0 ; i < largeur ; i++ ) {
    fprintf(out, "%d ", i);
  }
  fprintf(out, "%d\n", 0);

  fprintf(out, "POINT_DATA %d\n", largeur*largeur);
  fprintf(out, "SCALARS Distance float %d\n", 1);
  fprintf(out, "LOOKUP_TABLE default\n");
  for ( k = 0 ; k < largeur ; k++ ) {
    for ( i = 0 ; i < largeur ; i++ ) {
      for ( j = 0 ; j < largeur ; j++ ) {
	fprintf(out, "%f\n", mesh[j + largeur*i + largeur*largeur*k]);
      } // end for j: -> columns
    } // end for i: \/ rows
  } // end for k: planes
  fclose(out);
}

