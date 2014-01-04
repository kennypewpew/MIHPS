#include "Maillage.hpp"
#include "pgm.hpp"
#include "Triangle.hpp"
#include "pixel.hpp"
#include "Cavite.hpp"

#include <iostream>

int main( int argc, char **argv) {
  char a[20] = "data/Image/a.pgm";
  PGMImage test(a);

  Maillage mesh(test);


}
