#include <algorithm>
#include <array>
#include <complex>
#include <iostream>
#include <string>
#include <vector>

#include <cnpy.h>

//#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Write using MPI, write sequential, compare", "[R/W with mpi]")
{

  int rank;
  int size = 1;
  MPI_CHECK_ERR(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
  MPI_CHECK_ERR(MPI_Comm_size(MPI_COMM_WORLD, &size));

  // number of elements in array
  const size_t N = 10 * size;

  // write with MPI
  const int local_size = N / size;

  // create data
  std::vector<int> data_mpi(local_size);
  for (unsigned int i = 0; i < local_size; i++)
    data_mpi[i] = 10 * rank + i;

  // save it to file
  cnpy::npy_save(MPI_COMM_WORLD, "data_mpi.npy", data_mpi.data(), local_size);


  // write sequential
  if (rank == 0)
  {
    std::vector<int> data(N);
    for (int i = 0; i < N; ++i)
      data[i] = i;

    const std::vector<size_t> shape{ N };
    cnpy::npy_save("data_seq.npy", data.data(), shape, "w");

    // read data generated with MPI and compare
    auto data_mpi_npy = cnpy::npy_load("data_mpi.npy");
    REQUIRE(data_mpi_npy.shape.size() == 1);
    REQUIRE(data_mpi_npy.shape[0] == N);
    auto data_mpi_vec = data_mpi_npy.as_vec<int>();
    // extract local slice
    auto data_mpi_slice =
      std::vector<int>(data_mpi_vec.begin() + 10 * rank, data_mpi_vec.begin() + 10 * (rank + 1));
    // compare with original data
    REQUIRE(data_mpi_slice == data_mpi);
  }
}
