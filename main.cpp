#include "mainwindow.h"
#include<QFile>
#include<QDebug>
#include"constants.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}

