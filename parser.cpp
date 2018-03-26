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
//    ofstream myfile;
//    myfile.open ("/Users/IsaacPorras/Parser-Interface/CodeFile.cpp");
//    myfile << codigo;
//    myfile.close();
//    std::cout<<"Escribio en el archivo"<<std::endl;
    getBlocks(codigo);

    }

void Parser::readFile(){
//    string line;
//      ifstream myfile ("/Users/IsaacPorras/Parser-Interface/CodeFile.cpp");
//      if (myfile.is_open())
//      {
//        while ( getline (myfile,line) )
//        {
//          std::cout << line << std::endl;
//        }
//        myfile.close();
//      }

//      else cout << "Unable to open file";
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
