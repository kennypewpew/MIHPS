#include <iostream>
#include "N2.hpp"

int main(int argc, char **argv) {
  N2 test(2,2);
  N2 tester(2,3);
  std::cout << (test == tester);
  std::cout << std::endl;
}
