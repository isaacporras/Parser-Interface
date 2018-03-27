#ifndef VARNODE_H
#define VARNODE_H
#include <iostream>
#include <string>
using std::string;


class NodoVar {
public:
    string variable;
    string tipo;
    string valor;
    int posicion;
public:
    NodoVar *siguiente;
    NodoVar *anterior;

    NodoVar (string var, string valor, string tip){
        this->tipo = tip;
        this->valor = valor;
        this->variable = var;
        siguiente = nullptr;
        anterior = nullptr;
    }
    string getVariable(){
        return variable;
    }

public:
    void setPos(int pos){
        this->posicion = pos;
    }
public:
    int getPos(){
        return this->posicion;
    }
public:
    void setVariable(string dat){
        this->variable = dat;
    }
public:
    void setValor(string dat){
        this->valor = dat;
    }

};

#endif // VARNODE_H
