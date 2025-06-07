
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main()
{
  std::cout << "LASD Libraries 2025" << std::endl;
  lasdtest();
  std::cout << std::endl
            << "Starting additional tests..." << std::endl;
  mylasdtest();
  return 0;
}
