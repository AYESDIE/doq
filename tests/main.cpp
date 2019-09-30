// This will be used for testing purpose till we
// don't have a proper build system using CMake.

#include <iostream>

//#define CATCH_CONFIG_MAIN  // catch.hpp will define main()
#define CATCH_CONFIG_RUNNER  // we will define main()
#include "catch.hpp"

int main(int argc, char** argv)
{
  size_t seed = std::time(NULL);
  srand((unsigned int) seed);

  return Catch::Session().run(argc, argv);
}
