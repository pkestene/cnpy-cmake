# What is cnpy ?

Simple utility class to dump data array into a .npy file
which is directly readable by numpy/python.

This utility is written by Carl Rogers: https://github.com/rogersce/cnpy

The original code has been slightly refactored (cmake) to provide a pkgconfig file and an installation process.

# How to build using cmake ?

## Build cnpy

```shell
export CNPY_INSTALL_PATH=/opt/cnpy-0.2.0
mkdir _build; cd _build
cmake -DCMAKE_INSTALL_PREFIX=$CNPY_INSTALL_PATH ..
make
make install
```

## Use cnpy from another cmake project

You just need to make sure the directory containg `cnpy-config.cmake` is passed to env variable `CMAKE_PREFIX_PATH`; then `find_package(cnpy)` should be sufficient to use it.

```
export CMAKE_PREFIX_PATH=${CNPY_INSTALL_PATH}/lib/cmake:${CMAKE_PREFIX_PATH}
```

# How to use cnpy from autotools ?

Place the following lines in your .bashrc file (to make sure the `configure` script can safely use m4 macro `PKG_CHECK_MODULES`, which relies on `pkg-config` tool to retrieve compilation flags):

```bash
export CNPY_INSTALL_PATH=/opt/cnpy-0.2.0
export PKG_CONFIG_PATH=$CNPY_INSTALL_PATH/lib/pkgconfig:$PKG_CONFIG_PATH
export LD_LIBRARY_PATH=$CNPY_INSTALL_PATH/lib:$LD_LIBRARY_PATH
```

example config in a `configure.ac` script :
```shell
# ------------------------------------------------------------------------------
# CNPY library configuration
# ------------------------------------------------------------------------------
AC_MSG_CHECKING([whether cnpy sub-package is available using pkg-config detection])
PKG_CHECK_MODULES(CNPY, [cnpy >= 0.2.0],
[
    AC_DEFINE([HAVE_CNPY], [1], [cnpy available])
    enable_cnpy="yes"
],
[
    AC_MSG_WARN("cnpy disabled")
    enable_cnpy="no"
])
AM_CONDITIONAL(HAVE_CNPY, test -n "$CNPY_LIBS")
AC_SUBST([CNPY_CFLAGS])
AC_SUBST([CNPY_LIBS])
AS_IF([test "$enable_cnpy" = "yes"],
[
    CPPFLAGS="$CPPFLAGS $CNPY_CFLAGS"
    LIBS="$LIBS $CNPY_LIBS"
])
```

# Example of use

Create data in C++, and save them into a file :

``` c++
//create random data
std::complex<double>* data = new std::complex<double>[Nx*Ny*Nz];
for(unsigned int i = 0;i < Nx*Ny*Nz;i++) data[i] = std::complex<double>(rand(),rand());

//save it to file
const unsigned int shape[] = {Nz,Ny,Nx};
cnpy::npy_save("arr1.npy",data,shape,3,"w");

```

reload data in python :

``` python
import numpy as np

# reload data and make it a numpy array
data = np.load('arr1.npy')
```
