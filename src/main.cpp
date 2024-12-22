#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
