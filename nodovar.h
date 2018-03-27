#ifndef NODOVAR_H
#define NODOVAR_H
#include <iostream>
#include <string>

using std::string;

class NodoVar
{
public:
    NodoVar(string var, string valor, string tip, int ini, int fin, string Var_block, string blk);
public:
    string variable;
    string tipo;
    string valor;
    int posicion;


    int inicio;
    int final;
    string block;
public:
    NodoVar *siguiente;
    NodoVar *anterior;
    string getVariable();
    void setPos(int pos);
    int getPos();
    void setVariable(string dat);
    void setValor(string dat);

};

#endif // NODOVAR_H
