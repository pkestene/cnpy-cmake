/* g++ -o example example.cpp cnpy.cpp -lz */

#include"cnpy.h"
#include<complex>
#include<cstdlib>
#include<iostream>
#include<map>
#include<string>

const unsigned int Nx = 128;
const unsigned int Ny = 64;
const unsigned int Nz = 32;

int main()
{
    //set random seed so that result is reproducible (for testing)
    srand(0);
    //create random data
    std::complex<double>* data = new std::complex<double>[Nx*Ny*Nz];
    for(unsigned int i = 0;i < Nx*Ny*Nz;i++) data[i] = std::complex<double>(rand(),rand());

    //save it to file
    const unsigned int shape[] = {Nz,Ny,Nx};
    cnpy::npy_save("arr1.npy",data,shape,3,"w");

    //load it into a new array
    cnpy::NpyArray arr = cnpy::npy_load("arr1.npy");
    std::complex<double>* loaded_data = arr.data<std::complex<double>>();
    
    //make sure the loaded data matches the saved data
    assert(arr.word_size == sizeof(std::complex<double>));
    assert(arr.shape.size() == 3 && arr.shape[0] == Nz && arr.shape[1] == Ny && arr.shape[2] == Nx);
    for(unsigned int i = 0; i < Nx*Ny*Nz;i++) assert(data[i] == loaded_data[i]);

    //append the same data to file
    //npy array on file now has shape (Nz+Nz,Ny,Nx)
    cnpy::npy_save("arr1.npy",data,shape,3,"a");


    //now write to an npz file
    //non-array variables are treated as 1D arrays with 1 element
    double myVar1 = 1.2;
    std::string myVar2 = "abc";
    unsigned int shape1[] = {1};
    unsigned int shape2[] = {3};
    cnpy::npz_save("out.npz","myVar1",&myVar1,shape1,1,"w"); //"w" overwrites any existing file
    cnpy::npz_save("out.npz","myVar2",myVar2.c_str(),shape2,1,"a"); //"a" appends to the file we created above
    cnpy::npz_save("out.npz","arr1",data,shape,3,"a"); //"a" appends to the file we created above

    //load a single var from the npz file
    cnpy::NpyArray arr2 = cnpy::npz_load("out.npz","arr1");

    //load the entire npz file
    cnpy::npz_t my_npz = cnpy::npz_load("out.npz");

    //check that the loaded myVar1 matches myVar1
    cnpy::NpyArray arr_mv1 = my_npz["myVar1"];
    double* mv1 = arr_mv1.data<double>();
    assert(arr_mv1.shape.size() == 1 && arr_mv1.shape[0] == 1);
    assert(mv1[0] == myVar1);

    //cleanup: note that we are responsible for deleting all loaded data
    delete[] data;
}
