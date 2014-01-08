#ifndef MESH_FUNCTIONS_H
#define MESH_FUNCTIONS_H

#include "stdlib.h"
#include "stdio.h"

typedef int pt;

void generate_circle(double *centre, int rayon, double *mesh);
void generate_rectangle(double *down_left, double *up_right, double *mesh);
void save_dist(double* dist);
void save_path(double* dist, pt arrivee, pt* path);
void save_mesh(double* mesh);

#endif
