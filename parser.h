#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "varlist.h"
using std::string;
#include "blocklist.h"


struct block{
    int *inicio = (int*)malloc(sizeof (int));
    int *final = (int*)malloc(sizeof (int));
    string codigo_dentro;
};

class Parser
{
public:
   VarList lista_valores;
    string tiposDeVariables[6] = {"int","long","char","float", "double", "struct"};
    string codigoCompleto;
    Parser();
    void parse(string codigo);
    void writeFile(string codigo);
    void readFile();
    int getBlocks(string codigo, VarList *lista);
    int getBlocksAnidados(string codigo);
    VarList getType(string codigo, VarList &lista);
    string getVariable(string codigo);
    bool checkEqualSing(string codigo);
    int getVariableSize(string codigo);
    string getValor(string codigo, string tipo, VarList lista);
    bool verificarTipo(string tipo,string valor);
    string analizarValor(string valor, VarList listaVar);
    int buscarNum(string nombre_de_variable, VarList lista);
    string getNumbers(string numbers);
    BlockList copyList(VarList *listaVar);
    void imprimirVariables();



};

#endif // PARSER_H
