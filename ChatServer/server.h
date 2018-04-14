#ifndef SERVER_H
    #define SERVER_H

    #include <QtNetwork>
    #include <QObject>
    #include <QtNetwork/QTcpServer>
    #include <QtNetwork/QTcpSocket>



        class Server: public QTcpServer
        {

            Q_OBJECT
            public:

              Server(QObject * parent = 0 , quint16 port = 8888);
              virtual  ~Server();

            private slots:

              void acceptConnection();
              void startRead();
              void disconnected();

            public:

              QTcpSocket * client;
              Server *servidor;

        };


    #endif // SERVER_H
