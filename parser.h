#ifndef PARSER_H
#define PARSER_H
#include <string>



#include "client.h"
#include "QJsonObject"
#include "QJsonDocument"
using std::string;


struct block{
    int *inicio = (int*)malloc(sizeof (int));
    int *final = (int*)malloc(sizeof (int));
    string codigo_dentro;
};

class Parser
{
public:
    void reubicarStruct(string codigo);
    int *i = (int*)malloc(sizeof (int));
    string entero = "int";
    QJsonObject makeJson(string tip, string val, string var);
    string cutWhiteSpaces(string codigo);
    string tiposDeVariables[6] = {"int","long","char","float", "double", "struct"};
    string codigoCompleto;
    Parser();
    QJsonObject parse(string codigo);
    QJsonObject writeFile(string codigo);
    void readFile();
    bool esPointer(string codigo);
    int getBlocksAnidados(string codigo);
    QJsonObject getType(string codigo);
    string getVariable(string codigo);
    bool checkEqualSing(string codigo);
    bool checkDotSing(string codigo);
    int *getVariableSize(string codigo);
    string getValor(string codigo, string tipo);
    bool verificarTipo(string tipo,string valor);

    string getNumbers(string numbers);
    string getPrint_Addr_Value(string codigo);
    void imprimirVariables();
    struct block analizarStruct(string codigo);
    int *getReubicador(string codigo);
    string isStructDef(string codigo);





};

#endif // PARSER_H
