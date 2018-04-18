#include "server.h"
#include "variablelist.h"
#include <iostream>
#include "malloc.h"
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

    void Server::acceptConnection()
    {
      client = nextPendingConnection();

      connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
      connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));

      qDebug() << "New client from:" << client->peerAddress().toString();
    }

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
            else{
                QJsonObject obj;
                QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
                obj = doc.object();

                vl->preparation(obj);

            QString qstr = vl->getAddress(obj.value("Variable").toString());

            QJsonObject* jobj = new QJsonObject();
            QJsonValue* jstring1 = new QJsonValue(obj.value("Variable").toString());
            QJsonValue* jstring2 = new QJsonValue(obj.value("Value").toString());
            QJsonValue* jstring3 = new QJsonValue(qstr);
            jobj->insert("Label",jstring1->toString());
            jobj->insert("Value",jstring2->toString());
            jobj->insert("Address",jstring3->toString());
            QJsonDocument doc2(*jobj);
            QByteArray bytes = doc2.toJson();
            const char* charString = bytes.data();
            string json(charString);
            QString message = json.c_str();

            //client->write(QString(message + "\n").toUtf8());
            sendMessage(message);
            }
            break;
        }

    }

    void Server::sendMessage(QString data){
        client->write(QString(data+"\n").toUtf8());
        client->waitForBytesWritten(3000);
    }

    void Server::disconnected()
    {

        qDebug() << "Client disconnected:" << client->peerAddress().toString();

        client->write(QString("Server : I wish you didn't leave ):\n").toUtf8());
        client->waitForBytesWritten(3000);
    }

