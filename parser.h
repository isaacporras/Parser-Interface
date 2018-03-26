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
    string codigoCompleto;
    Parser();
    void parse(string codigo);
    void writeFile(string codigo);
    void readFile();
    void getBlocks(string codigo);
    int getBlocksAnidados(string codigo);


};

#endif // PARSER_H
