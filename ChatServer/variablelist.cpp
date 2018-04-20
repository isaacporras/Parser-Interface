#include "variablelist.h"
#include <QDebug>
#include <QJsonDocument>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

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

QString variablelist::preparation(QJsonObject object){
        //qDebug()<<"Va funcionando...."<<endl;
        QString type = QString(object.value("Type").toString());
        //qDebug()<<type<<endl;
        QString label = QString(object.value("Variable").toString());
        QString valor;
        if (type == QString("int")){
            string analisis = analizarValor(object.value("Value").toString().toUtf8().constData(), type.toUtf8().constData());
            int value = atoi(analisis.c_str());
            int* intPtr = mallocPtr->agregar_int(value);
            insertNodeInt(type,label,value,intPtr);
            qDebug()<<"Nodo insertado...";
            valor = QString::fromStdString(to_string(value).c_str());
        }else if (type == QString("float")){
            string analisis = analizarValor(object.value("Value").toString().toUtf8().constData(), type.toUtf8().constData());
            float value;
            string S = analisis;
            istringstream(S) >> value;
            float* floatPtr = mallocPtr->agregar_float(value);
            insertNodeFloat(type,label,value,floatPtr);
            qDebug()<<"Nodo insertado...";
            valor = QString::fromStdString(to_string(value).c_str());
        }else if (type == QString("double")){
            string analisis = analizarValor(object.value("Value").toString().toUtf8().constData(), type.toUtf8().constData());
            double value;
            string S = analisis;
            istringstream(S) >> value;
            double* doublePtr = mallocPtr->agregar_double(value);
            insertNodeDouble(type,label,value,doublePtr);
            qDebug()<<"Nodo insertado...";
            valor = QString::fromStdString(to_string(value).c_str());
        }else if (type == "long"){
            string analisis = analizarValor(object.value("Value").toString().toUtf8().constData(), type.toUtf8().constData());
            long value;
            string S = analisis;
            istringstream(S) >> value;
            long* longPtr = mallocPtr->agregar_long(value);
            insertNodeLong(type,label,value,longPtr);
            qDebug()<<"Nodo insertado...";
            valor = QString::fromStdString(to_string(value).c_str());
        }else if (type == "char"){
            string analisis = analizarValor(object.value("Value").toString().toUtf8().constData(), type.toUtf8().constData());
            char value = analisis[1];
            cout << analisis << endl;
            cout << value << endl;
            char* charPtr = mallocPtr->agregar_char(value);
            insertNodeChar(type,label,value,charPtr);
            qDebug()<<"Nodo insertado...";
            valor = QString::fromStdString(analisis.c_str());
        }

        else{
            qDebug()<<"No se encuentra el tipo"<<endl;
        }
        return valor;
}

