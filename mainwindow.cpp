#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    // Create the GraphScene
    auto* scene = new GraphScene(this);
    graph = new CoordGraphBuilder(ui->spinBox_vNum->value());
    graph->fillCircle(500, 500, 500, graph->getGraph().size());
    graph->connectGraph(ui->spinBox_eMin->value(), ui->spinBox_eMax->value());
    CoordGraph cGraph = graph->getGraph();
    for (size_t i = 0; i < cGraph.size(); ++i) {
        pair<int, int> coord = cGraph.getCoord(i);
        scene->addVertex(i, QPointF(coord.first, coord.second));
    }
    for (size_t i = 0; i < cGraph.size(); ++i) {
        vector <pair<size_t, int>> edges = cGraph.getEdges(i);
        for (size_t j = 0; j < edges.size(); j++) {
            pair<size_t, int> edge = edges[j];
            if (edge.first > i) {
                scene->addEdge(i, edge.first, edge.second);
            }
        }
    }

    // Set the scene bounding rectangle
    scene->setSceneRect(scene->itemsBoundingRect());

    // Replace the default QGraphicsView with your custom GraphView
    auto* graphView = new GraphView(scene);
    graphView->setBackgroundBrush(Qt::white);
    graphView->setObjectName(ui->graphicsView->objectName());
    graphView->setGeometry(ui->graphicsView->geometry());
    graphView->setParent(ui->centralwidget);

    // Delete the original graphicsView and assign the new one
    delete ui->graphicsView;
    ui->graphicsView = graphView;

    // Center the view on the scene content
    graphView->centerOn(scene->sceneRect().center());

    // Adjust the zoom to fit the graph within the view
    graphView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_generate_clicked()
{

}

