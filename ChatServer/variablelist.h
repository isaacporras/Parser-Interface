#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include <string>
#include <typeinfo>
#include <QString>
#include <QJsonObject>
#include "malloc.h"
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

class variablelist
{

private:

    Node *head;
    Node *tail;

public:
    variablelist();
    void preparation(QJsonObject object);
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
    Malloc* mallocPtr;
};

#endif // VARIABLELIST_H
