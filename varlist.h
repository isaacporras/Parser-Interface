#ifndef VARLIST_H
#define VARLIST_H

//
// Created by Isaac  Porras  on 24/2/18.
//
#include <iostream>
#include <string>
#include <iostream>
#include "varnode.h"


class VarList {
private:
    NodoVar *primero;
    NodoVar *ultimo;
    int largo = 0;

    //DEFINICION DE LA CLASE

public:
    VarList(){
        primero = ultimo = nullptr;
        ultimo = primero = nullptr;
    }


    //INGRESAR AL FINAL

public:
    void ingresarDatoFinal(string variable, string valor, string tipo){

        NodoVar *temporal = new NodoVar(variable,valor, tipo);

        if( primero == 0 ){

            primero = temporal;
            ultimo = temporal;
            temporal->siguiente = temporal;
            temporal->anterior = temporal;
            largo = largo + 1;
        }
        else {

            ultimo->siguiente = temporal;
            temporal-> anterior = ultimo;
            ultimo = temporal;
            temporal->siguiente = primero;
            primero->anterior = temporal;
            largo = largo+1;
        }

        NodoVar *corredor = primero->siguiente;
        int contador = 2;

        primero->setPos(1);

        while(corredor != primero){
            corredor->setPos(contador);
            contador = contador + 1;
            corredor = corredor -> siguiente;
        }

    }


    // ELIMINAR POR POSICION

public:
    void eliminarTodos(){


        this->primero = nullptr;
        this->ultimo = nullptr;


    }


    // IMPRIMIR LISTA AL DERECHO

public:
    void imprimirListaAlDerecho(){
        NodoVar *corredor = primero;
        if (primero == 0){
            std::cout << "No hay elementos en la lista" << std::endl;
        }
        else{

            NodoVar *corredor = primero->siguiente;
            int contador = 2;

            primero->setPos(1);
            std::cout << "El elemento es: " << primero->getVariable() <<", y tiene el siguiente valor:"<< primero->valor<< ", y es de tipo:"<< primero->tipo<<std::endl;
            while(corredor != primero){
                std::cout << "El elemento es:"<< corredor->getVariable() << ", y tiene el siguiente valor:"<< corredor->valor << ", y es de tipo:"<< corredor->tipo<< std::endl;
                contador = contador + 1;
                corredor = corredor -> siguiente;
            }
        }
    }
public:
    NodoVar *buscarNodo(string var){
        NodoVar *corredor = primero;
        if (primero == 0){
            std::cout << "No hay elementos en la lista" << std::endl;
        }
        else{

            NodoVar *corredor = primero->siguiente;
            int contador = 2;

            primero->setPos(1);
            if(primero->variable == var){
                return primero;
            }
            while(corredor != primero){
                if(corredor->variable == var){
                    return corredor;
                }
                contador = contador + 1;
                corredor = corredor -> siguiente;
            }
        }
    }

};



#endif // VARLIST_H
