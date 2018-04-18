#include "malloc.h"
#include <iostream>

using namespace std;

Malloc::Malloc(int size)
{
finalByte = 0;
mallocPtr = malloc(size);
}
int* Malloc::agregar_int(int x){
    charptr = (char*)mallocPtr;
    ptr = (int*)(charptr+finalByte);
    *ptr = x;
    finalByte += 4;
    return ptr;
    //cout << ptr << endl;
    /*char strAddress[] = "0x00000000";
    sprintf(strAddress, "0x%x", ptr);
    cout << strAddress << endl;*/
}

char* Malloc::agregar_char(char x){
    charptr = (char*)mallocPtr;
    *(charptr+finalByte) = x;
    finalByte += 1;
    return charptr+finalByte;
}
long* Malloc::agregar_long(long x){
    charptr = (char*)mallocPtr;
    longptr = (long*)(charptr+finalByte);
    *longptr = x;
    finalByte += 8;
    return longptr;
}

float* Malloc::agregar_float(float x){
    charptr = (char*)mallocPtr;
    floatptr = (float*)(charptr+finalByte);
    *floatptr = x;
    finalByte += 4;
    return floatptr;
}
double* Malloc::agregar_double(double x){
    charptr = (char*)mallocPtr;
    doubleptr = (double*)(charptr+finalByte);
    *doubleptr = x;
    finalByte += 8;
    return doubleptr;
}
