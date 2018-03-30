#ifndef BLOCKNODE_H
#define BLOCKNODE_H

#include <iostream>
#include <string>
using std::string;


class BlockNode {
public:
    string variable;
    string tipo;
    string valor;
    int posicion;


    int inicio;
    int final;
    string block;
public:
    BlockNode *siguiente;
    BlockNode *anterior;


    BlockNode (string var, string valor, string tip, int ini, int fin, string Var_block, string blk){

        if(Var_block == "variable"){
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
public:
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



#endif // BLOCKNODE_H
