#include "variablelist.h"
#include <QDebug>
#include <QJsonDocument>

variablelist::variablelist()
{
/*
    QString line = "{\"label\":\"racso\",\"type\":\"int\",\"value\":\"888\"}" ;

    QString line2 = "{\"label\":\"batman\",\"type\":\"float\",\"value\":\"9.99\"}" ;

    QJsonObject obj2;
    QJsonDocument doc2 = QJsonDocument::fromJson(line2.toUtf8());
    obj2 = doc2.object();

    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
    obj = doc.object();

    preparation(obj2);
    preparation(obj);
    showList();
*/
}

void variablelist::preparation(QJsonObject object){
        //qDebug()<<"Va funcionando...."<<endl;
        QString type = QString(object.value("Type").toString());
        qDebug()<<type<<endl;
        QString label = QString(object.value("Variable").toString());
        if (type == QString("int")){
            int value = object.value("Value").toString().toInt();
            insertNodeInt(type,label,value);
            qDebug()<<"Nodo insertado...";
        }else if (type == QString("float")){
            float value = object.value("Value").toString().toFloat();
            insertNodeFloat(type,label,value);
            qDebug()<<"Nodo insertado...";
        }else if (type == QString("double")){
            double value = object.value("Value").toString().toDouble();
            insertNodeDouble(type,label,value);
            qDebug()<<"Nodo insertado...";
        }else if (type == "long"){
            long value = object.value("Value").toString().toLong();
            insertNodeLong(type,label,value);

        }else{
            qDebug()<<"No se encuentra el tipo"<<endl;
        }
}

void variablelist::insertNodeInt(QString type, QString label, int value ){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->value = value;

    if(head == NULL){
        head = newnode;
        head->next = NULL;
        tail = newnode;
    }else{
        tail->next = newnode;
        tail = newnode;
        tail->next = NULL;
    }
}

void variablelist::insertNodeFloat(QString type, QString label, float value ){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->valuefloat = value;

    if(head == NULL){
        head = newnode;
        head->next = NULL;
        tail = newnode;
    }else{
        tail->next = newnode;
        tail = newnode;
        tail->next = NULL;
    }
}

void variablelist::insertNodeLong(QString type, QString label, long value ){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->value = value;

    if(head == NULL){
        head = newnode;
        head->next = NULL;
        tail = newnode;
    }else{
        tail->next = newnode;
        tail = newnode;
        tail->next = NULL;
    }
}

void variablelist::insertNodeDouble(QString type, QString label, double value ){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->value = value;

    if(head == NULL){
        head = newnode;
        head->next = NULL;
        tail = newnode;
    }else{
        tail->next = newnode;
        tail = newnode;
        tail->next = NULL;
    }
}

void variablelist::showList(){
    Node *temp = new Node();
    temp = head;

    if(head == NULL){
        qDebug()<<"List is empty";
    }else{
        while(temp != NULL){
            if(temp->type == "int"){
                 qDebug()<<"Type: "<<temp->type<<"Label: "<<temp->label<<" Value: "<<temp->value<<endl;
            }else if (temp->type == "float"){
                qDebug()<<"Type: "<<temp->type<<"Label: "<<temp->label<<" Value: "<<temp->valuefloat<<endl;
            }else if (temp->type == "double"){
                qDebug()<<"Type: "<<temp->type<<"Label: "<<temp->label<<" Value: "<<temp->valuedouble<<endl;
            }else if (temp->type == "long"){
                qDebug()<<"Type: "<<temp->type<<"Label: "<<temp->label<<" Value: "<<temp->valuelong<<endl;
            }else{
                qDebug()<<"No se encontro el tipo..."<<endl;
            }

            temp = temp->next;
        }
    }
}

void variablelist::getValue(int index){
    Node *temp = new Node();
    temp = head;

    for(int i = 0; i<index; i++){
        temp = temp->next;
    }
    qDebug()<<temp->value;
}

void variablelist::getLabel(int index){
    Node *temp = new Node();
    temp = head;

    for(int i = 0; i<index; i++){
        temp = temp->next;
    }
    qDebug()<<temp->label;
}

void variablelist::getType(int index){
    Node *temp = new Node();
    temp = head;

    for(int i = 0; i<index; i++){
        temp = temp->next;
    }
    qDebug()<<temp->type;
}

int variablelist::totalNodes(){
    Node *temp = new Node();
    temp = head;
    int cont;

    while(temp != NULL){
        temp = temp->next;
        cont++;
    }
    return cont;
}

