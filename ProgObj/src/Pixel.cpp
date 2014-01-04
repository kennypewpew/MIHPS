#include <iostream>
#include "N2.hpp"
#include "pixel.hpp"

int main(int argc, char **argv) {
  N2 test(2,2);
  N2 tester(1,1);
  Pixel pix(test, 3);
  Pixel pixel(tester, 4);
  Pixel pixels;
  test += pix;
  pix +=pixel;
  std::cout << pixel.getColor();
  std::cout << std::endl;
}
