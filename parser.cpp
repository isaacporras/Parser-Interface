#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <iostream>
#include "QString"
#include "QFile"
#include "QTextStream"
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <ctype.h>
#include <stdio.h>

///
///  Clase parser
///  Parsea todo el codigo
///

using std::string;

Parser::Parser()
{
    *i = 0;
}

///
///  Método -> parse
///  Parametro -> codigo
///  Mete la informacion recibida y enviada a un area de texto
///

QJsonObject Parser::parse(string codigo){
    if(*i>= codigo.size()){
        QJsonObject termino = makeJson("Finish", "Finish", "Finish");
        return termino;
    }
    codigoCompleto = codigo;
    std::cout<<"----------------------------SE EMPIEZA A PARSERA -----------------------------"<<std::endl;
    QJsonObject objeto = writeFile(codigo);
    return objeto;

 }

QJsonObject Parser::writeFile(string codigo){

    QJsonObject objeto = getType(codigo);
    return objeto;

    }

void Parser::readFile(){

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

string Parser::isStructDef(string codigo){
    int i = 0;

    while(codigo[i] == ' '){
        i = i + 1;
    }
    if(codigo[i] == '{'){
        std::cout<<"^^^^^^ SE VA A CREAR UNA ESTRUCTURA ^^^^"  <<std::endl;
        return "Se crea tipo struct";
    }
    if(codigo[i]!= ';'){
        std::cout<<"^^^^^^ SE VA A INSTANCIAR UNA ESTRUCTURA ^^^^"  <<std::endl;
        return "Se inicializa struct";
    }
}


QJsonObject Parser::makeJson(string tip, string val, string var){
    QJsonObject object
        {
            {"Type","NI"},
            {"Value","NI"},
            {"Variable","NI"}
        };

        QVariant tipo(QString::fromStdString(tip));
        QVariant valor(QString::fromStdString(val));
        QVariant variable(QString::fromStdString(var));

        object.insert("Type",tipo.toJsonValue());
        object.insert("Value",valor.toJsonValue());
        object.insert("Variable",variable.toJsonValue());
        return object;
}

string Parser::getPrint_Addr_Value(string codigo){
    string value = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    while(codigo[i]!= ' ' && codigo[i] != ')'){
        value =  value + codigo[i];
        i = i + 1;
    }
    return value;
}
QJsonObject Parser::getType(string codigo){
    do{
        if(*i>= codigo.size()){
            continue;
        }

        while(codigo[*i] == ' '){
            *i = *i + 1;
            continue;
        }

        std::cout << "EL I MIO ES:"<< *i << codigo.substr(*i, 6) << std::endl;

        if(codigo.substr(*i, 6) == "print("){
            std::cout << "Entro en el print" << std::endl;
            string value = getPrint_Addr_Value(codigo.substr(*i + 6, codigo.size()));
            std::cout << "VALUE:"<<value<< std::endl;
            QJsonObject obj = makeJson("Print Request",value,"NULL");
            try{

                int *x = getReubicador(codigo.substr(*i,codigo.size()));

                *i = *i + *x;
            }
                catch(int e){
                    std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                }
            return obj;
        }

        if(codigo.substr(*i, 8) == "getAddr("){
            std::cout << "Entro en el getAddr" << std::endl;
            string value = getPrint_Addr_Value(codigo.substr(*i + 8, codigo.size()));
            std::cout << "VALUE:"<<value<< std::endl;
            QJsonObject obj = makeJson("Addr Request",value,"NULL");
            try{

                int *x = getReubicador(codigo.substr(*i,codigo.size()));

                *i = *i + *x;
            }
                catch(int e){
                    std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                }
            return obj;
        }

        if(codigo[*i] == 'i'){
            if(codigo.substr(*i,4) == "int "){

                string variable  = getVariable(codigo.substr(*i + 4,codigo.size()));

                bool tieneDot = checkDotSing(codigo.substr(*i + 4 + variable.size(),codigo.size()));

                bool tieneIgual = checkEqualSing(codigo.substr(*i + 4 + variable.size(),codigo.size()));

                bool isPointer = esPointer(codigo.substr(*i + 3,codigo.size()));

                if(isPointer == true){

                    string valor = getValor(codigo.substr(*i + 7 +variable.size(),codigo.size()), "int");

                    try{

                        int *x = getReubicador(codigo.substr(*i,codigo.size()));
                        std::cout << "SE REUBICA EN:"<< codigo[*x] << std::endl;
                        *i = *i + *x + 1;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("int pointer",valor,variable);
                    return objeto;
                    continue;

                }
                else if(tieneIgual == true){

                    string valor = getValor(codigo.substr(*i+6+variable.size(),codigo.size()), "int");

                    try{

                        int *x = getReubicador(codigo.substr(*i,codigo.size()));
                        std::cout << "SE REUBICA EN:"<< codigo[*x] << std::endl;
                        *i = *i + *x + 1;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("int",valor,variable);
                    return objeto;
                    continue;

                }


                else if(tieneDot == true){
                    std::cout<<"VARIABLE NO INICIALIZADA"<<std::endl;

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("int","NI",variable);
                    return objeto;
                    continue;
                }



           }
            *i = *i +1;
        }
        else if(codigo[*i]=='f'){
            if(codigo.substr(*i,6) == "float "){

                string variable  = getVariable(codigo.substr(*i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(*i + 6 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(*i + 6 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(*i+8+variable.size(),codigo.size()),"float");
                bool isPointer = esPointer(codigo.substr(*i + 5,codigo.size()));


                if(isPointer == true){
                string valor = getValor(codigo.substr(*i+9+variable.size(),codigo.size()),"float");

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("float pointer",valor,variable);
                    return objeto;
                    continue;
                }
                else if(tieneIgual == true){


                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("float",valor,variable);
                    return objeto;
                    continue;
                }

                else if(tieneDot == true){

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                    }
                    QJsonObject  objeto = makeJson("float","NI",variable);
                    return objeto;
                    continue;
                }



            }

        }
        else if(codigo[*i]=='l'){
            if(codigo.substr(*i,5) == "long "){

                string variable  = getVariable(codigo.substr(*i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(*i + 5 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(*i + 6 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(*i+7+variable.size(),codigo.size()),"long");
                bool isPointer = esPointer(codigo.substr(*i + 4,codigo.size()));

                if(isPointer == true){

                    string valor = getValor(codigo.substr(*i + 8 +variable.size(),codigo.size()), "long");

                    try{

                        int *x = getReubicador(codigo.substr(*i,codigo.size()));
                        std::cout << "SE REUBICA EN:"<< codigo[*x] << std::endl;
                        *i = *i + *x + 1;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("long pointer",valor,variable);
                    return objeto;
                    continue;

            }
                else if(tieneIgual == true){

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("long",valor,variable);
                    return objeto;
                    continue;
                }
                else if(tieneDot == true){

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("long","NI",variable);
                    return objeto;
                    continue;
                }



            }

        }
        else if(codigo[*i]=='d'){
            if(codigo.substr(*i,7) == "double "){

                string variable  = getVariable(codigo.substr(*i + 7,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(*i + 7 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(*i + 6 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(*i+9+variable.size(),codigo.size()),"double");
                bool isPointer = esPointer(codigo.substr(*i + 6,codigo.size()));


                if(isPointer == true){

                    string valor = getValor(codigo.substr(*i + 9 +variable.size(),codigo.size()), "double");

                    try{

                        int *x = getReubicador(codigo.substr(*i,codigo.size()));
                        std::cout << "SE REUBICA EN:"<< codigo[*x] << std::endl;
                        *i = *i + *x + 1;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("double pointer",valor,variable);
                    return objeto;
                    continue;
            }
                else if(tieneIgual == true){


                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("double",valor,variable);
                    return objeto;
                    continue;
                }
                else if(tieneDot == true){

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("double","NI",variable);
                    return objeto;
                    continue;
                }
                else if(isPointer == true){

                    string valor = getValor(codigo.substr(*i + 9 +variable.size(),codigo.size()), "double");

                    try{

                        int *x = getReubicador(codigo.substr(*i,codigo.size()));
                        std::cout << "SE REUBICA EN:"<< codigo[*x] << std::endl;
                        *i = *i + *x + 1;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("double pointer",valor,variable);
                    return objeto;
                    }
            }

        }
        else if(codigo[*i]=='c' ){
            if(codigo.substr(*i,5) == "char "){

                string variable  = getVariable(codigo.substr(*i + 4,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(*i + 5 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(*i + 6 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(*i+7+variable.size(),codigo.size()),"char");
                bool isPointer = esPointer(codigo.substr(*i + 4,codigo.size()));
                if(isPointer == true){

                    string valor = getValor(codigo.substr(*i + 8 +variable.size(),codigo.size()), "char");

                    try{

                        int *x = getReubicador(codigo.substr(*i,codigo.size()));
                        std::cout << "SE REUBICA EN:"<< codigo[*x] << std::endl;
                        *i = *i + *x + 1;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("char pointer",valor,variable);
                    return objeto;
                    continue;
                }

                else if(tieneIgual == true){

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("char",valor,variable);
                    return objeto;
                    continue;
                }
                else if(tieneDot == true){

                    try{
                        int *x = getReubicador(codigo.substr(*i,codigo.size()));

                        *i = *i + *x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    QJsonObject  objeto = makeJson("char","NI",variable);
                    return objeto;
                    continue;
                }

            }

        }

        else if(codigo[*i] == 's' ){


            if(codigo.substr(*i,7) == "struct "){

                string variable  = getVariable(codigo.substr(*i + 6,codigo.size()));
                string *variable3  = (string *)malloc(sizeof(string));
                *variable3 = variable;

                if(isStructDef(codigo.substr(*i + 7 + variable.size(), codigo.size())) == "Se crea tipo struct"){
                    *i = *i + 7 + variable.size() ;
                    struct block bk = analizarStruct(codigo.substr(*i, codigo.size()));

                    QJsonObject  objeto = makeJson("struct definition",std::to_string(*bk.inicio),std::to_string(*bk.final));
                    QVariant var(QString::fromStdString(variable));
                    objeto.insert("Struct name",var.toJsonValue());
                    return objeto;
                    continue;
                }

                else if(isStructDef(codigo.substr(*i + 7 + variable.size(), codigo.size())) == "Se inicializa struct"){
                    string variable  = getVariable(codigo.substr(*i + 7,codigo.size()));
                    string variable2 = getValor(codigo.substr(*i + 7 + variable.size(),codigo.size()),"Struct");
                    std::cout<<"SE ENCONTRO QUE SE QUIERE INICIALIZAR LA SIGUIENTE ESTRUCTURA :"<<variable2<<std::endl;
                    QJsonObject  objeto = makeJson("struct instantiation",variable, variable2);
                    *i = *i + 8 + variable2.size();
                    return objeto;
                    continue;

                }

            }
             i = i +1;
        }
        else if (codigo[*i] == '}'){
            QJsonObject  objeto = makeJson("}","}","}");
           *i = *i + 1 ;
            return objeto;
        }

        else if(codigo[*i] == '{' ){
            QJsonObject  objeto = makeJson("{","{","{");
           *i = *i + 1 ;
            return objeto;


        }


        else if (getVariable(codigo.substr(*i + 1,codigo.size())) != " "&& getVariable(codigo.substr(*i ,codigo.size())).size()!= 0 && (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "int") == false &&
                  (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "long") == false && (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "double") == false &&
                  (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "char") == false && (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "struct") == false
                  && (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "float") == false && (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "int") == false &&
                  (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size()))) == "{") == false && (cutWhiteSpaces(getVariable(codigo.substr(*i + 1 ,codigo.size())))== "}") == false&&
                 (cutWhiteSpaces(codigo.substr(*i + 1 ,5))== "print") == false && (cutWhiteSpaces(codigo.substr(*i + 1 ,7))== "getAddr") == false){

              string variable = getVariable(codigo.substr(*i,codigo.size())) ;
              printf("%s",variable.c_str());
              std::cout << "LA VARIABLE:---------------------------+"<< variable[0] <<"+--------------------------"<<variable.size() <<std::endl;
              bool tieneIgual = checkEqualSing(codigo.substr(*i + variable.size(),codigo.size()));
              std::cout<<(getVariable(codigo.substr(*i ,codigo.size())) == "int")  <<std::endl;
              if (tieneIgual == true){
                  string valor = getValor(codigo.substr(*i  + variable.size(),codigo.size()),"Post Asignation");
                  try{
                      int *x = getReubicador(codigo.substr(*i,codigo.size()));

                      *i = *i + *x;
                  }
                      catch(int e){
                          std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                      }

                  QJsonObject  objeto = makeJson("Post Primitive Asignation",valor,variable);

                  return objeto;

              }
              else if(codigo[*i + variable.size()] == '.'){

                  string atributo = getVariable(codigo.substr(*i + variable.size() + 1   ,codigo.size()));
                  string variable = getVariable(codigo.substr(*i ,codigo.size()));
                  string valor_str = getValor(codigo.substr(*i  + variable.size() + atributo.size() + 1,codigo.size()),"Post Asignation");
                  try{
                      int *x = getReubicador(codigo.substr(*i,codigo.size()));

                      *i = *i + *x;
                  }
                      catch(int e){
                          std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                      }
                  QVariant atr(QString::fromStdString(atributo));
                  QJsonObject  objeto = makeJson("Post Struct Asignation",valor_str,variable);
                  objeto.insert("Atributo",atr.toJsonValue());
                  return objeto;
                  continue;
              }
              else{
                  *i = *i + 1;
              }
        }

        else{
            *i = *i +1;
        }

    }
        while(*i <= codigo.size());
    QJsonObject  objetof = makeJson("Finish","Finish","Finish");

    return objetof;

}
string Parser::cutWhiteSpaces(string codigo){

    std::remove(codigo.begin(), codigo.end(), ' ');
    return codigo;
}
struct block Parser::analizarStruct(string codigo){


    struct block b1;
    string status = "block cerrado";
    int *j = (int*)malloc(sizeof (int));
    *j = 0;
    while (*j != codigo.size()){

        if (codigo[*j] == '{' && status == "block cerrado"){

            *b1.inicio = *i + *j;

            status = "block abierto";
             *j = *j + 1;
             continue ;
        }

        else if(codigo[*j]=='}' && status == "block abierto"){
            std::cout << "Cerro un block en la posicion :" << *j << std::endl;
            std::cout << "Mi bloque final es:"<< std::endl;
            std::cout << codigo.substr(1,*j) << std::endl;
            *b1.final = *i + *j;
            status = "block cerrado";
            *j = *j + 1;
            break;
        }
        else{
            *j =  *j + 1;
            continue ;
        }
    }

    return b1;
}


string Parser::getVariable(string codigo){

    string variable = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    while(codigo[i]!= ' ' && codigo[i]!= ';' && codigo[i]!= '.'){
        variable = variable + codigo[i];
        i = i + 1;
    }
    return variable;
}
bool Parser:: esPointer(string codigo){
    int *j = (int*)malloc(sizeof (int));
    *j =0;

    while(codigo[*j] == ' '){
        *j = *j + 1;
    }
    if(codigo[*j] == '*'){

        return true;
    }
    if(codigo[*j]!= '*'){

        return false;
    }
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

bool Parser::checkDotSing(string codigo){
    int i = 0;

    while(codigo[i] == ' '){
        i = i + 1;
    }
    if(codigo[i] == ';'){

        return true;
    }
    if(codigo[i]!= ';'){

        return false;
    }

}


int *Parser::getVariableSize(string codigo){

    string variable = "";
    int *i  = (int*)malloc(sizeof(int));
    *i = 0;
    while(codigo[*i] == ' '){
        *i = *i + 1;
    }
    *i = 0;
    while(codigo[*i]!= ' '){
        variable = variable + codigo[*i];
        *i = *i + 1;
    }
    return i;
}

string Parser::getValor(string codigo, string tipo){

    string valor = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    if(codigo[i] == '='){
        i = i +1;
        while(codigo[i] == ' '){
            i = i + 1;
        }
    }
    while(codigo[i]!= ';'){
        valor = valor + codigo[i];
        i = i + 1;
    }
    return valor;
}

int *Parser::getReubicador(string codigo){
    int *i = (int *)malloc(sizeof(int));
    *i = 0;
    while(codigo[*i] != ';'){
        *i = *i +1;
    }
    return i;
}


















































