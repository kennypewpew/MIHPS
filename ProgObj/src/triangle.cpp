#include "Triangle.hpp"
#include "pixel.hpp"
#include "N2.hpp"

#include <iostream>

int main ( int argc, char **argv ) {
  Pixel a(5,5,10), b(-5,-5,20), c(5,-5,30);
  Triangle tri(a,b,c);
  int x, y;
  std::cin >> x >> y;
  N2 check(x,y);
  bool maybe;

  maybe = tri.CircleContains(check);
  if ( true == maybe ) {
    std::cout << "yes";
  }
  if ( false == maybe ) {
    std::cout << "no";
  }
  std::cout << "\n";
}
