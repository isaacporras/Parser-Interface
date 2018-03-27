#include "nodovar.h"
#include <iostream>
#include <string>
using std::string;



NodoVar::NodoVar(string var, string valor, string tip, int ini, int fin, string Var_block, string blk)
{
    if(Var_block =="variable"){
        this->tipo = tip;
        this->valor = valor;
        this->variable = var;
        siguiente = nullptr;
        anterior = nullptr;
     }
    else if(Var_block == "block"){
        this->inicio = ini;
        this->final = fin;
        this->block = blk;
        this->variable = "Es Block";
        siguiente = nullptr;
        anterior = nullptr;
    }

}
string NodoVar::getVariable(){
    return variable;
}
void NodoVar::setPos(int pos){
        this->posicion = pos;
}
int NodoVar::getPos(){
        return this->posicion;
}
void NodoVar::setVariable(string dat){
        this->variable = dat;
}
void NodoVar::setValor(string dat){
        this->valor = dat;
    }
