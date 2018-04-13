#ifndef IDE_WINDOW_H
#define IDE_WINDOW_H


#include <QMainWindow>
#include "parser.h"
#include "client.h"
namespace Ui {
class IDE_Window;
}

class IDE_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit IDE_Window(QWidget *parent = 0);
    ~IDE_Window();
    Parser parser;
    Client *cliente;

private slots:
     void on_RunButton_clicked();
     void addOutputArea();
     void addMemoryDirection(int fila);
     void addValor(int fila);
     void addEtiqueta(int fila);
     void addReferencia(int fila);
     void createClient();
     void getParserData();

private:
    Ui::IDE_Window *ui;
    enum Columna{
        DIRECCION,VALOR,ETIQUETA, REFERENCIAS
    };
};

#endif // IDE_WINDOW_H
