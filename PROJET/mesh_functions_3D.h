#ifndef MESH_FUNCTIONS_3D_H
#define MESH_FUNCTIONS_3D_H

#include "stdlib.h"
#include "stdio.h"

typedef int pt;

void generate_circle_3D(double *centre, int rayon, double *mesh);
void generate_rectangle_3D(double *down_left, double *up_right, double *mesh);
void save_dist_3D(double* dist);
void save_path_3D(double* dist, pt arrivee, pt* path);
void save_mesh_3D(double* mesh);

#endif
