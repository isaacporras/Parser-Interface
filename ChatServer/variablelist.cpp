#include "variablelist.h"
#include <QDebug>
#include <QJsonDocument>
#include <iostream>

variablelist::variablelist()
{
    mallocPtr = new Malloc(1024);
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
        //qDebug()<<type<<endl;
        QString label = QString(object.value("Variable").toString());
        if (type == QString("int")){
            int value = object.value("Value").toString().toInt();
            int* intPtr = mallocPtr->agregar_int(value);
            insertNodeInt(type,label,value,intPtr);
            qDebug()<<"Nodo insertado...";
        }else if (type == QString("float")){
            float value = object.value("Value").toString().toFloat();
            float* floatPtr = mallocPtr->agregar_float(value);
            insertNodeFloat(type,label,value,floatPtr);
            qDebug()<<"Nodo insertado...";
        }else if (type == QString("double")){
            double value = object.value("Value").toString().toDouble();
            double* doublePtr = mallocPtr->agregar_double(value);
            insertNodeDouble(type,label,value,doublePtr);
            qDebug()<<"Nodo insertado...";
        }else if (type == "long"){
            long value = object.value("Value").toString().toLong();
            long* longPtr = mallocPtr->agregar_long(value);
            insertNodeLong(type,label,value,longPtr);
            qDebug()<<"Nodo insertado...";

        }else if (type == "char"){
            char value = object.value("Value").toString().toStdString()[0];
            char* charPtr = mallocPtr->agregar_char(value);
            insertNodeChar(type,label,value,charPtr);
            qDebug()<<"Nodo insertado...";
        }

        else{
            qDebug()<<"No se encuentra el tipo"<<endl;
        }
}

void variablelist::insertNodeInt(QString type, QString label, int value , int* ptr){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->value = value;
    newnode->ptr = (void*)ptr;
    char strAddress[] = "0x00000000";
    sprintf(strAddress, "0x%x", ptr);
    newnode->address = strAddress;

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
void variablelist::insertNodeChar(QString type, QString label, char value , char* ptr){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->valuechar = value;
    newnode->ptr = (void*)ptr;
    char strAddress[] = "0x00000000";
    sprintf(strAddress, "0x%x", ptr);
    newnode->address = strAddress;

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

void variablelist::insertNodeFloat(QString type, QString label, float value , float* ptr){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->valuefloat = value;

    newnode->ptr = (void*)ptr;
    char strAddress[] = "0x00000000";
    sprintf(strAddress, "0x%x", ptr);
    newnode->address = strAddress;

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

void variablelist::insertNodeLong(QString type, QString label, long value, long* ptr ){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->value = value;

    newnode->ptr = (void*)ptr;
    char strAddress[] = "0x00000000";
    sprintf(strAddress, "0x%x", ptr);
    newnode->address = strAddress;

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

void variablelist::insertNodeDouble(QString type, QString label, double value, double* ptr ){

    Node *newnode = new Node();
    newnode->label = label;
    newnode->type = type;
    newnode->value = value;

    newnode->ptr = (void*)ptr;
    char strAddress[] = "0x00000000";
    sprintf(strAddress, "0x%x", ptr);
    newnode->address = strAddress;

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
QString variablelist::getAddress(QString label){
    Node *temp = new Node();
    temp = head;

    for(int i = 0; i<totalNodes(); i++){
        if (label == temp->label){
            break;
        }
        temp = temp->next;
    }
    return temp->address;
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
    int cont = 0;

    while(temp != NULL){
        cont++;
        temp = temp->next;
    }
    return cont;
}

