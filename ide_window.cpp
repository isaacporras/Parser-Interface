#include "ide_window.h"
#include "ui_ide_window.h"
#include "iostream"
#include "parser.h"

IDE_Window::IDE_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE_Window)
{
    ui->setupUi(this);

}

IDE_Window::~IDE_Window()
{
    delete ui;
}

void IDE_Window::on_ParseButton_clicked()
{
    parser.parse(ui->CodeTextArea->toPlainText().toStdString());

}
