#include "stdlib.h"
#include "stdio.h"

typedef int pt;		//point
extern int _largeur;

double* init_tab_mesh();
double* init_tab_dist();
void obstacle(double* mesh);
int find_voisin(pt current, pt* voisin, double* mesh);
double* tab_distance(double* mesh, pt depart, pt arrivee);
pt* court_chemin(double* dist, pt arrivee);
pt* court_chemin_bis(double* dist, pt arrivee);

