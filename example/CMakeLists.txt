# test example
add_executable(cnpy_example cnpy_example.cpp)
target_link_libraries(cnpy_example
  PUBLIC
  cnpy::cnpy)

if(CNPY_USE_MPI)
  add_executable(cnpy_example_mpi cnpy_example_mpi.cpp)
  target_link_libraries(cnpy_example_mpi
    PUBLIC
    cnpy::cnpy
    MPI::MPI_CXX)
endif()
