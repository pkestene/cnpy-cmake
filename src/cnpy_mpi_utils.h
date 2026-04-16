#ifndef CNPY_MPI_UTILS_H_
#define CNPY_MPI_UTILS_H_

#include <mpi.h>
#include <stdio.h>

namespace cnpy
{

// =======================================================================================
// =======================================================================================
int
mpi_check_error(int err, char const * const func, const char * const file, int const line)
{

  if (err != MPI_SUCCESS)
  {
    int  errorStringLen;
    char errorString[MPI_MAX_ERROR_STRING];
    MPI_Error_string(err, errorString, &errorStringLen);
    fprintf(stderr, "Error at %s:%d: calling %s ==> %s\n", file, line, func, errorString);
  }

  return err;
} // check_mpi_error

} // namespace cnpy

// clang-format off
# define MPI_CHECK_ERR(value) ::cnpy::mpi_check_error((value), #value, __FILE__, __LINE__)
// clang-format on

namespace cnpy
{
// =======================================================================================
// =======================================================================================
template <typename T>
inline MPI_Datatype
mpi_type()
{
  static_assert(!std::is_same<T, T>::value, "Unknown MPI type");
  return MPI_DATATYPE_NULL;
}

template <>
inline MPI_Datatype
mpi_type<double>()
{
  return MPI_DOUBLE;
}

template <>
inline MPI_Datatype
mpi_type<float>()
{
  return MPI_FLOAT;
}

template <>
inline MPI_Datatype
mpi_type<uint64_t>()
{
  return MPI_UINT64_T;
}

template <>
inline MPI_Datatype
mpi_type<uint32_t>()
{
  return MPI_UINT32_T;
}

#ifdef __APPLE__
template <>
inline MPI_Datatype
mpi_type<unsigned long>()
{
  return MPI_UNSIGNED_LONG;
}
#endif // __APPLE__

template <>
inline MPI_Datatype
mpi_type<uint16_t>()
{
  return MPI_UINT16_T;
}

template <>
inline MPI_Datatype
mpi_type<uint8_t>()
{
  return MPI_UINT8_T;
}

template <>
inline MPI_Datatype
mpi_type<int64_t>()
{
  return MPI_INT64_T;
}

template <>
inline MPI_Datatype
mpi_type<int32_t>()
{
  return MPI_INT32_T;
}

template <>
inline MPI_Datatype
mpi_type<int16_t>()
{
  return MPI_INT16_T;
}

template <>
inline MPI_Datatype
mpi_type<int8_t>()
{
  return MPI_INT8_T;
}

template <>
inline MPI_Datatype
mpi_type<char>()
{
  return MPI_CHAR;
}

template <>
inline MPI_Datatype
mpi_type<bool>()
{
  return MPI_CXX_BOOL;
}

} // namespace cnpy

#endif // CNPY_MPI_UTILS_H_