string variablelist::analizarValor(string valor, string tipo){

    ///
    ///Operaciones con enteros
    ///

    if (tipo == "int"){

        ///
        ///Suma
        ///

        if (valor.find('+') != string::npos){
            string strNum1 = valor.substr(0,valor.find('+'));
            string strNum2 = valor.substr(valor.find('+') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                int suma = (atoi(strNum1.c_str()) + atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(strNum1.c_str()) + atoi(valor_num2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(valor_num1.c_str()) + atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma = (atoi(valor_num1.c_str()) + atoi(valor_num2.c_str()));
                return to_string(suma);
            }
        }

        ///
        ///Resta
        ///

        else if (valor.find('-') != string::npos){
            string strNum1 = valor.substr(0,valor.find('-'));
            string strNum2 = valor.substr(valor.find('-') + 1);
            cout << valor << endl << tipo << endl << strNum1 << endl << strNum2 << endl;
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                int suma = (atoi(strNum1.c_str()) - atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(strNum1.c_str()) - atoi(valor_num2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(valor_num1.c_str()) - atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma = (atoi(valor_num1.c_str()) - atoi(valor_num2.c_str()));
                return to_string(suma);
            }
        }

        ///
        ///Multiplicación
        ///

        if (valor.find('*') != string::npos){
            string strNum1 = valor.substr(0,valor.find('*'));
            string strNum2 = valor.substr(valor.find('*') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                int suma = (atoi(strNum1.c_str()) * atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(strNum1.c_str()) * atoi(valor_num2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(valor_num1.c_str()) * atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma = (atoi(valor_num1.c_str()) * atoi(valor_num2.c_str()));
                return to_string(suma);
            }
        }

        ///
        ///División
        ///

        if (valor.find('/') != string::npos){
            string strNum1 = valor.substr(0,valor.find('/'));
            string strNum2 = valor.substr(valor.find('/') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                int suma = (atoi(strNum1.c_str()) / atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(strNum1.c_str()) / atoi(valor_num2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(valor_num1.c_str()) / atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma = (atoi(valor_num1.c_str()) / atoi(valor_num2.c_str()));
                return to_string(suma);
            }
        }

        ///
        ///Módulo
        ///

        if (valor.find('%') != string::npos){
            string strNum1 = valor.substr(0,valor.find('%'));
            string strNum2 = valor.substr(valor.find('%') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                int suma = (atoi(strNum1.c_str()) % atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(strNum1.c_str()) % atoi(valor_num2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma  = (atoi(valor_num1.c_str()) % atoi(strNum2.c_str()));
                return to_string(suma);
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                int suma = (atoi(valor_num1.c_str()) % atoi(valor_num2.c_str()));
                return to_string(suma);
            }
        }

        else{
            return valor;
        }
    }

    ///
    ///Operaciones con doubles
    ///

    if (tipo == "double"){

        ///
        ///Suma
        ///
        if (valor.find('+') != string::npos){
            string strNum1 = valor.substr(0,valor.find('+'));
            string strNum2 = valor.substr(valor.find('+') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Resta
        ///

        if (valor.find('-') != string::npos){
            string strNum1 = valor.substr(0,valor.find('-'));
            string strNum2 = valor.substr(valor.find('-') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Multiplicación
        ///

        if (valor.find('*') != string::npos){
            string strNum1 = valor.substr(0,valor.find('*'));
            string strNum2 = valor.substr(valor.find('*') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
        }

        ///
        ///División
        ///

        if (valor.find('/') != string::npos){
            string strNum1 = valor.substr(0,valor.find('/'));
            string strNum2 = valor.substr(valor.find('/') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Módulo
        ///

        if (valor.find('%') != string::npos){
            string strNum1 = valor.substr(0,valor.find('%'));
            string strNum2 = valor.substr(valor.find('%') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = strNum1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = strNum2;
                istringstream(S) >> value2;
                double modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                double value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                double value2;
                S = valor_num2;
                istringstream(S) >> value2;
                double modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
        }
        else{
            return valor;
        }
    }

    ///
    ///Operaciones con long
    ///

    if (tipo == "long"){

        ///
        ///Suma
        ///
        if (valor.find('+') != string::npos){
            string strNum1 = valor.substr(0,valor.find('+'));
            string strNum2 = valor.substr(valor.find('+') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Resta
        ///

        if (valor.find('-') != string::npos){
            string strNum1 = valor.substr(0,valor.find('-'));
            string strNum2 = valor.substr(valor.find('-') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Multiplicación
        ///

        if (valor.find('*') != string::npos){
            string strNum1 = valor.substr(0,valor.find('*'));
            string strNum2 = valor.substr(valor.find('*') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
        }

        ///
        ///División
        ///

        if (valor.find('/') != string::npos){
            string strNum1 = valor.substr(0,valor.find('/'));
            string strNum2 = valor.substr(valor.find('/') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Módulo
        ///

        if (valor.find('%') != string::npos){
            string strNum1 = valor.substr(0,valor.find('%'));
            string strNum2 = valor.substr(valor.find('%') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) ){
                    estado_num1 = false;
                    break;
                }
                p++;
            }
            p = 0;
            while(p != strNum2.size()){
                char y = strNum2[p];
                if (!isdigit(y)){
                    estado_num2= false;
                    break;
                }
                p++;
            }
            if(estado_num1 == true && estado_num2 == true){
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = strNum1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = strNum2;
                istringstream(S) >> value2;
                long modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                long value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                long value2;
                S = valor_num2;
                istringstream(S) >> value2;
                long modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
        }
        else{
            return valor;
        }
    }

    ///
    ///Operaciones con float
    ///

    if (tipo == "float"){

        ///
        ///Suma
        ///
        if (valor.find('+') != string::npos){
            string strNum1 = valor.substr(0,valor.find('+'));
            string strNum2 = valor.substr(valor.find('+') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float suma = value1 + value2;
                ostringstream Q;
                Q.fill('#');
                Q << suma;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Resta
        ///

        if (valor.find('-') != string::npos){
            string strNum1 = valor.substr(0,valor.find('-'));
            string strNum2 = valor.substr(valor.find('-') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float resta = value1 - value2;
                ostringstream Q;
                Q.fill('#');
                Q << resta;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Multiplicación
        ///

        if (valor.find('*') != string::npos){
            string strNum1 = valor.substr(0,valor.find('*'));
            string strNum2 = valor.substr(valor.find('*') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float producto = value1 * value2;
                ostringstream Q;
                Q.fill('#');
                Q << producto;
                S = Q.str();
                return S;
            }
        }

        ///
        ///División
        ///

        if (valor.find('/') != string::npos){
            string strNum1 = valor.substr(0,valor.find('/'));
            string strNum2 = valor.substr(valor.find('/') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float division = value1 / value2;
                ostringstream Q;
                Q.fill('#');
                Q << division;
                S = Q.str();
                return S;
            }
        }

        ///
        ///Módulo
        ///

        if (valor.find('%') != string::npos){
            string strNum1 = valor.substr(0,valor.find('%'));
            string strNum2 = valor.substr(valor.find('%') + 1);
            int p = 0;
            bool estado_num1 = true;
            bool estado_num2 = true;
            bool isPoint = false;
            while(p!= strNum1.size()){
                char x  = strNum1[p];
                if (!isdigit(x) && x != '.'){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == true){
                    estado_num1 = false;
                    break;
                }
                if (x == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            p = 0;
            isPoint = false;
            while(p != strNum2.size()){
                char y  = strNum2[p];
                if (!isdigit(y) && y != '.'){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == true){
                    estado_num2 = false;
                    break;
                }
                if (y == '.' && isPoint == false)
                    isPoint = true;
                p = p+1;
            }
            if(estado_num1 == true && estado_num2 == true){
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == true && estado_num2 == false){
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = strNum1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == true){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = strNum2;
                istringstream(S) >> value2;
                float modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
            else if(estado_num1 == false && estado_num2 == false){
                string valor_num1 = getValue(QString::fromStdString(strNum1.c_str()),tipo);
                if(valor_num1 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                string valor_num2 = getValue(QString::fromStdString(strNum2.c_str()),tipo);
                if(valor_num2 == "ERROR"){
                    return "NO SE ENCONTRO";
                }
                float value1;
                string S = valor_num1;
                istringstream(S) >> value1;
                float value2;
                S = valor_num2;
                istringstream(S) >> value2;
                float modulo = fmod(value1,value2);
                ostringstream Q;
                Q.fill('#');
                Q << modulo;
                S = Q.str();
                return S;
            }
        }
        else{
            return valor;
        }
    }

    ///
    ///Verificación de char
    ///

    if (tipo == "char"){
        if (valor[0]!='\'' || valor[valor.size()-1]!='\''){
            string valor_var = getValue(QString::fromStdString(valor.c_str()),tipo);
            if(valor_var == "ERROR"){
                return "SE DEBE PONER ' ' PARA INICIALIZAR UN CHAR";
            }
            valor_var = "'"+valor_var+"'";
            return valor_var;
        }
        else{
            return valor;
        }
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
    newnode->valuelong = value;

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
    newnode->valuedouble = value;

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
string variablelist::getValue(QString label, string type){
    Node *temp = new Node();
    temp = head;

    for(int i = 0; i<totalNodes(); i++){
        if (label == temp->label){
            break;
        }
        temp = temp->next;
    }
    if (type == "int")
        return to_string(temp->value);
    else if (type == "double"){
        string S;
        ostringstream Q;
        Q.fill('#');
        Q << temp->valuedouble;
        S = Q.str();
        return S;
    }
    else if (type == "long"){
        string S;
        ostringstream Q;
        Q.fill('#');
        Q << temp->valuelong;
        S = Q.str();
        return S;
    }
    else if (type == "float"){
        string S;
        ostringstream Q;
        Q.fill('#');
        Q << temp->valuefloat;
        S = Q.str();
        return S;
    }
    else if (type == "char"){
        string S;
        ostringstream Q;
        Q.fill('#');
        Q << temp->valuechar;
        S = Q.str();
        return S;
    }
    return "ERROR";
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

