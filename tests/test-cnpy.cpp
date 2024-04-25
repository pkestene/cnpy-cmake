#include <algorithm>
#include <array>
#include <complex>
#include <iostream>
#include <string>
#include <vector>

#include <cnpy.h>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Write/Read data 1d int", "[read/write]")
{
  std::vector<int>    data{ 1, 2, 3, 4, 5, 6 };
  std::vector<size_t> shape{ 6 };

  cnpy::npy_save("array1d_int.npy", &(data[0]), shape, "w");

  auto array = cnpy::npy_load("array1d_int.npy");
  auto data_read = array.as_vec<int>();

  REQUIRE(data == data_read);
}
