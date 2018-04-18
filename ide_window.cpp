#include "ide_window.h"
#include "ui_ide_window.h"
#include "iostream"
#include "parser.h"
#include <string>
#include <fstream>
#include "client.h"

#include "QJsonObject"
#include "QJsonDocument"
using namespace std;

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
    ui->OutputArea->insertPlainText(">");
    createClient();
}

IDE_Window::~IDE_Window()
{
    delete ui;
}

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

    if (objeto.find("Type").value().toString() == "}" || objeto.find("Type").value().toString() == "{"){
        ui->RunButton->click();
    }
    ui->RAM_view->insertRow(ui->RAM_view->rowCount());
    int fila = ui->RAM_view->rowCount() -1;

    addMemoryDirection(fila,cliente->jsonActual.value("Address").toString());
    addValor(fila,cliente->jsonActual.value("Value").toString());
    addEtiqueta(fila,cliente->jsonActual.value("Label").toString());
    addReferencia(fila);
    addOutputArea();

}

void IDE_Window::addOutputArea(){
    QTextCursor curs = ui->OutputArea->textCursor();
    char * error = new char[strlen("ERROR") + strlen("\n") + 1];
    strcpy(error, "ERROR");
    strcat(error, "\n");
    ui->OutputArea->insertPlainText(error);
    ui->OutputArea->insertPlainText(">");

}
void IDE_Window::addMemoryDirection(int fila, QString address){
    ui->RAM_view->setItem(fila,DIRECCION,new QTableWidgetItem(address));
}
void IDE_Window::addValor(int fila,QString value){
    ui->RAM_view->setItem(fila,VALOR,new QTableWidgetItem(value));
}
void IDE_Window::addEtiqueta(int fila,QString label){
    ui->RAM_view->setItem(fila, ETIQUETA,new QTableWidgetItem(label));
}
void IDE_Window::addReferencia(int fila){
    ui->RAM_view->setItem(fila,REFERENCIAS,new QTableWidgetItem("2"));
}

void IDE_Window::createClient(){
    Client* client = new Client(0,"127.0.0.1",8888);
    cliente = client;


}
void IDE_Window::sendData(string data){
    cliente->SendData(QString(data.c_str()));
}

void IDE_Window::on_pushButton_clicked()
{
    reiniciarParseo();
}
void IDE_Window::reiniciarParseo(){
    *parser.i = 0;
}
