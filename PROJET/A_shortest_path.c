#include "stdlib.h"
#include "stdio.h"
#include "mesh_functions.h"
#include "A_shortest_path.h"

extern int _largeur;

// fill array with ALL neighbors, not just the valid ones
// returns number of neighbors ( probably 4 )
int all_voisin(pt current, pt* voisin, double* mesh){
	int y = current/_largeur;
	int x = current%_largeur;
	int i = 0;
	if(y != 0 )    voisin[i++] = current-_largeur;
	if(x != 0 )	voisin[i++] = current-1;
	if(x != _largeur -1 ) voisin[i++] = current+1;
	if(y != _largeur -1 ) voisin[i++] = current+_largeur;
	// Should probably set rest of array to 0, just to be safe
	int j;
	for ( j = i+1 ; j < 4 ; j++ ) { voisin[j] = 0; }
	return i;
}

// Add neighbors using A* algorithm
// On ajoute que les voisins qui sont les plus proches(ignorant les obstacles) a la liste de voisins a visiter. Les autres seront ajouté a la liste plus tard par un autre chemin.
int A_find_voisin(pt current, pt* voisin, double* mesh, pt arrivee){
        /**** Same as find_voisin ****/
	int y = current/_largeur;
	int x = current%_largeur;
	int i = 0;
	//printf("Point %d, %d: ", x, y);
	// add valid neighbors (not edge && not obstacle)
	if(y != 0 && mesh[current-_largeur] != -1)	voisin[i++] = current-_largeur;
	if(x != 0 && mesh[current-1] != -1)	voisin[i++] = current-1;
	if(x != _largeur -1 && mesh[current+1] != -1) voisin[i++] = current+1;
	if(y != _largeur -1 && mesh[current+_largeur] != -1) voisin[i++] = current+_largeur;
	int j;
	for ( j = i ; j < 4 ; j++ ) { voisin[j] = 0; }

	/**** Begin A* specific section ****/
	int yy = arrivee/_largeur;
	int xx = arrivee%_largeur;

	// calculate distance from each valid neighbor to endpoint
	int min_dist = (x-xx)*(x-xx) + (y-yy)*(y-yy); // only want to add points closer than current
	for ( j = 0 ; j < i ; j++ ) { 
	  if ( (( voisin[j]/_largeur - yy)
		*( voisin[j]/_largeur - yy) 
		+( voisin[j]%_largeur - xx)
		*( voisin[j]%_largeur - xx))
	       < min_dist )
	    { min_dist = (voisin[j]/_largeur - yy)*( voisin[j]/_largeur - yy)
	      +( voisin[j]%_largeur - xx)*( voisin[j]%_largeur - xx) ;
	    } // end if: calculate distance to closest neighbor
	} // end for: calculate min_dist

	// invalidate neighbors which are not closer than current point
	for ( j = i-1 ; j >= 0 ; j-- ) {
	  if ( ( voisin[j]/_largeur - yy)*( voisin[j]/_largeur - yy)
	       +( voisin[j]%_largeur - xx)*( voisin[j]%_largeur - xx)
	       > min_dist ) {
	    int k;
	    for ( k = j ; k < 3 ; k++ ) {
	      voisin[k] = voisin[k+1]; // squash value to be removed
	    }
	    i--;
	  } // end if: neighbor is closer than current
	} // end for: remove neighbors from list
	//printf("%d valid neighbors: ", i);
	//for ( j = 0 ; j < i ; j++ ) {
	//printf("%d, %d;  ", voisin[j]%_largeur, voisin[j]/_largeur);
	//}
	//printf("\n");
	return i;
}

