#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include <string>
#include <typeinfo>
#include <QString>
#include <QJsonObject>
#include "malloc.h"
#include <iostream>

using namespace std;

///
/// Node
/// Estructura que maneja la información de cada variable
///

struct Node{
    int value;
    float valuefloat;
    long valuelong;
    double valuedouble;
    char valuechar;
    QString type;
    QString label;
    Node *next;
    void* ptr;
    QString address;
};

///
/// Clase variablelist
///
/// Clase encargada de la administración de la memoria y de procesar las solicitudes del cliente
///

class variablelist
{

private:

    Node *head;
    Node *tail;

public:
    variablelist();
    QString preparation(QJsonObject object);
    void insertNodeInt(QString type, QString label, int value, int* ptr);
    void insertNodeFloat(QString type, QString label, float value, float* ptr );
    void insertNodeLong(QString type, QString label, long value, long* ptr );
    void insertNodeDouble(QString type, QString label, double value, double* ptr );
    void insertNodeChar(QString type, QString label, char value , char* ptr);
    void showList();
    int totalNodes();
    void getValue(int index);
    void getLabel(int index);
    void getType(int index);
    QString getAddress(QString label);

    ///
    /// mallocPtr
    /// Se encarga de crear las variables en la memoria RAM
    ///

    Malloc* mallocPtr;

    string analizarValor(string valor , string tipo);
    string getValue(QString label, string type);
    Node* getNode(QString label);
};

#endif // VARIABLELIST_H
