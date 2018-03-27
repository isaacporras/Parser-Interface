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
#include <ctype.h>
#include <stdio.h>
#define ISNUM(X) X >='0' && X <='9'

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
                string valor = getValor(codigo.substr(i+6+variable1.size(),codigo.size()), "int");
                bool verificacion  = verificarTipo("int",valor);
                std::cout<<"Es de tipo int y tiene de variable: "<< variable1<<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;



            }
            i = i +1;
        }
        else if(codigo[i]=='f'){
            if(codigo.substr(i,6) == "float "){

                string variable2  = getVariable(codigo.substr(i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 6 + variable2.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+8+variable2.size(),codigo.size()),"float");
                bool verificacion = verificarTipo("float",valor);
                std::cout<<"Es de tipo float y tiene de variable: "<< variable2<<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;


            }
             i = i +1;
        }
        else if(codigo[i]=='l'){
            if(codigo.substr(i,5) == "long "){

                string variable3  = getVariable(codigo.substr(i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 5 + variable3.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+7+variable3.size(),codigo.size()),"long");
                bool verificacion = verificarTipo("long",valor);
                std::cout<<"Es de tipo long y tiene de variable: "<< variable3 <<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;




            }
             i = i +1;
        }
        else if(codigo[i]=='d'){
            if(codigo.substr(i,7) == "double "){

                string variable  = getVariable(codigo.substr(i + 7,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 7 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+9+variable.size(),codigo.size()),"double");
                bool verificacion = verificarTipo("double",valor);
                std::cout<<"Es de tipo double y tiene de variable: "<< variable <<" tiene igual : " << tieneIgual<<", y un valor de: "<<valor<<std::endl;
            }
             i = i +1;
        }
        else if(codigo[i]=='c' ){
            if(codigo.substr(i,5) == "char "){

                string variable4  = getVariable(codigo.substr(i + 4,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 5 + variable4.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+7+variable4.size(),codigo.size()),"char");
                bool verificacion = verificarTipo("char",valor);
                std::cout<<"Es de tipo char y tiene de variable: "<< variable4 <<" tiene igual : " <<tieneIgual<<", y un valor de: "<<valor<<std::endl;


            }
             i = i +1;
        }
        else if(codigo[i]=='s' ){
            if(codigo.substr(i,7) == "struct "){
                string variable5  = getVariable(codigo.substr(i + 6,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + getVariableSize(codigo.substr(i + 7,codigo.size())),codigo.size()));
                string valor = getValor(codigo.substr(i+6+variable5.size(),codigo.size()),"struct");
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







string Parser::getValor(string codigo, string tipo){
    string valor = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    while(codigo[i]!= ';'){
        valor = valor + codigo[i];
        i = i + 1;
    }





    string valor2 = valor;
   if (valor2.find('.')!= std::string::npos){
       valor2.erase(std::remove(valor2.begin(), valor2.end(), '.'), valor2.end());
   }
   if (valor2.find(',')!= std::string::npos){
       valor.erase(std::remove(valor2.begin(), valor2.end(), ','), valor2.end());
   }



   string estado ="es numero";

   if(tipo == "float" || tipo == "long" || tipo == "double"){
       std::cout<<"EL VALOR 2 ES: "<<valor2 <<std::endl;
       int p = 0;
       while(p != valor2.size()){
           char x  = valor2[p];
           if (!isdigit(x)){
               estado = "no es numero";
               break;
           }
           p = p + 1;
       }
   }
   else{
       int p = 0;
        while(p!= valor.size()){
            char x  = valor[p];
            if (!isdigit(x)){
                estado = "no es numero";
                break;
            }
            p = p + 1;
        }
   }







    if (estado == "es numero"){
        return valor;
    }
    else if (estado == "no es numero"){
        if(tipo =="char"){
            return valor;
        }
        else{
            return analizarValor(valor);
        }


    }
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

        if(typeid (atol(valor.c_str())).name() == typeid (4294967296).name()){
            return true;
        }
        else{
            return false;
        }
    }
    if(tipo == "float"){

        if(typeid (strtof((valor).c_str(),0)).name() == typeid(3.5F).name()){
            return true;
        }
        else{
            return false;
        }
    }
    if(tipo == "double"){
        std:cout<<typeid (atof(valor.c_str())).name()<<std::endl;
        if(typeid (atof(valor.c_str())).name() == typeid(8.99999999999996).name()){
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

string Parser::analizarValor(string valor){

    std::cout<<"SE METIO A ANALIZAR EL VARLOR"<<std::endl;
    if (valor.find('+')!= std::string::npos){
        std::cout<<"ENCONTRO QUE HAY QUE SUMAR"<<std::endl;
        string num1 = valor.substr(0,valor.find('+'));
        std::cout<<"NUM1: |" << num1 <<"|"<<std::endl;

        string num2 = valor.substr(valor.find('+') + 1,valor[valor.size()-1]);
        std::cout<<"NUM2: |" << num2 <<"|"<<std::endl;
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";
        while(p!= num1.size()-1){
            char x  = num1[p];
            std::cout<<"Mi numero esta compuesto por" << x <<std::endl;
            if (!isdigit(x) ){
                std::cout<<"la parte del elemento que no cumplio es:" << x <<std::endl;
                estado_num1 = "no es numero";
                break;
            }
            p = p +1;
        }
        int j = 0;
        while(j != num2.size()){
            char y  = num2[j];
            if (!isdigit(y)){
                std::cout<<"la parte del elemento que no cumplio es:" << y <<std::endl;
                estado_num2= "no es numero";
                break;
            }
            j = j + 1;
        }
        std::cout<<"LOS ESTADOS DE LOS NUMERO SON :"<< estado_num1<<", "<<estado_num2<<std::endl;
        if(estado_num1 == "es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num1.c_str()) + atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            int suma  = (atoi( num1.c_str()) + buscarNum(num2));
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num2.c_str()) + buscarNum(estado_num1));
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){
            int suma = (buscarNum(num2) + buscarNum(num1));
            return to_string(suma);

        }

    }
    else if (valor.find('-')!= std::string::npos){
        std::cout<<"VA A RESTAR"<<std::endl;
        string num1 = valor.substr(0,valor.find('-'));
        std::cout<<"NUM1: |" << num1 <<"|"<<std::endl;

        string num2 = valor.substr(valor.find('-') + 1,valor[valor.size()-1]);
        std::cout<<"NUM2: |" << num2 <<"|"<<std::endl;
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";
        while(p!= num1.size()-1){
            char x  = num1[p];
            std::cout<<"Mi numero esta compuesto por" << x <<std::endl;
            if (!isdigit(x) ){
                std::cout<<"la parte del elemento que no cumplio es:" << x <<std::endl;
                estado_num1 = "no es numero";
                break;
            }
            p = p +1;
        }
        int j = 0;
        while(j != num2.size()){
            char y  = num2[j];
            if (!isdigit(y)){
                std::cout<<"la parte del elemento que no cumplio es:" << y <<std::endl;
                estado_num2= "no es numero";
                break;
            }
            j = j + 1;
        }

        std::cout<<"LOS ESTADOS DE LOS NUMERO SON :"<< estado_num1<<", "<<estado_num2<<std::endl;
        if(estado_num1 == "es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num1.c_str()) - atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            int suma = (atoi( num1.c_str()) - buscarNum(num2));
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num2.c_str()) - buscarNum(num1));
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){
            int suma = (buscarNum(num2) - buscarNum(num1));
            return to_string(suma);

        }
    }
    else if (valor.find('/')!= std::string::npos){
        std::cout<<"VA A DIVIDIR"<<std::endl;
        string num1 = valor.substr(0,valor.find('/'));
        std::cout<<"NUM1: |" << num1 <<"|"<<std::endl;

        string num2 = valor.substr(valor.find('/') + 1,valor[valor.size()-1]);
        std::cout<<"NUM2: |" << num2 <<"|"<<std::endl;
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";
        while(p!= num1.size()-1){
            char x  = num1[p];
            std::cout<<"Mi numero esta compuesto por" << x <<std::endl;
            if (!isdigit(x) ){
                std::cout<<"la parte del elemento que no cumplio es:" << x <<std::endl;
                estado_num1 = "no es numero";
                break;
            }
            p = p +1;
        }
        int j = 0;
        while(j != num2.size()){
            char y  = num2[j];
            if (!isdigit(y)){
                std::cout<<"la parte del elemento que no cumplio es:" << y <<std::endl;
                estado_num2= "no es numero";
                break;
            }
            j = j + 1;
        }

        if(estado_num1 == "es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num1.c_str()) / atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            int suma = (atoi( num1.c_str()) / buscarNum(num2));
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num2.c_str()) / buscarNum(num1));
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){
            int suma = (buscarNum(num2) / buscarNum(num1));
            return to_string(suma);

        }


    }
    else if (valor.find('%')!= std::string::npos){

        string num1 = valor.substr(0,valor.find('+') - 1);
        string num2 = valor.substr(valor.find('+') + 1,valor[valor.size()-1]);
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";
        while(p!= valor.size()){
            char x  = num1[p];
            char y  = num2[p];
            if (!isdigit(x) ){
                estado_num1 = "no es numero";
                break;
            }
            if (!isdigit(x) ){
                estado_num2= "no es numero";
                break;
            }
            p = p + 1;
        }
        if(estado_num1 == "es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num1.c_str()) % atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            int suma = (atoi( num1.c_str()) % buscarNum(num2));
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            int suma = (atoi( num2.c_str()) % buscarNum(num1));
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){
            int suma = (buscarNum(num2) % buscarNum(num1));
            return to_string(suma);

        }
    }
    else{

    }
}


int Parser::buscarNum(string nombre_de_variable){

}






































