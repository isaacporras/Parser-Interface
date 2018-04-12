#ifndef SERVER_H
    #define SERVER_H

    #include <QtNetwork>
    #include <QObject>
    #include <QtNetwork/QTcpServer>
    #include <QtNetwork/QTcpSocket>

    /*namespace NetworkArdic
    {*/

        class Server: public QTcpServer
        {

            Q_OBJECT
            public:

              Server(QObject * parent = 0 , quint16 port = 4000);
              virtual  ~Server();

            private slots:

              void acceptConnection();
              void startRead();
              void disconnected();

            private:

              QTcpSocket * client;

        };

    //}

    #endif // SERVER_H
