#ifndef SERVER_H
    #define SERVER_H

    #include <QtNetwork>
    #include <QObject>
    #include <QtNetwork/QTcpServer>
    #include <QtNetwork/QTcpSocket>
#include "variablelist.h"



        class Server: public QTcpServer
        {

            Q_OBJECT
            public:

              Server(QObject * parent = 0 , quint16 port = 8888);
              virtual  ~Server();
              void sendMessage(QString data);

            private slots:

              void acceptConnection();
              void startRead();
              void disconnected();

            public:
              bool firstTime;
              QTcpSocket * client;
              Server *servidor;
              variablelist *vl;


        };


    #endif // SERVER_H
