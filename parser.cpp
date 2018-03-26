#include "parser.h"

#include <string>
#include <fstream>
using namespace std;
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <iostream>
#include "QDebug"
#include "QString"
#include "QFile"
#include "QTextStream"
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>

using std::string;

Parser::Parser()
{

}
void Parser::parse(string codigo){
    codigoCompleto = codigo;
    std::cout<<"----------------------------SE EMPIEZA A PARSERA -----------------------------"<<std::endl;
    writeFile(codigo);
    readFile();
 }

void Parser::writeFile(string codigo){

//    getBlocks(codigo);
    getType(codigo);

    }

void Parser::readFile(){

}
void Parser::getBlocks(string codigo){
    std::cout << "El tamano de mi codigo es: "<<codigo.size() << std::endl;
    struct block b1;
    string status = "block cerrado";
    int i = 0;
    while (i != codigo.size()){

        if (codigo[i] == '{' && status == "block cerrado"){
            std::cout << "Encontro un block abierto en la posicion :"  << i << std::endl;
            *b1.inicio = i;
            status = "block abierto";
             i = i + 1;
             continue ;

        }
        else if (codigo[i] == '{' && status == "block abierto"){
            std::cout << "Encontro un block anidado en :" << i << std::endl;
            i =  i + getBlocksAnidados(codigo.substr( i, codigo.size()));
            std::cout<< "Se reubico mi contador en: " << i << ", el cual contiene: " <<codigo[i]<<std::endl;
            i = i + 1;
            continue ;

        }
        else if(codigo[i]=='}' && status == "block abierto"){
            std::cout << "Cerro un block en la posicion :" << i << std::endl;
            *b1.final = i;
            status = "block cerrado";
            i = i + 1;
            continue ;
        }
        else{
            i =  i + 1;
            continue ;
        }


    }

}

int Parser::getBlocksAnidados(string codigo){
    std::cout<< "se encontro block anidado" << std::endl;
    struct block b1;
    string status = "block cerrado";
    int i = 0;
    while (i != codigo.size()){

        if (codigo[i] == '{' && status == "block cerrado"){

            *b1.inicio = i;
            status = "block abierto";
            i = i + 1;

        }
        else if(codigo[i]=='}' && status == "block abierto"){
            std::cout << "Cerro un block anidado en la posicion :" << i << ", el cual contiene: " <<codigo[i]<< std::endl;
            *b1.final = i;
            break;
        }
        else if(codigo[i]!='}'){
            i = i + 1;
        }
    }
    std::cout<< "EL SUBLOKE ES :"<<std::endl;
    std::cout<<codigo.substr(0,i + 1 )<<std::endl;
    return *b1.final;
}



