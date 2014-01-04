#include "Mesh.hpp"
#include "pgm.hpp"
#include "Triangle.hpp"
#include "pixel.hpp"
#include "Cavite.hpp"

#include <iostream>

int main( int argc, char **argv) {
  char a[20] = "data/Image/a.pgm";
  Mesh test(a);

  int number, precision;
  //std::cout << "Enter number of iterations, then precision:  ";
  //std::cin >> number >> precision;

  /*
  test.add(1, 30);
  test.saveVTK("test1.vtk");
  test.add(1, 30);
  test.saveVTK("test2.vtk");
  test.add(1, 30);
  test.saveVTK("test3.vtk");
  test.add(1, 30);
  test.saveVTK("test4.vtk");
  test.add(1, 30);
  test.saveVTK("test5.vtk");
  test.add(1, 30);
  test.saveVTK("test6.vtk");
  test.add(1, 30);
  test.saveVTK("test7.vtk");
  test.add(1, 30);
  test.saveVTK("test8.vtk");
  test.add(1, 30); 
  test.saveVTK("test9.vtk");
  test.add(1, 30);
  test.saveVTK("test10.vtk");
  */

  //test.add(10000, 10);
  //test.saveVTK("test1.vtk");
  test.add(10000, 9);
  test.saveVTK("test2.vtk");
  test.add(2000, 8);
  test.saveVTK("test3.vtk");
  test.add(1000, 7);
  test.saveVTK("test4.vtk");
  test.add(1000, 7);
  test.saveVTK("test5.vtk");
  test.add(1000, 7);
  test.saveVTK("test6.vtk");
  test.add(1000, 7);
  test.saveVTK("test7.vtk");/*
  test.add(100, 5);
  test.saveVTK("test8.vtk");
  test.add(100, 5);
  test.saveVTK("test9.vtk");
  test.add(100, 5);
  test.saveVTK("test10.vtk");
  test.add(100, 5);
  test.saveVTK("test10.vtk");
			    */

  //test.saveMESH("test.mesh");
}
