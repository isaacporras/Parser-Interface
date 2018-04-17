#include "server.h"
#include "variablelist.h"
#include <iostream>
using namespace std;

variablelist *vl = new variablelist();

    Server::Server(QObject* parent , quint16 port): QTcpServer(parent)
    {
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
            //qDebug() << "Client :" << line;

            QJsonObject obj;
            QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
            obj = doc.object();

            vl->preparation(obj);

            break;

            client->write(QString("Server : I've taken your message (:\n").toUtf8());
            client->waitForBytesWritten(3000);
        }

    }

    void Server::disconnected()
    {

        qDebug() << "Client disconnected:" << client->peerAddress().toString();

        client->write(QString("Server : I wish you didn't leave ):\n").toUtf8());
        client->waitForBytesWritten(3000);
    }

