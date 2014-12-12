#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w = MainWindow();
//    MainWindow w();
    MainWindow w;
    w.show();




    return a.exec();
}
