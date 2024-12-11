#include "mainwindow.h"
#include "coordgraph.h"
#include "coordgraphbuilder.h"
#include "graphscene.h"

#include <QApplication>
#include <QDebug>
#include <QMainWindow>




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
    const int graphSize = 20;
    CoordGraphBuilder myBuilder = CoordGraphBuilder(graphSize);
    myBuilder.fillCircle(500, 500, 100, graphSize);
    myBuilder.connectGraph(2, 6);
    myBuilder.printEdges();
    qDebug().noquote() << myBuilder.isConnected();
    vector<vector<size_t>> paths;
    if (myBuilder.isConnected()) {
        paths = myBuilder.hamiltonianPaths(0, graphSize - 1, 5);
        for (size_t i = 0; i < paths.size(); i++) {
            qDebug().noquote() << "\n\n";
            myBuilder.printPath(paths[i]);
        }
    }
    */

    QApplication app(argc, argv);
    MainWindow mainWindow;
    auto* scene = new GraphScene();
    for (int i = 0; i < 5; ++i) {
        scene->addVertex(i, QPointF(i * 50, 0));
    }
    scene->addEdge(0, 1, 10);
    scene->addEdge(1, 2, 20);
    scene->addEdge(2, 3, 30);
    scene->addEdge(3, 4, 40);

    //auto* view = new GraphView(scene);
    //mainWindow.setCentralWidget(view);
    //mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
