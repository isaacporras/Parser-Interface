#include "varlist.h"
#include <iostream>
#include <string>
#include <iostream>
#include <iostream>
#include <string>
#include "blocklist.h"
#include "QJsonArray"
#include "QJsonObject"
#include "QJsonDocument"
#include "qdebug.h"

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
        this->largo = 0;

    }
NodoVar *VarList::buscarNodo(string var){

    std::cout<<"SE METIO A BUSCAR EL NODO"<<std::endl;
    if (this->primero == 0){
        std::cout << "No hay elementos en la lista" << std::endl;
        BlockList def_list;
        NodoVar *nodo = new NodoVar("NO SE ENCONTRO","NO SE ENCONTRO","NO SE ENCONTRO",0,0,"","",def_list);
        nodo->setVariable("NO SE ENCONTRO");
        return nodo;
    }
    else{

        NodoVar *corredor = primero->siguiente;
        int contador = 2;
        primero->setPos(1);
        if(primero->variable == var){
            return primero;
        }
        while(corredor != primero){
//            std::cout<<"LA VARIABLE DE MI NODO ES: " << corredor->variable << " = " << corredor->valor<<std::endl;
            if(corredor->variable == var){
                std::cout<<"EL DATO ENCONTRADO ES: " << corredor->variable << " = " << corredor->valor<<std::endl;
                return corredor;
            }
            contador = contador + 1;
            corredor = corredor -> siguiente;
        }
        BlockList def_list;
        NodoVar *nodo = new NodoVar("NO SE ENCONTRO","NO SE ENCONTRO","NO SE ENCONTRO",0,0,"","",def_list);
        nodo->setVariable("NO SE ENCONTRO");
        return nodo;

    }
}

void VarList::imprimirListaAlDerecho(){
    QJsonObject object
    {
        {"Type","NI"},
        {"Value","NI"},
        {"Variable","NI"}
    };

    object.insert("Type","funciono jeje");
    QJsonDocument doc(object);
    QByteArray bytes = doc.toJson();
    const char* charString= bytes.data();
     std::string someString(charString);

    std::cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<bytes.data()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
    std::cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<object.find("Type").value().toString().toStdString()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
    object.find("Type").value().toString();
       std::cout<<"-------------------------------MI LISTA CONTIENE LOS SIGUIENTES ELEMENTOS----------------------"<<std::endl;

       if (this->primero == 0){
           std::cout << "No hay elementos en la lista" << std::endl;
       }

       else{

           NodoVar *corredor = primero->siguiente;

           primero->setPos(1);
           std::cout << "El elemento es: " << primero->getVariable() <<", y tiene el siguiente valor:"<< primero->valor<< ", y es de tipo:"<< primero->tipo<<std::endl;

           if(primero->getVariable() =="Es Block" || primero->tipo == "Tipo Struct Definition"){

               primero->lista.imprimirListaAlDerechoBlock();
               std::cout<<"-------------------------------YA NO HAY ELEMENTOS EN MI BLOCK----------------------"<<std::endl;

           }

           while(corredor != primero){

               std::cout << "El elemento es:"<< corredor->getVariable() << ", y tiene el siguiente valor:"<< corredor->valor << ", y es de tipo:"<< corredor->tipo<< std::endl;
               if(corredor->getVariable() == "Es Block"|| corredor->tipo == "Tipo Struct Definition" || corredor->tipo == "Variable Struct"){
                   std::cout<<"MI BLOCK TIENE LOS SIGUIENTES ELEMENTOS"<<std::endl;
                   corredor->lista.imprimirListaAlDerechoBlock();
               }
               corredor = corredor -> siguiente;
           }
       }
   }
