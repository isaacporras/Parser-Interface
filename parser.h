#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "client.h"
#include "QJsonObject"
#include "QJsonDocument"
using std::string;
/**
  *@file Parser.h
  * @version 1.0
  * @date 5/3/18
  * @author Oscar Isaac Porras Perez
  * @title Parser
  * @brief Maneja todo lo referente al parseo del codigo C!
  */
/**
 * @brief The block struct Este struct es utilizado para representar las estructuras de codigo
 */
struct block{
    int* inicio = (int*)malloc(sizeof (int));
    int* final = (int*)malloc(sizeof (int));
    string codigo_dentro;
};
/**
 * @brief The Parser class Maneja todo lo referente al parseo del codigo C!
 */
class Parser
{
public:
    /**
     * @brief reubicarStruct Reubica el lector en la la posicion de inicio de la siguiente declaracion de variable
     * @param codigo Codigo sobre el cual se esta trabajando
     */
    void reubicarStruct(string codigo);
    /**
     * @brief i Este es el contador que va a funcionar como lector del codigo
     */
    int* i = (int*)malloc(sizeof (int));

    string entero = "int";
    /**
     * @brief makeJson Recibe los parametros necesarios que van a ser utilizados para la creacion del Json
     * @param tip Tipo de la variable
     * @param val El valor de la variable
     * @param var La etiqueta de la variable
     * @return
     */
    QJsonObject makeJson(string tip, string val, string var);
    /**
     * @brief cutWhiteSpaces Metodo que le pasa un string y elimina los espacios en blanco
     * @param codigo codigo al que se le van a eliminar los espacios en blanco
     * @return retorna el codigo sin espacios en blanco
     */
    string cutWhiteSpaces(string codigo);

    string tiposDeVariables[6] = {"int","long","char","float", "double", "struct"};
    string codigoCompleto;
    /**
     * @brief Parser inicializa el Parser
     */
    Parser();
    /**
     * @brief parse Llama a todos los metodos necesarios para parsear el codigo
     * @param codigo codigo que va a ser Parseado
     * @return  retorna un QJSON con la informacion de la varaible que leyo
     */
    QJsonObject parse(string codigo);
    /**
     * @brief writeFile redirecciona otra vez los metos que llamo el metodo parser
     * @param codigo Codigo que se va a parsear
     * @return
     */
    QJsonObject writeFile(string codigo);
    /**
     * @brief readFile Este metodo no esta siendo utilizado actualmente
     */
    void readFile();
    /**
     * @brief esPointer Verifica si en un fracmento de codigo hay un pointer
     * @param codigo Fracmento de codigo que se va a analizar
     * @return
     */
    bool esPointer(string codigo);
    /**
     * @brief getBlocksAnidados analiza blocks anidados
     * @param codigo Codigo de los blocks anidados
     * @return  retorna una posicion en la que se va a reubicar el lector
     */
    int getBlocksAnidados(string codigo);
    /**
     * @brief getType Este metodo lleva el flujo total del parseo del codigo
     * @param codigo Codigo que se va a parsear
     * @return retorna un QJSON con la informacion de la varaible que leyo
     */
    QJsonObject getType(string codigo);
    /**
     * @brief getVariable Analiza un fracmento de codigo y obtiene la variable que tiene adentro
     * @param codigo Fracmento de codigo que se va a analizar
     * @return retorna un string con la variable correspondiente
     */
    string getVariable(string codigo);
    /**
     * @brief checkEqualSing Verifica que en la asignacion de variables existan un igual entre la variable y el valor
     * @param codigo Fracmento de codigo que se va a analizar
     * @return True si tiene igual y False si no
     */
    bool checkEqualSing(string codigo);
    /**
     * @brief checkDotSing Verifica si tiene un punto y coma al final de la variable
     * @param codigo Fracmento de codigo que se va a analizar
     * @return True si tiene punto y coma y False si no
     */
    bool checkDotSing(string codigo);
    /**
     * @brief getVariableSize Recibe una variable y retorna el tamano de la variable
     * @param codigo Fracmento con la variable
     * @return Tamano de la variable
     */
    int *getVariableSize(string codigo);
    /**
     * @brief getValor Obtiene un fracmento de codigo y retorna el valor que se le esta asignando a una variable
     * @param codigo Fragmento de codigo
     * @param tipo Tipo de la variable que se le esta haciendo la asignacion
     * @return  Retorna el valor que se le esta asignando
     */
    string getValor(string codigo, string tipo);
    /**
     * @brief verificarTipo Verifica si el tipo establecido concuenrda con el valor asignado
     * @param tipo El tipo declarado
     * @param valor El valor asignado
     * @return True si comple y false si no cumple
     */
    bool verificarTipo(string tipo,string valor);
    /**
     * @brief getNumbers recibe los numeros
     * @param numbers numeros
     * @return retorna los numeros recortados
     */
    string getNumbers(string numbers);
    /**
     * @brief getPrint_Addr_Value Recibe un fragmento de codigo y retorna lo que se encuentra entre parentesis
     * @param codigo Fragmento de codigo
     * @return El valor que encontro dentro del parentesis
     */
    string getPrint_Addr_Value(string codigo);
    /**
     * @brief imprimirVariables imprime las variables que se encuentran almacenadas
     */
    void imprimirVariables();
    /**
     * @brief analizarStruct Analiza un struct
     * @param codigo Fragmento de codigo que tiene el struct
     * @return struct con la representacion del struct de codigo
     */
    struct block analizarStruct(string codigo);
    /**
     * @brief getReubicador reubica el contador en el punto y coma mas cercano
     * @param codigo codigo que quiere reubicar
     * @return el contador
     */
    int *getReubicador(string codigo);
    /**
     * @brief isStructDef Verifica si en el fragmento de codigo que le estan pasando hay una definicion de struct
     * @param codigo codigo con el fragmento
     * @return Retorna un string con la informacion del struct
     */
    string isStructDef(string codigo);





};

#endif // PARSER_H
