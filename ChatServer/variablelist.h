#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include <string>
#include <typeinfo>
#include <QString>
#include <QJsonObject>

struct Node{
    int value;
    float valuefloat;
    long valuelong;
    double valuedouble;
    QString type;
    QString label;
    Node *next;
};

class variablelist
{

private:

    Node *head;
    Node *tail;

public:
    variablelist();
    void preparation(QJsonObject object);
    void insertNodeInt(QString type, QString label, int value );
    void insertNodeFloat(QString type, QString label, float value );
    void insertNodeLong(QString type, QString label, long value );
    void insertNodeDouble(QString type, QString label, double value );
    void showList();
    int totalNodes();
    void getValue(int index);
    void getLabel(int index);
    void getType(int index);
};

#endif // VARIABLELIST_H
