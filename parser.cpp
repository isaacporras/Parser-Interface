#include "parser.h"

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
#include "nodovar.h"


using std::string;

Parser::Parser()
{

}
void Parser::parse(string codigo){

    codigoCompleto = codigo;
    std::cout<<"----------------------------SE EMPIEZA A PARSERA -----------------------------"<<std::endl;
    writeFile(codigo);
    imprimirVariables();
 }

void Parser::writeFile(string codigo){
    lista_valores.eliminarTodos();
    getType(codigo, lista_valores);

    }

void Parser::readFile(){

}

void Parser::imprimirVariables(){
    std::cout<<"********************************************************************************"<<std::endl;
    lista_valores.imprimirListaAlDerecho();
    std::cout<<"********************************************************************************"<<std::endl;
}


int Parser::getBlocks(string codigo, VarList *list){

    std::cout<<"ENCONTRO EL SIGUIENTE BLOQUE"<<std::endl;
    std::cout<<codigo<<std::endl;

    struct block b1;
    string status = "block cerrado";
    int i = 0;
    while (i != codigo.size()){

        if (codigo[i] == '{' && status == "block cerrado"){

            *b1.inicio = i;
            status = "block abierto";
             i = i + 1;
             continue ;
        }
        else if (codigo[i] == '{' && status == "block abierto"){

            i =  i + getBlocksAnidados(codigo.substr( i, codigo.size()));

            std::cout<< "Se reubico mi contador en: " << i << ", el cual contiene: " <<codigo[i]<<std::endl;
            i = i + 1;
            continue ;

        }
        else if(codigo[i]=='}' && status == "block abierto"){
            std::cout << "Cerro un block en la posicion :" << i << std::endl;
            std::cout << "Mi bloque final es:"<< std::endl;
            std::cout << codigo.substr(1,i) << std::endl;
            *b1.final = i;
            status = "block cerrado";
            i = i + 1;
            break;
        }
        else{
            i =  i + 1;
            continue ;
        }
    }

    VarList provicional;
    VarList listaBlock1 = getType(codigo.substr(*b1.inicio + 1,*b1.final + 1 ), provicional);
    listaBlock1.imprimirListaAlDerecho();

    BlockList listaBlock2 = copyList(&listaBlock1);

    listaBlock2.imprimirListaAlDerechoBlock();
    list->ingresarDatoFinalVar("Tipo block", "Tipo block","Tipo Block",*b1.inicio,*b1.final,"block",codigo.substr(*b1.inicio, *b1.final + 1),listaBlock2);

    return *b1.final;

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

BlockList Parser::copyList(VarList *listaVar){

    BlockList lista;
    NodoVar *corredor  = listaVar->primero;
    lista.ingresarDatoFinalBlock(corredor->variable,corredor->valor, corredor->tipo,-10,-10,"variable","Tipo Variable");
    corredor = corredor->siguiente;
    while (corredor != listaVar->primero) {

        lista.ingresarDatoFinalBlock(corredor->variable,corredor->valor, corredor->tipo,-10,-10,"variable","Tipo Variable");
        corredor = corredor->siguiente;
    }
    return lista;
}


VarList Parser::getType(string codigo, VarList &lista_var){
    int i = 0;

    while(i!= codigo.size()){

        if(codigo[i] == 'i'){
            if(codigo.substr(i,4) == "int "){

                string variable  = getVariable(codigo.substr(i + 4,codigo.size()));
                std::cout<<"LA VARIABLE"<< variable<<std::endl;
                std::cout<<"MI CODIGO ES: "<<codigo.substr(i + 3 + variable.size(),codigo.size())<<std::endl;
                bool tieneDot = checkDotSing(codigo.substr(i + 4 + variable.size(),codigo.size()));

                bool tieneIgual = checkEqualSing(codigo.substr(i + 4 + variable.size(),codigo.size()));



                BlockList lista2;

                if(tieneIgual == true){

                    string valor = getValor(codigo.substr(i+6+variable.size(),codigo.size()), "int", lista_var);
                    bool verificacion  = verificarTipo("int",valor);

                    if (valor == "NO SE ENCONTRO"){
                        std::cout<<"NO SE ENCONTRO LA VARIABLE 2.0"<<std::endl;

                        lista_var.ingresarDatoFinalVar(variable,valor, "int",-10,-10,"variable","Tipo Variable",lista2);
                        i = i + 1;

                    }
                    else{

                    lista_var.ingresarDatoFinalVar(variable,valor, "int",-10,-10,"variable","Tipo Variable",lista2);
                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                    }
                }

                else if(tieneDot == true){
                    std::cout<<"VARIABLE NO INICIALIZADA"<<std::endl;
                    lista_var.ingresarDatoFinalVar(variable,"No se ha inicializado", "int",-10,-10,"variable","Tipo Variable",lista2);
                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }


           }
            i = i +1;
        }
        else if(codigo[i]=='f'){
            if(codigo.substr(i,6) == "float "){

                string variable  = getVariable(codigo.substr(i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 6 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(i + 6 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+8+variable.size(),codigo.size()),"float", lista_var);
                BlockList lista2;
                if (valor == "NO SE ENCONTRO"){
                    std::cout<<"NO SE ENCONTRO LA VARIABLE"<<std::endl;
                    lista_var.ingresarDatoFinalVar(variable,valor,"float",-10,-10,"variable","Tipo Variable",lista2);
                    i = i + 1;
                }
                bool verificacion = verificarTipo("float",valor);

                if(tieneIgual == true){
                    lista_var.ingresarDatoFinalVar(variable,valor,"float",-10,-10,"variable","Tipo Variable",lista2);

                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }
                else if(tieneDot == true){
                    lista_var.ingresarDatoFinalVar(variable,"No se ha inicializado","float",-10,-10,"variable","Tipo Variable",lista2);
                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }

            }
             i = i +1;
        }
        else if(codigo[i]=='l'){
            if(codigo.substr(i,5) == "long "){

                string variable  = getVariable(codigo.substr(i + 5,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 5 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(i + 6 + variable.size(),codigo.size()));

                BlockList lista2;
                if(tieneIgual == true){
                    string valor = getValor(codigo.substr(i+7+variable.size(),codigo.size()),"long", lista_var);
                    bool verificacion = verificarTipo("long",valor);

                    if (valor == "NO SE ENCONTRO"){
                        std::cout<<"NO SE ENCONTRO LA VARIABLE"<<std::endl;
                        lista_var.ingresarDatoFinalVar(variable,valor,"long",-10,-10,"variable","Tipo Variable", lista2);
                        i = i + 1;
                    }
                    lista_var.ingresarDatoFinalVar(variable,valor,"long",-10,-10,"variable","Tipo Variable", lista2);

                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }
                else if(tieneDot == true){
                    lista_var.ingresarDatoFinalVar(variable,"No se ha inicializado","long",-10,-10,"variable","Tipo Variable", lista2);
                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }


            }
             i = i +1;
        }
        else if(codigo[i]=='d'){
            if(codigo.substr(i,7) == "double "){

                string variable  = getVariable(codigo.substr(i + 7,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 7 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(i + 6 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+9+variable.size(),codigo.size()),"double",lista_var);
                BlockList lista2;
                if (valor == "NO SE ENCONTRO"){
                    std::cout<<"NO SE ENCONTRO LA VARIABLE"<<std::endl;
                    lista_var.ingresarDatoFinalVar(variable,valor,"double",-10,-10,"variable","Tipo Variable", lista2);
                    i = i + 1;
                }
                bool verificacion = verificarTipo("double",valor);

                if(tieneIgual == true){
                    lista_var.ingresarDatoFinalVar(variable,valor,"double",-10,-10,"variable","Tipo Variable", lista2);

                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }
                else if(tieneDot == true){
                    lista_var.ingresarDatoFinalVar(variable,valor,"No se ha inicializado",-10,-10,"variable","Tipo Variable", lista2);
                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }
            }
             i = i +1;
        }
        else if(codigo[i]=='c'){
            if(codigo.substr(i,5) == "char "){

                string variable  = getVariable(codigo.substr(i + 4,codigo.size()));
                bool tieneIgual = checkEqualSing(codigo.substr(i + 5 + variable.size(),codigo.size()));
                bool tieneDot = checkDotSing(codigo.substr(i + 6 + variable.size(),codigo.size()));
                string valor = getValor(codigo.substr(i+7+variable.size(),codigo.size()),"char", lista_var);
                BlockList lista2;
                if (valor == "NO SE ENCONTRO"){
                    std::cout<<"NO SE ENCONTRO LA VARIABLE"<<std::endl;
                    lista_var.ingresarDatoFinalVar(variable,valor, "char",-10,-10,"variable","Tipo Variable", lista2);
                    i = i + 1;
                }
                bool verificacion = verificarTipo("char",valor);

                if(tieneIgual == true){
                    lista_var.ingresarDatoFinalVar(variable,valor, "char",-10,-10,"variable","Tipo Variable", lista2);

                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }
                else if(tieneDot == true){
                    lista_var.ingresarDatoFinalVar(variable,"No se ha inicializado", "char",-10,-10,"variable","Tipo Variable", lista2);
                    try{
                        int x = *getReubicador(codigo.substr(i,codigo.size()));
                        std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                        i = i + x;
                    }
                        catch(int e){
                            std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                        }
                }
            }
             i = i + 1;
        }
        else if(codigo[i] == 's' ){

            if(codigo.substr(i,7) == "struct "){

                string variable  = getVariable(codigo.substr(i + 6,codigo.size()));
                string *variable3  = (string *)malloc(sizeof(string));
                *variable3 = variable;
                std::cout<<"LA VARIABLE DE DE MI STRUCT  ES :" << variable <<"555555555555555555555555555555555555555555555555555555555555555555555555555555555"<<std::endl;
                if(isStructDef(codigo.substr(i + 7 + variable.size(), codigo.size())) == "Se crea tipo struct"){
                    std::cout<< codigo.substr(i+ 7, codigo.size()) <<std::endl;
                    i = i + analizarStruct(codigo.substr(i + 7 + variable.size(), codigo.size()),&lista_var, variable);
                }

                if(isStructDef(codigo.substr(i + 7 + variable.size(), codigo.size())) == "Se inicializa struct"){
                    string variable  = getVariable(codigo.substr(i + 7,codigo.size()));

                    if(lista_var.buscarNodo(variable)->variable != "NO SE ENCONTRO"){
                        BlockList listaBlock;
                        BlockList listaBlock2  = lista_var.buscarNodo(variable)->lista;
                        BlockList listaBlockFinal = copyStructList(listaBlock2,listaBlock);

                        string variable2 = getValor(codigo.substr(i + 7 + variable.size(),codigo.size()),"Struct", lista_var);
                        std::cout<<"SE ENCONTRO QUE SE QUIERE INICIALIZAR LA SIGUIENTE ESTRUCTURA :"<<variable2<<std::endl;
                        lista_var.ingresarDatoFinalVar(variable2, *variable3,"Variable Struct",-10,-10,"Variable Struct","Variable Struct",listaBlockFinal);
                        i = i + 8 + variable2.size();
                    }

                }
            }
             i = i +1;
        }

        else if(codigo[i]=='{' ){

            i  =  i + getBlocks(codigo.substr(i, codigo.size()),&lista_var);

        }




        else if (buscarNum(getVariable(codigo.substr(i ,codigo.size())),lista_var)->variable != "NO SE ENCONTRO"){
            std::cout<< "ENCONTRO UNA ASIGNACION DE VARIABLE"<<std::endl;

            string variable = getVariable(codigo.substr(i ,codigo.size())); //Da el nombre de la variable
            NodoVar *nodox = buscarNum(getVariable(codigo.substr(i ,codigo.size())),lista_var);
            string variable_dentro_lista = getVariable(codigo.substr(i + nodox->variable.size() + 1   ,codigo.size()));




            string valor = getValor(codigo.substr(i  + variable.size() + variable_dentro_lista.size() + 3,codigo.size()),nodox->tipo, lista_var);


            if(nodox->tipo == "Variable Struct" && codigo[i + variable.size()] == '.'){
                std::cout<<"FUNCIONOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"<<std::endl;
                nodox->lista.imprimirListaAlDerechoBlock();
                BlockNode *nodo_dentro_lista = nodox->lista.buscarNodo(variable_dentro_lista);
                std::cout<<"NODO_DENTRO_LISTA: "<<nodo_dentro_lista->valor<<std::endl;
                nodo_dentro_lista->valor = valor;
                try{
                    int x = *getReubicador(codigo.substr(i,codigo.size()));
                    std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                    i = i + x;
                }
                    catch(int e){
                        std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                    }
            }

            else if (nodox->tipo != "Variable Struct"){
                NodoVar *nodox = buscarNum(getVariable(codigo.substr(i ,codigo.size())),lista_var);
                valor = getValor(codigo.substr(i + nodox->variable.size() + 2,codigo.size()),nodox->tipo, lista_var);
                nodox->valor = valor;

                try{
                    int x = *getReubicador(codigo.substr(i,codigo.size()));
                    std::cout<< "Se reubico mi contador en: "<<codigo[i + x ]<<std::endl;
                    i = i + x;
                }
                catch(int e){
                    std::cout<< "NO SE PUDO REUBICAR"<<std::endl;
                }
            }


        }
        else{
            i = i +1;
        }
   }
    return lista_var;
}

BlockList Parser::copyStructList(BlockList lista1, BlockList lista2){
        if(lista1.largo == 0){
            return lista2;
        }

    BlockNode *corredor  = lista1.primero;
    lista2.ingresarDatoFinalBlock(corredor->variable,corredor->valor, corredor->tipo,-10,-10,"variable","Tipo Variable");
    corredor = corredor->siguiente;
    while (corredor != lista1.primero) {

        lista2.ingresarDatoFinalBlock(corredor->variable,corredor->valor, corredor->tipo,-10,-10,"variable","Tipo Variable");
        corredor = corredor->siguiente;
    }
    return lista2;

}


int Parser::analizarStruct(string codigo, VarList *list, string variable){

    std::cout<<"ENCONTRO EL SIGUIENTE STRUCT"<<std::endl;
    std::cout<<codigo<<std::endl;

    struct block b1;
    string status = "block cerrado";
    int i = 0;
    while (i != codigo.size()){

        if (codigo[i] == '{' && status == "block cerrado"){

            *b1.inicio = i;
            status = "block abierto";
             i = i + 1;
             continue ;
        }
        else if (codigo[i] == '{' && status == "block abierto"){

            i =  i + getBlocksAnidados(codigo.substr( i, codigo.size()));
            std::cout<< "Se reubico mi contador en: " << i << ", el cual contiene: " <<codigo[i]<<std::endl;
            i = i + 1;
            continue ;

        }
        else if(codigo[i]=='}' && status == "block abierto"){
            std::cout << "Cerro un block en la posicion :" << i << std::endl;
            std::cout << "Mi bloque final es:"<< std::endl;
            std::cout << codigo.substr(1,i) << std::endl;
            *b1.final = i;
            status = "block cerrado";
            i = i + 1;
            break;
        }
        else{
            i =  i + 1;
            continue ;
        }
    }

    VarList provicional;

    VarList listaBlock1 = getType(codigo.substr(*b1.inicio + 1,*b1.final + 1 ), provicional);
    listaBlock1.imprimirListaAlDerecho();

    BlockList listaBlock2 = copyList(&listaBlock1);
    list->ingresarDatoFinalVar(variable, "Tipo Struct Definition","Tipo Struct Definition",*b1.inicio,*b1.final,"Tipo Struct Definition",codigo.substr(*b1.inicio, *b1.final + 1),listaBlock2);

    return *b1.final;
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

string Parser::getValor(string codigo, string tipo, VarList lista_Var){

    string valor = "";
    int i = 0;
    while(codigo[i] == ' '){
        i = i + 1;
    }
    while(codigo[i]!= ';'){
        valor = valor + codigo[i];
        i = i + 1;
    }

    if(tipo == "Struct" || tipo == "Variable Struct"){
        return valor;
    }

    string valor2 = valor;
   if (valor2.find('.')!= std::string::npos){
       valor2.erase(std::remove(valor2.begin(), valor2.end(), '.'), valor2.end());
   }
   if (valor2.find(',')!= std::string::npos){
       valor.erase(std::remove(valor2.begin(), valor2.end(), ','), valor2.end());
   }



   string estado = "es numero";

   if(tipo == "float" || tipo == "long" || tipo == "double"){

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
        if(tipo == "char"){

            return valor;
        }
        else{

            return analizarValor(valor, lista_Var);
        }


    }
}

int *Parser::getReubicador(string codigo){
    int *i = (int *)malloc(sizeof(int));
    *i = 0;
    while(codigo[*i] != ';'){
        *i = *i +1;
    }
    return i;
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

        if(typeid (atol(valor.c_str())).name() == typeid(4294967296).name()){
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





string Parser::analizarValor(string valor, VarList listaVar){

    std::cout<<"++++++++++++++++++++++++++++++++++   se metio a analizar con :" <<valor<<" ++++++++++++++++++++++++++++++++++++"<<std::endl;
    listaVar.imprimirListaAlDerecho();
    valor= valor + ";";

    if (valor.find('+')!= std::string::npos){

        std::cout<<"SE METIO A SUMAR :" <<valor<<std::endl;
        string num1 = getNumbers(valor.substr(0,valor.find('+') + 1));

        string num2 = getNumbers(valor.substr(valor.find('+') + 1, valor.size()));
        std::cout<<"num1 = "<<num1<<", num2 = "<<num2 <<std::endl;
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";

        while(p!= num1.size()){
            char x  = num1[p];
            std::cout<<"EL CARACTER A EVALUAR ES: "<<x<<std::endl;
            if (!isdigit(x) ){

                estado_num1 = "no es numero";
                break;
            }
            p = p +1;
        }
        int j = 0;
        while(j != num2.size()){
            char y  = num2[j];
            if (!isdigit(y)){

                estado_num2= "no es numero";
                break;
            }
            j = j + 1;
        }
        std::cout<<"LOS ESTADOS DE MI NUMERO SON: "<<estado_num1 <<", " << estado_num2<<std::endl;


        if(estado_num1 == "es numero" && estado_num2 == "es numero"){
            NodoVar *nodo = buscarNum(num1,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            std::cout<<numeroBuscado << std::endl;
            int suma = (atoi( num1.c_str()) + atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            NodoVar *nodo = buscarNum(num2,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma  = (atoi( num1.c_str()) + numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            NodoVar *nodo = buscarNum(num1,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (atoi( num2.c_str()) + numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){

            NodoVar *nodo1 = buscarNum(num1,  listaVar);
            int numeroBuscado1 = obtenerNumero(nodo1);
            NodoVar *nodo2 = buscarNum(num2,  listaVar);
            int numeroBuscado2 = obtenerNumero(nodo2);
            std::cout <<"NINGUNO DE LOS DOS SON NUMEROS, Y TIENEN: " <<nodo1->valor<<" , "<<nodo2->valor<<std::endl;
            if(nodo1->valor == "NO SE ENCONTRO" || nodo2->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (numeroBuscado1 + numeroBuscado2);
            return to_string(suma);

        }

    }
    else if (valor.find('-')!= std::string::npos){
        std::cout<<"VA A RESTAR"<<std::endl;
        string num1 = getNumbers(valor.substr(0,valor.find('-') + 1));

        string num2 = getNumbers(valor.substr(valor.find('-') + 1, valor.size()));
        std::cout<<"NUM1: |" << num1 <<"|"<<std::endl;
        std::cout<<"NUM2: |" << num2 <<"|"<<std::endl;
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";

        while(p!= num1.size()){
            char x  = num1[p];
            std::cout<<"EL CARACTER A EVALUAR ES: "<<x<<std::endl;
            if (!isdigit(x) ){

                estado_num1 = "no es numero";
                break;
            }
            p = p +1;
        }
        int j = 0;
        while(j != num2.size()){
            char y  = num2[j];
            if (!isdigit(y)){

                estado_num2= "no es numero";
                break;
            }
            j = j + 1;
        }

        std::cout<<"LOS ESTADOS DE MI NUMERO SON: "<<estado_num1 <<", " << estado_num2<<std::endl;

        if(estado_num1 == "es numero" && estado_num2 == "es numero"){

            int suma = (atoi( num1.c_str()) - atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            NodoVar *nodo = buscarNum(num2,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma  = (atoi( num1.c_str()) - numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            NodoVar *nodo = buscarNum(num1,  listaVar);
            std::cout <<"AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH: "<<nodo->variable <<std::endl;
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (atoi( num2.c_str()) - numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){
            NodoVar *nodo1 = buscarNum(num1,  listaVar);
            int numeroBuscado1 = obtenerNumero(nodo1);
            NodoVar *nodo2 = buscarNum(num2,  listaVar);
            int numeroBuscado2 = obtenerNumero(nodo2);
            if(nodo1->valor == "NO SE ENCONTRO" || nodo2->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (numeroBuscado1 - numeroBuscado2);
            return to_string(suma);

        }
    }
    else if (valor.find('/')!= std::string::npos){
        std::cout<<"VA A DIVIDIR"<<std::endl;
        string num1 = getNumbers(valor.substr(0,valor.find('/') + 1));

        string num2 = getNumbers(valor.substr(valor.find('/') + 1, valor.size()));
        std::cout<<"NUM1: |" << num1 <<"|"<<std::endl;
        std::cout<<"NUM2: |" << num2 <<"|"<<std::endl;
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";

        while(p!= num1.size()){
            char x  = num1[p];
            std::cout<<"EL CARACTER A EVALUAR ES: "<<x<<std::endl;
            if (!isdigit(x) ){

                estado_num1 = "no es numero";
                break;
            }
            p = p +1;
        }
        int j = 0;
        while(j != num2.size()){
            char y  = num2[j];
            if (!isdigit(y)){

                estado_num2= "no es numero";
                break;
            }
            j = j + 1;
        }
        std::cout<<"LOS ESTADOS DE MI NUMERO SON: "<<estado_num1 <<", " << estado_num2<<std::endl;
        if(estado_num1 == "es numero" && estado_num2 == "es numero"){

            int suma = (atoi( num1.c_str()) / atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            NodoVar *nodo = buscarNum(num2,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma  = (atoi( num1.c_str()) / numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            NodoVar *nodo = buscarNum(num1,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (atoi( num2.c_str())  / numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){
            NodoVar *nodo1 = buscarNum(num1,  listaVar);
            int numeroBuscado1 = obtenerNumero(nodo1);
            NodoVar *nodo2 = buscarNum(num2,  listaVar);
            int numeroBuscado2 = obtenerNumero(nodo2);
            if(nodo1->valor == "NO SE ENCONTRO" || nodo2->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (numeroBuscado1 / numeroBuscado2);
            return to_string(suma);

        }


    }
    else if (valor.find('%')!= std::string::npos){

        string num1 = getNumbers(valor.substr(0,valor.find('%') + 1));



        string num2 = getNumbers(valor.substr(valor.find('%') + 1, valor.size()));
        int p = 0;
        string estado_num1 ="es numero";
        string estado_num2 ="es numero";
        while(p!= num1.size()){
            char x  = num1[p];
            std::cout<<"EL CARACTER A EVALUAR ES: "<<x<<std::endl;
            if (!isdigit(x) ){

                estado_num1 = "no es numero";
                break;
            }
            p = p +1;
        }
        int j = 0;
        while(j != num2.size()){
            char y  = num2[j];
            if (!isdigit(y)){

                estado_num2= "no es numero";
                break;
            }
            j = j + 1;
        }
        std::cout<<"LOS ESTADOS DE MI NUMERO SON: "<<estado_num1 <<", " << estado_num2<<std::endl;
        if(estado_num1 == "es numero" && estado_num2 == "es numero"){

            int suma = (atoi( num1.c_str()) % atoi( num2.c_str() ));
            return to_string(suma);
        }
        else if(estado_num1 == "es numero" && estado_num2 == "no es numero"){
            NodoVar *nodo = buscarNum(num2,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->variable == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma  = (atoi( num1.c_str()) % numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "es numero"){
            NodoVar *nodo = buscarNum(num1,  listaVar);
            int numeroBuscado = obtenerNumero(nodo);
            if(nodo->variable == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (atoi( num2.c_str()) % numeroBuscado);
            return to_string(suma);
        }
        else if(estado_num1 == "no es numero" && estado_num2 == "no es numero"){
            NodoVar *nodo1 = buscarNum(num1,  listaVar);
            int numeroBuscado1 = obtenerNumero(nodo1);
            NodoVar *nodo2 = buscarNum(num2,  listaVar);
            int numeroBuscado2 = obtenerNumero(nodo2);
            if(nodo1->valor == "NO SE ENCONTRO" || nodo2->valor == "NO SE ENCONTRO"){
                return "NO SE ENCONTRO";
            }
            int suma = (numeroBuscado1 % numeroBuscado2);
            return to_string(suma);

        }
    }
    else{

    }
}

int Parser::obtenerNumero(NodoVar *nodo){

    if(nodo->tipo == "int"){
        return atoi(nodo->valor.c_str());
    }
    if(nodo->tipo == "float"){
        return strtof((nodo->valor).c_str(),0);
    }
    if(nodo->tipo == "long"){
        return atol(nodo->valor.c_str());
    }
    if(nodo->tipo == "double"){
        return atof(nodo->valor.c_str());
    }
}


NodoVar *Parser::buscarNum(string nombre_de_variable, VarList listaVar){

  std::cout<<"SE METIO A BUSCAR LA VARIABLE:" << nombre_de_variable << std::endl;


  NodoVar *nodo = lista_valores.buscarNodo(nombre_de_variable);
  string valor_en_scope = listaVar.buscarNodo(nombre_de_variable)->variable;
  std::cout<<"EN SCOPE:" << valor_en_scope << std::endl;
  std::cout<<"NODO:" << nodo->variable<< std::endl;

  if(nodo->variable == "NO SE ENCONTRO" && valor_en_scope == "NO SE ENCONTRO"){
      std::cout<<"NO SE ENCONTRO EL DATO BUSCADO" << std::endl;
      BlockList listaprov;
      NodoVar* nodox = new NodoVar(" "," "," ",-10,-10," "," ",listaprov);
      nodox->valor = "NO SE ENCONTRO";
      nodox->variable = "NO SE ENCONTRO";
      return nodox;
  }
  else if(nodo->variable == "NO SE ENCONTRO" && valor_en_scope != "NO SE ENCONTRO"){
      nodo = listaVar.buscarNodo(nombre_de_variable);
      return nodo;
  }
  else{
      return nodo;
  }
}

string Parser::getNumbers(string number){
    string valor = "";
    int i = 0;
    while(number[i] == ' '){
        i = i + 1;
    }

    while(number[i]!= '+' && number[i]!= ' ' && number[i]!= ';' && number[i]!= '-' && number[i]!= '/'&& number[i]!= '%'){

        valor = valor + number[i];
        i = i + 1;
    }

    return valor;
}






