// Create and fill/calculate distance table
// Si A_find_voisin trouve des voisins valide, on fait comme avant pour les explorer.
// S'il n'y a pas de voisins valide, on recommence l'exploration autour du point de debut en regardant les diamands de point autour ce point
double* A_tab_distance(double* mesh, pt depart, pt arrivee){
        int i;
	int fin = _largeur*_largeur;
	double* dist = init_tab_dist(); // Create initialised distance array
	dist[depart] = 0;
	pt* liste = malloc(10*fin*sizeof(pt)); // Points in order to be checked
	int a_traiter = 0; // Positition in list[]
	int n_liste = 0; // Number of valid points in list[]
	pt current = depart; // Current position within list[]
	pt voisin[4]; // Array containing list of neighbors
	int n_voisin; // Number of valid neighbors to check
	int max_diamond_size = 1;
	//n_voisin = A_find_voisin(3+3*_largeur, voisin, mesh, arrivee);
	//while(a_traiter <= n_liste){ 
	int duplicates = 0;
	while ( current != arrivee ) {
	  //int l;
	  //for ( l = 0 ; l < 200 ; l++ ) {
	  n_voisin = A_find_voisin(current, voisin, mesh, arrivee);
	  if ( n_voisin != 0 ) {
	    /* should probably reverse A_find_voisin and find_voisin (minor optimisation) */
	    duplicates += n_voisin - 1;
	    for(i=0; i<n_voisin; i++) {
	      int repeated = 0;
	      int j;
	      for ( j = n_liste - duplicates ; j < n_liste ; j++ ) {
		if ( liste[j] == voisin[i] ) { repeated = 1; }
	      }
		if ( repeated == 0 ) { liste[n_liste++] = voisin[i]; }
	      /* NO DISTANCE COMPARISON CHECK */
		/* unlike djikstra, this actually is an issue here 
		   -- fix by setting distance to [lowest of set neighbors(of point being updated)] + 1 */
	    } // end for: neighbors
	  
	      n_voisin = find_voisin(current, voisin, mesh);
	      for(i=0; i<n_voisin; i++) {
		//if(dist[voisin[i]] ==-1){ dist[voisin[i]] = dist[current] + 1; }
		if ( dist[voisin[i]] == -1 ) {
		  int voisin_voisin[4];
		  int n_voisin_voisin = all_voisin(voisin[i], voisin_voisin, mesh);
		  int k;
		  int min_dist = _largeur*_largeur;
		  for ( k = 0 ; k < n_voisin_voisin ; k++ ) {
		    if ( dist[voisin_voisin[k]] < min_dist
			 && dist[voisin_voisin[k]] != -1 ) {
		      min_dist = dist[voisin_voisin[k]];
		    }// end if: distance is minimal
		  }// end for: neighbor's neighbors
		  dist[voisin[i]] = min_dist + 1;

		}// end if: neighbor's distance needs setting


	      } // end for: voisins

	      mesh[current] = -1; // mark node as visited ( will not be revisited )
	      current = liste[a_traiter++]; // Increment position in list[]
	      //printf("n_liste = %d, a_traiter = %d\n\n", n_liste, a_traiter);
	    }
	    else{ /* add point from a diamond centered on the origin */ 
	      int array_size = 0;
	      int diamond_size;
	      for ( diamond_size = 1 ; diamond_size <= max_diamond_size ; diamond_size++ ) { array_size += diamond_size; }
	      pt candidates[4*array_size][2]; // store distance[0] and position[1] of valid points
	      int i_cand = 0;
	      int min_cand = _largeur*_largeur*2;
	      /******** Start checking diamonds **********/
	      for ( diamond_size = 1 ; diamond_size <= max_diamond_size ; diamond_size++) {
		//printf("Diamond of size %d of %d\n", diamond_size, max_diamond_size);
		/* top vertex -> right vertex */
		for ( i = 0 ; i < diamond_size ; i++ ) {
		  int y = depart/_largeur + diamond_size - i;
		  int x = depart%_largeur + i;
		  // if not obstacle && distance already set(point open to search) && not out of bounds
		  if ( x >= 0 && y >= 0 && x < _largeur && y < _largeur) {
		    if ( mesh[x + _largeur * y] != -1 && 
			 dist[x + _largeur * y] != -1 ) {
		      candidates[i_cand][0] = (x - arrivee%_largeur)*(x - arrivee%_largeur)
		                             +(y - arrivee/_largeur)*(y - arrivee/_largeur);
		      candidates[i_cand][1] = x + y*_largeur;
		      if ( candidates[i_cand][0] <= min_cand ) {
			min_cand = candidates[i_cand][0];
		      };
		      i_cand++;
		    } // end if: point is valid
		  } // end if: in bounds
		} // end for: top right edge of diamond
		/* right vertex -> bottom vertex */
		for ( i = 0 ; i < diamond_size ; i++ ) {
		  int y = depart/_largeur - i;
		  int x = depart%_largeur + (diamond_size - i);
		  if ( x >= 0 && y >= 0 && x < _largeur && y < _largeur) {
		    if ( mesh[x + _largeur * y] != -1 && 
			 dist[x + _largeur * y] != -1 ) {
		      candidates[i_cand][0] = (x-arrivee%_largeur)*(x-arrivee%_largeur)
			                     +(y-arrivee/_largeur)*(y-arrivee/_largeur);
		      candidates[i_cand][1] = x + y*_largeur;
		      if ( candidates[i_cand][0] <= min_cand ) {
			min_cand = candidates[i_cand][0];
		      }
		    i_cand++;
		  } // end if: point is valid
		  } // end if: point is in bounds
		} // end if: bottom right edge of diamond
		/* bottom vertex -> left vertex */
		for ( i = 0 ; i < diamond_size ; i++ ) {
		  int y = depart/_largeur - (diamond_size - i);
		  int x = depart%_largeur - i;
		  if ( x >= 0 && y >= 0 && x < _largeur && y < _largeur) {
		    if ( mesh[x + _largeur * y] != -1 && 
			 dist[x + _largeur * y] != -1 ) {
		      candidates[i_cand][0] = (x-arrivee%_largeur)*(x-arrivee%_largeur)
			                     +(y-arrivee/_largeur)*(y-arrivee/_largeur);
		      candidates[i_cand][1] = x + y*_largeur;
		      if ( candidates[i_cand][0] <= min_cand ) {
			min_cand = candidates[i_cand][0];
		      }
		      i_cand++;
		    } // end if: point is valid
		  } // end if: point is in bounds
		} // end if: bottom left edge of diamond
		/* left vertex -> top vertex */
		for ( i = 0 ; i < diamond_size ; i++ ) {
		  int y = depart/_largeur + i;
		  int x = depart%_largeur - (diamond_size - i);
		  if ( x >= 0 && y >= 0 && x < _largeur && y < _largeur) {
		    if ( mesh[x + _largeur * y] != -1 && 
			 dist[x + _largeur * y] != -1 ) {
		      candidates[i_cand][0] = (x-arrivee%_largeur)*(x-arrivee%_largeur)
		                             +(y-arrivee/_largeur)*(y-arrivee/_largeur);
		      candidates[i_cand][1] = x + y*_largeur;
		      if ( candidates[i_cand][0] <= min_cand ) {
			min_cand = candidates[i_cand][0];
		      }
		      i_cand++;
		    } // end if: point is valid
		  } // end if: in bounds
		} // end if: top left edge of diamond
	      } // end for: diamond sizes
	      /******** End checking diamonds **********/

	      /* Add points closest to arrivee */
	      int added = 0;
	      for ( i = 0 ; i < i_cand ; i++ ) {
		if ( min_cand == candidates[i][0] ) {
		  liste[n_liste++] = candidates[i][1];
		  //printf("Candidate added\n");
		  added = 1;
		  /* Enlarge diamond if edge point is used */
		  if ( candidates[i][1]/_largeur - depart/_largeur
		       +candidates[i][1]%_largeur - depart%_largeur
		       == max_diamond_size ) { max_diamond_size++; }
		} // end if: closest candidate

	      } // end for: add neighbors to list
	      if ( added == 1 ) {
		current = liste[a_traiter++];
	      }
	      else { max_diamond_size++; 
		//printf("Diamond enlarged to %d, i_cand = %d, min_cand = %d\n", max_diamond_size, i_cand, min_cand);
		for ( i = 0 ; i < i_cand ; i++ ) {
		  //printf("%d, %d: %d\n", candidates[i][1]%_largeur, candidates[i][1]/_largeur, candidates[i][0]);
		}
	      }
	      //printf("n_liste = %d, a_traiter = %d\n\n", n_liste, a_traiter);
		mesh[current] = -1;

	    } // end if: n_voisins == 0

	} // end while: fill distance table
	//printf("%d nodes visited on the way to %d, %d\n", n_liste, arrivee%_largeur, arrivee/_largeur);
	free(liste);
	return dist;
}
