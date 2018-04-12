#include <iostream>
#include <QCoreApplication>

#include "client.h"

using namespace std;

int main(int argc, char *argv[])
    {
        QCoreApplication a(argc, argv);

        Client* client = new Client(0,"127.0.0.1",4000);

        string line;
        while(line!="exit"){
            cout << "Message : ";
            cin >> line;
            client->SendData(QString(line.c_str()));
        }

        return a.exec();
    }
