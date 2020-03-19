# test example
add_executable(cnpy_example cnpy_example.cpp)
target_link_libraries(cnpy_example 
  PUBLIC
  cnpy::cnpy)
