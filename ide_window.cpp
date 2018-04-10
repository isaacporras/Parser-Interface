#include "ide_window.h"
#include "ui_ide_window.h"
#include "iostream"
#include "parser.h"

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
    addOutputArea();

}
void IDE_Window::addOutputArea(){
    QTextCursor curs = ui->OutputArea->textCursor();

    ui->OutputArea->insertPlainText("hola\n");
    ui->OutputArea->insertPlainText(">");


}
