#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    w.setWindowTitle("XML Editor");
    w.resize(920,635);

    return a.exec();

}
