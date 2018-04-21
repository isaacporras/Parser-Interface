#include "client.h"
    #include <QHostAddress>
    #include <iostream>
    using namespace std;

///
///  Clase Client
///  Clase que se comunica con el Server, mantiene relación directa con el IDE y el parser
///

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

    ///
    ///  Método -> SendData
    ///  Parámetro -> data
    ///  Envia un mensaje JSON data al servidor y espera una respuesta
    ///

    void Client::SendData(QString data)
    {
        if(!data.isEmpty())
        {
            mensajeRecibido = false;
            socket->write(QString(data + "\n").toUtf8());
            socket->waitForBytesWritten(1000);
        }
    }

    ///
    ///  Método -> ReadData
    ///  Lee informacion del servidor y la almacena para que se muestre  en el IDE
    ///

    void Client::ReadData()
    {
        while(socket->canReadLine())
        {

            QString line = QString::fromUtf8(socket->readAll()).trimmed();
            cout << line.toUtf8().constData() << endl;

            QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
            jsonActual = doc.object();
            mensajeRecibido = true;
        }
    }

    ///
    ///  Método -> connected
    ///  Inicia la comunicacion con el servidor
    ///

    void Client::connected()
    {
        socket->write(QString("Client : Server connection has been made (: \n").toUtf8());
        socket->waitForBytesWritten(1000);
    }


