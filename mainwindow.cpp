#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new GraphScene(this);
    graphBuilder = new CoordGraphBuilder(ui->spinBox_vNum->value());
    auto* graphView = new GraphView(scene);
    graphView->setBackgroundBrush(Qt::white);
    graphView->setObjectName(ui->graphicsView->objectName());
    graphView->setGeometry(ui->graphicsView->geometry());
    graphView->setParent(ui->centralwidget);

    // Delete the original graphicsView and assign the new one
    delete ui->graphicsView;
    ui->graphicsView = graphView;
    on_pushButton_generate_clicked();

    on_spinBox_vNum_valueChanged(ui->spinBox_vNum->value());
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_generate_clicked()
{
    scene->clear();
    graphBuilder->clear();
    graphBuilder->repopulate(ui->spinBox_vNum->value());
    graphBuilder->fillCircle(500, 500, 500, graphBuilder->getGraph().size());
    graphBuilder->connectGraph(ui->spinBox_eMin->value(), ui->spinBox_eMax->value());
    CoordGraph cGraph = graphBuilder->getGraph();
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

    // Center the view on the scene content
    ui->graphicsView->centerOn(scene->sceneRect().center());

    // Adjust the zoom to fit the graph within the view
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    ui->comboBox_pNum->clear();
    ui->textEdit_console->clear();
    if (graphBuilder->isConnected()) {
        ui->textEdit_console->setText("Looks like all vertices are interconnected, you can calculate hamiltonian path!");
        ui->pushButton_calculate->setEnabled(true);
    }
    else {
        ui->textEdit_console->setText("Uh oh! Some of the vertices are separated from the rest. If you want to calculate hamiltonian path, regenerate the graph!");
        ui->pushButton_calculate->setEnabled(false);
    }
}


void MainWindow::on_spinBox_vNum_valueChanged(int arg1)
{
    ui->spinBox_eMax->setMaximum(arg1);

    ui->comboBox_pStart->clear();
    ui->comboBox_pFinish->clear();
    for (size_t i = 0; i < ui->spinBox_vNum->value(); i++) {
        ui->comboBox_pStart->addItem(QString::number(i));
        ui->comboBox_pFinish->addItem(QString::number(i));
    }
    ui->comboBox_pStart->setCurrentIndex(0);
    ui->comboBox_pFinish->setCurrentIndex(ui->spinBox_vNum->value() - 1);
}


void MainWindow::on_spinBox_eMax_valueChanged(int arg1)
{
    ui->spinBox_eMin->setMaximum(arg1);
}


void MainWindow::on_spinBox_eMin_valueChanged(int arg1)
{
    ui->spinBox_eMax->setMinimum(arg1);
}


void MainWindow::on_comboBox_pStart_currentIndexChanged(int index)
{
    if (ui->comboBox_pFinish->currentIndex() == index) {
        ui->pushButton_calculate->setEnabled(false);
    }
    else {
        ui->pushButton_calculate->setEnabled(true);
    }
}


void MainWindow::on_comboBox_pFinish_currentIndexChanged(int index)
{
    if (ui->comboBox_pStart->currentIndex() == index) {
        ui->pushButton_calculate->setEnabled(false);
    }
    else {
        ui->pushButton_calculate->setEnabled(true);
    }
}


void MainWindow::on_pushButton_calculate_clicked()
{
    ui->comboBox_pNum->setEnabled(true);
    ui->comboBox_pNum->clear();
    vector< vector < size_t > > paths = graphBuilder->hamiltonianPaths(ui->comboBox_pStart->currentIndex(), ui->comboBox_pFinish->currentIndex(), ui->spinBox_pAmount->value());
    for (size_t i = 0; i < paths.size(); i++) {
        ui->comboBox_pNum->addItem("T: " + QString::number(graphBuilder->totalWeight(paths[i])));
    }
    ui->textEdit_console->clear();
    ui->textEdit_console->setText(QString::number(paths.size()) + " paths was found. Choose which one to display");
}


void MainWindow::on_comboBox_pNum_currentIndexChanged(int index)
{
    if (index < 0) {
        return;
    }
    ui->textEdit_console->clear();
    QString data = QString::fromStdString(graphBuilder->pathToString(index));
    ui->textEdit_console->setText(data);
    scene->selectPath(graphBuilder->getPath(index));
}

