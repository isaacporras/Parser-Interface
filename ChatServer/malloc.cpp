#include "malloc.h"
#include <iostream>

///
/// Clase Malloc
/// Encargada de la administración de memoria en la RAM
///

using namespace std;

Malloc::Malloc(int size)

{
finalByte = 0;
mallocPtr = malloc(size);
}

///
///  Método -> agregar_int
///  Parámetro -> x
///  Asigna variables tipo Int en la memoria RAM y devuelve un puntero con su dirección en memoria
///

int* Malloc::agregar_int(int x){
    charptr = (char*)mallocPtr;
    ptr = (int*)(charptr+finalByte);
    *ptr = x;
    finalByte += 4;
    return ptr;
}

///
///  Método -> agregar_char
///  Parámetro -> x
///  Asigna variables tipo Char en la memoria RAM y devuelve un puntero con su dirección en memoria
///

char* Malloc::agregar_char(char x){
    charptr = (char*)mallocPtr;
    *(charptr+finalByte) = x;
    finalByte += 1;
    return charptr+finalByte-1;
}

///
///  Método -> agregar_long
///  Parámetro -> x
///  Asigna variables tipo Long en la memoria RAM y devuelve un puntero con su dirección en memoria
///

long* Malloc::agregar_long(long x){
    charptr = (char*)mallocPtr;
    longptr = (long*)(charptr+finalByte);
    *longptr = x;
    finalByte += 8;
    return longptr;
}

///
///  Método -> agregar_float
///  Parámetro -> x
///  Asigna variables tipo Float en la memoria RAM y devuelve un puntero con su dirección en memoria
///

float* Malloc::agregar_float(float x){
    charptr = (char*)mallocPtr;
    floatptr = (float*)(charptr+finalByte);
    *floatptr = x;
    finalByte += 4;
    return floatptr;
}

///
///  Método -> agregar_double
///  Parámetro -> x
///  Asigna variables tipo Double en la memoria RAM y devuelve un puntero con su dirección en memoria
///

double* Malloc::agregar_double(double x){
    charptr = (char*)mallocPtr;
    doubleptr = (double*)(charptr+finalByte);
    *doubleptr = x;
    finalByte += 8;
    return doubleptr;
}