void Parser::getType(string codigo){
    int i = 0;

    while(i!= codigo.size()){
        if(codigo[i] == 'i'){
            if(codigo.substr(i,4) == "int "){

                string variable1  = getVariable(codigo.substr(i + 4,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 4 + variable1.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+6+variable1.size(),codigo.size()));
                bool verificacion  = verificarTipo("int",valor);
                if(verificacion == true && tieneIgual == true){
                    std::cout<<"Es de tipo int y tiene de variable: "<< variable1<<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;
                }
                else{
                    std::cout<<"HAY UN ERROR DE SINTAXIS EN LA DECLARACION DE LA VARIABLE :" <<variable1<<std::endl;
                }

            }
            i = i +1;
        }
        else if(codigo[i]=='f'){
            if(codigo.substr(i,6) == "float "){

                string variable2  = getVariable(codigo.substr(i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 6 + variable2.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+8+variable2.size(),codigo.size()));
                bool verificacion = verificarTipo("float",valor);
                if(verificacion == true && tieneIgual == true){
                    std::cout<<"Es de tipo float y tiene de variable: "<< variable2<<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;
                }
                else{
                    std::cout<<"HAY UN ERROR DE SINTAXIS EN LA DECLARACION DE LA VARIABLE :" <<variable2<<std::endl;
                }

            }
             i = i +1;
        }
        else if(codigo[i]=='l'){
            if(codigo.substr(i,5) == "long "){

                string variable3  = getVariable(codigo.substr(i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 5 + variable3.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+7+variable3.size(),codigo.size()));
                bool verificacion = verificarTipo("long",valor);
                if(verificacion == true && tieneIgual == true){
                    std::cout<<"Es de tipo long y tiene de variable: "<< variable3 <<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;
                }else{
                    std::cout<<"HAY UN ERROR DE SINTAXIS EN LA DECLARACION DE LA VARIABLE :" <<variable3<<std::endl;
                }


            }
             i = i +1;
        }
        else if(codigo[i]=='d'){
            if(codigo.substr(i,7) == "double "){

                string variable  = getVariable(codigo.substr(i + 7,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 7 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+9+variable.size(),codigo.size()));
                bool verificacion = verificarTipo("double",valor);
                if(verificacion == true && tieneIgual == true){
                     std::cout<<"Es de tipo y tiene de variable: "<< variable <<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;
                }
                else{
                    std::cout<<"HAY UN ERROR DE SINTAXIS EN LA DECLARACION DE LA VARIABLE :" <<variable<<std::endl;
                }


            }
             i = i +1;
        }
        else if(codigo[i]=='c' ){
            if(codigo.substr(i,5) == "char "){

                string variable4  = getVariable(codigo.substr(i + 4,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 5 + variable4.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+7+variable4.size(),codigo.size()));
                bool verificacion = verificarTipo("char",valor);
                if(verificacion == true && tieneIgual == true){
                    std::cout<<"Es de tipo char y tiene de variable: "<< variable4 <<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;
                }
                else{
                    std::cout<<"HAY UN ERROR DE SINTAXIS EN LA DECLARACION DE LA VARIABLE :" <<variable4<<std::endl;
                }

            }
             i = i +1;
        }
        else if(codigo[i]=='s' ){
            if(codigo.substr(i,7) == "struct "){
                string variable5  = getVariable(codigo.substr(i + 6,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + getVariableSize(codigo.substr(i + 7,codigo.size())),codigo.size()));
                string valor = getValor(codigo.substr(i+6+variable5.size(),codigo.size()));
                std::cout<<"Es de tipo struct y tiene de variable: "<< variable5  <<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;
            }
             i = i +1;
        }
        else{
             i = i +1;
        }
    }
}
string Parser::getVariable(string codigo){
    string variable = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    while(codigo[i]!= ' '){
        variable = variable + codigo[i];
        i = i + 1;
    }
    return variable;
}

bool Parser::checkEqualSing(string codigo){

    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    if(codigo[i] == '='){

        return true;
    }
    if(codigo[i]!= '='){

        return false;
    }
}
int Parser::getVariableSize(string codigo){
    string variable = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    while(codigo[i]!= ' '){
        variable = variable + codigo[i];
        i = i + 1;
    }
    return i;
}
string Parser::getValor(string codigo){
    string valor = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    while(codigo[i]!= ' ' && codigo[i]!= ';'){
        valor = valor + codigo[i];
        i = i + 1;
    }
    return valor;
}

bool Parser::verificarTipo(string tipo ,string valor){
    if(tipo == "int"){
        if(typeid (atoi( valor.c_str() )).name() == typeid(9).name()){
            return true;
        }
        else{
            return false;
        }
    }

    if(tipo == "long"){
        std::cout<<typeid(atol(valor.c_str())).name() <<std::endl;
        if(typeid (atol(valor.c_str())).name() == typeid (4294967296).name()){
            return true;
        }
        else{
            return false;
        }
    }
    if(tipo == "float"){
        float f = strtof((valor).c_str(),0);
        std::cout<<typeid(3.5F).name() <<std::endl;
        if(typeid (f).name() == typeid(3.5F).name()){
            return true;
        }
        else{
            return false;
        }
    }
    if(tipo == "double"){
        double d = atof(valor.c_str());

        if(typeid (d).name() == typeid(8.99999999999996).name()){
            return true;
        }
        else{
            return false;
        }
    }
    if(tipo == "char"){

        if(valor[0] == '"' && valor[valor.size()-1] == '"'){
            return true;
        }
        else{
            return false;
        }
    }
}
