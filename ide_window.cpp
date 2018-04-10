#include "ide_window.h"
#include "ui_ide_window.h"
#include "iostream"
#include "parser.h"
#include <string>
#include <fstream>
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


}

IDE_Window::~IDE_Window()
{
    delete ui;
}

void IDE_Window::on_RunButton_clicked()
{
    parser.parse(ui->CodeTextArea->toPlainText().toStdString());
    ui->RAM_view->insertRow(ui->RAM_view->rowCount());
    int fila = ui->RAM_view->rowCount() -1;
    addMemoryDirection(fila);
    addValor(fila);
    addEtiqueta(fila);
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
void IDE_Window::addMemoryDirection(int fila){
    ui->RAM_view->setItem(fila,DIRECCION,new QTableWidgetItem("0x00F12"));
}
void IDE_Window::addValor(int fila){
    ui->RAM_view->setItem(fila,VALOR,new QTableWidgetItem("9"));
}
void IDE_Window::addEtiqueta(int fila){
    ui->RAM_view->setItem(fila, ETIQUETA,new QTableWidgetItem("x"));
}
void IDE_Window::addReferencia(int fila){
    ui->RAM_view->setItem(fila,REFERENCIAS,new QTableWidgetItem("2"));
}
