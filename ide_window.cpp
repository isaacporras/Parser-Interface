#include "ide_window.h"
#include "ui_ide_window.h"
#include "iostream"
#include "parser.h"
#include "logger.h"
#include <string>
#include <fstream>
#include "client.h"
#include "QJsonObject"
#include "QJsonDocument"
#include <stdio.h>
#include <unistd.h>
using namespace std;

///
///  Clase IDE_Window
///  Interfaz que permite escribir codigo
///

logger *l1 = new logger();

IDE_Window::IDE_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE_Window)

{
    ui->setupUi(this);
    setWindowTitle("C! - IDE");
    QStringList Ram_view_columns;
    Ram_view_columns<<"Dirección"<< "Valor"<<"Etiqueta"<<"Referencias";
    ui->RAM_view->setColumnCount(4);
    ui->RAM_view->setColumnWidth(3, 130);
    ui->RAM_view->setHorizontalHeaderLabels(Ram_view_columns);
    ui->OutputArea->setDocumentTitle("Output");
    ui->OutputArea->setReadOnly(true);
    createClient();
}

IDE_Window::~IDE_Window()
{
    delete ui;
}

///
///  Método -> on_RunButton_clicked
///  Ejecuta el codigo
///

void IDE_Window::on_RunButton_clicked()
{
    string codigo = ui->CodeTextArea->toPlainText().toStdString();
    QJsonObject objeto = parser.parse(codigo);
    if(objeto.find("Type").value().toString() == "struct definition"){
        statusStruct = "struct abierto";
    }
    QJsonDocument doc(objeto);
    QByteArray bytes = doc.toJson();
    const char* charString = bytes.data();
    string someString(charString);
    std::cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<bytes.data()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
    sendData(someString);
    if(cliente->jsonActual.isEmpty()){
        ui->RAM_view->rowCount();
    }
    else {
    if (objeto.find("Type").value().toString() == "}" || objeto.find("Type").value().toString() == "{"){
        ui->RunButton->click();
    }

    if (cliente->jsonActual.value("Print Request").toString()!=NULL){
        string linea = cliente->jsonActual.value("Print Request").toString().toUtf8().constData();
        linea = ">>> " + linea;
        QString qsLinea = QString(linea.c_str());
        addStdOutArea(qsLinea);
    }
    else{
        ui->RAM_view->insertRow(ui->RAM_view->rowCount());
        int fila = ui->RAM_view->rowCount() -1;

        addMemoryDirection(fila,cliente->jsonActual.value("Address").toString());
        addValor(fila,cliente->jsonActual.value("Value").toString());
        addEtiqueta(fila,cliente->jsonActual.value("Label").toString());
        addReferencia(fila);
        //QString linea = QString::fromStdString(someString);
        QString linea = QString("");
        addOutputArea();
    }
    }
}

///
///  Método -> addOutputArea
///  Parametro -> linea
///  Mete la informacion recibida y enviada a un area de texto
///

void IDE_Window::addStdOutArea(QString linea){
    ui->STDOut->appendPlainText(linea);

}

void IDE_Window::addOutputArea(){
    ui->OutputArea->appendPlainText(l1->logMessage(0,"Llamando al servidor..."));
    ui->OutputArea->appendPlainText(l1->logMessage(0,"Enviando la siguiente informacion..."));

}

///
///  Método -> addMemoryDirection
///  Parametro -> fila, address
///  Añade una direccion de memoria address al RAM Live View
///

void IDE_Window::addMemoryDirection(int fila, QString address){
    ui->RAM_view->setItem(fila,DIRECCION,new QTableWidgetItem(address));
}

///
///  Método -> addValor
///  Parametro -> fila, value
///  Añade un valor value al RAM Live View
///

void IDE_Window::addValor(int fila,QString value){
    ui->RAM_view->setItem(fila,VALOR,new QTableWidgetItem(value));
}

///
///  Método -> addEtiqueta
///  Parametro -> fila, label
///  Añade una etiqueta label al RAM Live View
///

void IDE_Window::addEtiqueta(int fila,QString label){
    ui->RAM_view->setItem(fila, ETIQUETA,new QTableWidgetItem(label));
}

///
///  Método -> addReferencia
///  Parametro -> fila
///  Añade una cantidad de referencias al RAM Live View
///

void IDE_Window::addReferencia(int fila){
    ui->RAM_view->setItem(fila,REFERENCIAS,new QTableWidgetItem("1"));
}

///
///  Método -> createClient
///  Instancia la clase Client
///

void IDE_Window::createClient(){
    Client* client = new Client(0,"127.0.0.1",8888);
    cliente = client;
     ui->OutputArea->appendPlainText(l1->logMessage(0,"Estableciendo conexion con el servidor..."));


}

///
///  Método -> sendData
///  Parametro -> data
///  Envia una data en JSON al servidor
///

void IDE_Window::sendData(string data){
    cliente->SendData(QString(data.c_str()));
}

void IDE_Window::on_pushButton_clicked()
{
    reiniciarParseo();
    ui->OutputArea->appendPlainText(l1->logMessage(1,"Se reinicio el sistema..."));
}

///
///  Método -> reiniciarParseo
///  Reinicia el puntero del parser

void IDE_Window::reiniciarParseo(){
    *parser.i = 0;
}
