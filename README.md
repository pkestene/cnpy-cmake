# What is cnpy ?

Simple utility class to dump data array into a .npy file
which is directly readable by numpy/python.

This utility is written by Carl Rogers: https://github.com/rogersce/cnpy

The original code has been slightly refactored (cmake) to provide a pkgconfig file and an installation process.

# example of use

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

