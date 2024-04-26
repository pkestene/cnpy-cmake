#include <cnpy.h>
#include <complex>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

const unsigned int N = 10;

namespace
{
using namespace cnpy;

void
test(MPI_Comm mpi_comm)
{
  int rank;
  MPI_CHECK_ERR(MPI_Comm_rank(mpi_comm, &rank));

  auto local_size = N;

  // create data
  auto data = new uint32_t[N];
  for (unsigned int i = 0; i < N; i++)
    data[i] = 10 * rank + i;

  // save it to file
  cnpy::npy_save(mpi_comm, "array_mpi.npy", data, N);

  // cleanup: note that we are responsible for deleting all loaded data
  delete[] data;
}

} // namespace

int
main(int argc, char * argv[])
{
  MPI_Init(&argc, &argv);

  ::test(MPI_COMM_WORLD);

  MPI_Finalize();
}
