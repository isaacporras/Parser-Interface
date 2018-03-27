#ifndef VARLIST_H
#define VARLIST_H

#include <string>
#include <iostream>
#include <string>
#include "nodovar.h"
using std::string;

class VarList
{
public:
    VarList();
public:
    NodoVar *primero;
    NodoVar *ultimo;
    int largo = 0;
    void ingresarDatoFinalVar(string variable, string valor, string tipo, int inicio,int final,string Var_block,string block);
    void eliminarTodos();
    void imprimirListaAlDerecho();
    NodoVar *buscarNodo(string var);
};

#endif // VARLIST_H
