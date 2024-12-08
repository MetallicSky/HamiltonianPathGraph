#include "mainwindow.h"
#include "coordgraph.h"
#include "coordgraphbuilder.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    /*
    CoordGraph mainGraph(10);
    const int min = 1;
    const int max = 100;
    for (size_t i = 0; i < mainGraph.size(); i++) {
        for (size_t j = i + 1; j < mainGraph.size(); j++) {
            int randNum = rand()%(max-min + 1) + min;
            mainGraph.setWeight(i, j, randNum);
        }
    }
    */

    CoordGraphBuilder myBuilder = CoordGraphBuilder(100);
    myBuilder.fillCircle(500, 500, 100, 100);
    myBuilder.connectGraph(2, 6);
    myBuilder.printEdges();
    qDebug().noquote() << myBuilder.isConnected();
    vector<vector<size_t>> paths = myBuilder.hamiltonianPaths(0, 1, 10);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
