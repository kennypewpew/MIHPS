#include "Image.hpp"
#include "N2.hpp"
#include "pixel.hpp"

#include <iostream>

int main( int argc, char **argv ) {
  char a[30] = "data/Image/a.pgm";
  PGMImage raw(a);
  Image picture(raw);
  Pixel pix;
  N2 pos(100,100);

  for ( int i = 0 ; i < 1000 ; i+= 100 ) {
    pix = picture.pixels[i];
    std:: cout << pix << "\n";
  }

  std:: cout << picture.nbRows() << " by " << picture.nbCols() << " = " << picture.nbRows() * picture.nbCols() << "\n";
}
