#include "stdlib.h"
#include "stdio.h"
#include "shortest_path.h"

typedef int pt;		//point

int all_voisin(pt current, pt* voisin, double* mesh);
int A_find_voisin(pt current, pt* voisin, double* mesh, pt arrivee);
double* A_tab_distance(double* mesh, pt depart, pt arrivee);
