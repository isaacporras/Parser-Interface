#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "varlist.h"
using std::string;


struct block{
    int *inicio = (int*)malloc(sizeof (int));
    int *final = (int*)malloc(sizeof (int));
};

class Parser
{
public:
   VarList lista_variables;
   VarList lista_valores;
    string tiposDeVariables[6] = {"int","long","char","float", "double", "struct"};
    string codigoCompleto;
    Parser();
    void parse(string codigo);
    void writeFile(string codigo);
    void readFile();
    void getBlocks(string codigo);
    int getBlocksAnidados(string codigo);
    void getType(string codigo);
    string getVariable(string codigo);
    bool checkEqualSing(string codigo);
    int getVariableSize(string codigo);
    string getValor(string codigo, string tipo);
    bool verificarTipo(string tipo,string valor);
    string analizarValor(string valor);
    int buscarNum(string nombre_de_variable);


};

#endif // PARSER_H
