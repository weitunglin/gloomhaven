#include "mainwindow.h"
#include "pregame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    PreGame window1;
    window1.show();
    return a.exec();
}
