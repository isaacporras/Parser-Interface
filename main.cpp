
#include "ide_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IDE_Window w;
    w.show();

    return a.exec();
}
