#ifndef MALLOC_H
#define MALLOC_H


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
    void* mallocPtr;
    int* ptr;
    char* charptr;
    long* longptr;
    float* floatptr;
    double* doubleptr;
    int finalByte;
};

#endif // MALLOC_H
