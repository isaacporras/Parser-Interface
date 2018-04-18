#include "client.h"
    #include <QHostAddress>
    #include <iostream>
    using namespace std;



    Client::Client(QObject * obj, QString add, quint16 port) : QObject(obj)
    {

        socket = new QTcpSocket(this);


        connect(socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
        connect(socket, SIGNAL(connected()), this, SLOT(connected()));

        socket->connectToHost(QHostAddress(add), port);
    }

    Client::~Client(){
        socket->close();
        delete socket;
    }



    void Client::SendData(QString data)
    {
        if(!data.isEmpty())
        {
            socket->write(QString(data + "\n").toUtf8());
            socket->waitForBytesWritten(3000);
        }
    }

    void Client::ReadData()
    {
        while(socket->canReadLine())
        {

            QString line = QString::fromUtf8(socket->readAll()).trimmed();
            cout << line.toUtf8().constData() << endl;

            QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
            jsonActual = doc.object();
        }
    }

    void Client::connected()
    {
        socket->write(QString("Client : Server connection has been made (: \n").toUtf8());
        socket->waitForBytesWritten(3000);
    }


