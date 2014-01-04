#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "array.hpp"
#include "N2.hpp"
#include "pixel.hpp"
#include "pgm.hpp"
#include <iostream>

/* Summary
     public:
       array <Pixel> pixels // *actually only need int to store color if you want to save memory
       int rows, cols
     public:
       Image(const PGMImage&)
       ~Image()
       Pixel pixel(const N2&)
       Pixel pixel(const int&, const int&)
       int nbRows() const;
       int nbCols() const;
       int number(const Pixel& pix);
       int number(const int&, const int&);
       Image& operator=(const Image& equal) {
 */

class Image
{
private:
  array <Pixel> pixels;
  int rows, cols;

public:
  /* Default constructor: mostly useful for Mesh constructor*/
  Image() {
    //std::cout << "Image by default\n";
    rows = 0;
    cols = 0;
  }

  /* Construct based off of a read image */
  Image(const PGMImage& img) {
    rows = img.height();
    cols = img.width();

    //std::cout << rows << " rows, " << cols << " columns" << "\n";

    for ( int i = 0 ; i < rows ; i++ ) {
      for ( int j = 0 ; j < cols ; j++ ) {
	Pixel tmp(j,i,img(i,j)); // see pgm.hpp l:37 for i<-->j
	pixels.add( tmp );
      } // end for j: -> row
    } // end for i: \/ rows
  } // end constructor

  ~Image() {}

/* Assignment operator */
  Image& operator=(const Image& equal) {
    pixels = equal.pixels;
    rows = equal.nbRows();
    cols = equal.nbCols();
    //std::cout << "Assignment complete\n";
  }

/* Methods */
  Pixel pixel(const N2& ref) {
    Pixel out;
    out = pixels[ref.x() + cols*ref.y()];
    return out;
  }

  Pixel pixel(const int& x, const int& y) {
    Pixel out;
    out = pixels[x + cols*y];
    return out;
  }

  int nbRows() const {
    return rows;
  }

  int nbCols() const {
    return cols;
  }

  int number(const Pixel& pix) const {
    int tmp;
    tmp = pix.x() + nbCols()*pix.y();
    return tmp;
  }

  int number(const int& x, const int& y) const {
    int tmp;
    tmp = x + nbCols()*y;
    return tmp;
  }

};






#endif
