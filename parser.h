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
    string getValor(string codigo, string tipo);
    bool verificarTipo(string tipo,string valor);
    string analizarValor(string valor);
    int buscarNum(string nombre_de_variable);
    string getNumbers(string numbers);
    BlockList copyList(VarList *listaVar);



};

#endif // PARSER_H
