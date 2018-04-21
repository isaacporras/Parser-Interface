#ifndef MALLOC_H
#define MALLOC_H

///
/// Clase Malloc
/// Encargada de la administración de memoria en la RAM
///

class Malloc
{
public:
    Malloc(int size);    
    int* agregar_int(int x);
    char* agregar_char(char x);
    long* agregar_long(long x);
    float* agregar_float(float x);
    double* agregar_double(double x);

private:

    ///
    /// mallocPtr
    ///
    /// Espacio de memoria asignada al Server
    ///
    ///
    /// mallocPtr, charptr, longptr, floatptr, doubleptr
    ///
    /// Punteros para la creación de variables en el mallocPtr
    ///
    ///
    /// finalbyte
    ///
    /// Posición donde se encuentra memoria libre

    void* mallocPtr;
    int* ptr;
    char* charptr;
    long* longptr;
    float* floatptr;
    double* doubleptr;
    int finalByte;
};

#endif // MALLOC_H
