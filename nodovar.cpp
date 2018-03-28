#include "nodovar.h"
#include <iostream>
#include <string>
#include "blocklist.h"
using std::string;



NodoVar::NodoVar(string var, string valor, string tip, int ini, int fin, string Var_block, string blk, BlockList listaBlock)
{
    if(Var_block =="variable"){
        this->tipo = tip;
        this->valor = valor;
        this->variable = var;
        siguiente = nullptr;
        anterior = nullptr;
     }
    else if(tip == "Tipo struct"){
        this->lista = listaBlock;
        this->inicio = ini;
        this->final = fin;
        this->block = blk;
        this->variable = var;
        this->tipo = "Es struct";
        siguiente = nullptr;
        anterior = nullptr;
    }
    else if(Var_block == "block"){
        this->lista = listaBlock;
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
