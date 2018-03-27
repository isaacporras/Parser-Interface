#include "varlist.h"
#include <iostream>
#include <string>
#include <iostream>
#include <iostream>
#include <string>
#include "blocklist.h"
using std::string;



VarList::VarList()
{
    primero = ultimo = nullptr;
    ultimo = primero = nullptr;
}

void VarList::ingresarDatoFinalVar(string variable, string valor, string tipo, int inicio,int final,string Var_block,string block, BlockList listaBlock){

        NodoVar *temporal = new NodoVar(variable,valor,tipo,inicio,final,Var_block,block, listaBlock);

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

void VarList::eliminarTodos(){


        this->primero = nullptr;
        this->ultimo = nullptr;


    }
NodoVar *VarList::buscarNodo(string var){
    NodoVar *corredor = primero;
    if (this->primero == 0){
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
void VarList::imprimirListaAlDerecho(){
       std::cout<<"-------------------------------MI LISTA CONTIENE LOS SIGUIENTES ELEMENTOS----------------------"<<std::endl;
       NodoVar *corredor = primero;
       if (primero == 0){
           std::cout << "No hay elementos en la lista" << std::endl;
       }
       else{

           NodoVar *corredor = primero->siguiente;

           primero->setPos(1);
           std::cout << "El elemento es: " << primero->getVariable() <<", y tiene el siguiente valor:"<< primero->valor<< ", y es de tipo:"<< primero->tipo<<std::endl;
           if(primero->getVariable()=="Es Block"){
               primero->lista.imprimirListaAlDerechoBlock();
               std::cout<<"-------------------------------YA NO HAY ELEMENTOS EN MI BLOCK----------------------"<<std::endl;
           }
           while(corredor != primero){
               std::cout << "El elemento es:"<< corredor->getVariable() << ", y tiene el siguiente valor:"<< corredor->valor << ", y es de tipo:"<< corredor->tipo<< std::endl;
               if(corredor->getVariable() =="Es Block"){
                   std::cout<<"MI BLOCK TIENE LOS SIGUIENTES ELEMENTOS"<<std::endl;
                   corredor->lista.imprimirListaAlDerechoBlock();
               }
               corredor = corredor -> siguiente;
           }
       }
   }
