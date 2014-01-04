#include <iostream>
#include <cstdlib>
#include <cmath>
#include "array.hpp"

int main(int argc, char **argv)
{
  array <double> test(4);
  array <double> testing(test);

  test.add(3.1); test.show();
  test.add(5.4); test.show();
  test.add(4.3); test.show();
  test.add(1.); test.show();
  test.remove(1); test.show();
  //test.add(2.9); test.show();
  std::cout << test[2] << std::endl;
  test.getSize();

  const double & x = test[1];
  std::cout << x << '\n';

  test[1] = 2.113;
  test.show();

}
