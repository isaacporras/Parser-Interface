#include "server.h"
#include "variablelist.h"
#include <iostream>
#include "malloc.h"
#include <string>

///
/// Clase Server
/// Encargada de la administración de las variables y del manejo de la memoria. Se comunica con la clase Client.
///

using namespace std;

    Server::Server(QObject* parent , quint16 port): QTcpServer(parent)
    {
        vl = new variablelist();
        firstTime = true;
        if(!servidor){
            servidor = this;
        }
      connect(this, SIGNAL(newConnection()),this, SLOT(acceptConnection()));

      if (!this->listen(QHostAddress::Any, port)) {
              qDebug() << "ERROR";
          }
    }

    Server::~Server()
    {
      delete client;
      close();
    }

    ///
    ///  Método -> acceptConnection
    ///  Inicia la comunicación con algún cliente que la esté solicitando
    ///

    void Server::acceptConnection()
    {
      client = nextPendingConnection();

      connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
      connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));

      qDebug() << "New client from:" << client->peerAddress().toString();
    }

    ///
    ///  Método -> startRead
    ///  Lee la información en JSON enviada por el cliente.
    ///

    void Server::startRead()
    {
        while(client->canReadLine())
        {
            QString line = QString::fromUtf8(client->readAll().trimmed());
            cout << "Client :\n" << line.toUtf8().constData() << endl;

            if (firstTime == true){
                //sendMessage(QString("Hello!"));
                firstTime = false;
            }
            else if(line.toUtf8().constData() == "0"){

            }
            else{
                QJsonObject obj;
                QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
                obj = doc.object();

                QString finalValue = vl->preparation(obj);
                if (obj.value("Type").toString() == "Print Request"){
                    QJsonObject* jobj = new QJsonObject();
                    QJsonValue* jstring1 = new QJsonValue(finalValue);
                    jobj->insert("Print Request",jstring1->toString());
                    QJsonDocument doc2(*jobj);
                    QByteArray bytes = doc2.toJson();
                    const char* charString = bytes.data();
                    string json(charString);
                    QString message = json.c_str();
                    qDebug() << message;
                    sendMessage(message);
                    }
                else{
                QString qstr;
            if (obj.value("Type").toString() == "Post Primitive Asignation"){
                string var = obj.value("Variable").toString().toUtf8().constData();
                qstr = vl->getAddress(QString(var.substr(1).c_str()));
            }
            else {qstr = vl->getAddress(obj.value("Variable").toString());}



            QJsonObject* jobj = new QJsonObject();
            QJsonValue* jstring1 = new QJsonValue(obj.value("Variable").toString());
            QJsonValue* jstring2 = new QJsonValue(finalValue);
            QJsonValue* jstring3 = new QJsonValue(qstr);
            jobj->insert("Label",jstring1->toString());
            jobj->insert("Value",jstring2->toString());
            jobj->insert("Address",jstring3->toString());
            QJsonDocument doc2(*jobj);
            QByteArray bytes = doc2.toJson();
            const char* charString = bytes.data();
            string json(charString);
            QString message = json.c_str();

            qDebug() << message;
            sendMessage(message);
            }
            break;
        }
        }

    }

    ///
    ///  Método -> sendMessage
    ///  Parámetro -> data
    ///  Envía la información data, que contiene los resultados de la administración de memoria
    ///

    void Server::sendMessage(QString data){
        client->write(QString(data+"\n").toUtf8());
        client->waitForBytesWritten(1000);
    }

    ///
    ///  Método -> disconnected
    ///  Notifica cuando el Cliente actual pierde la comunicación.
    ///

    void Server::disconnected()
    {
        qDebug() << "Client disconnected:" << client->peerAddress().toString();
    }

