#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;


struct block{
    int *inicio = (int*)malloc(sizeof (int));
    int *final = (int*)malloc(sizeof (int));
};

class Parser
{
public:
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
    string getValor(string codigo);
    bool verificarTipo(string tipo,string valor);


};

#endif // PARSER_H
