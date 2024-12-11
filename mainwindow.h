#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphscene.h"
#include "coordgraphbuilder.h"
#include <QMainWindow>
#include <QGraphicsScene>



QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_generate_clicked();

private:
    Ui::MainWindow *ui;
    GraphScene* scene;
    CoordGraphBuilder* graph;
};
#endif // MAINWINDOW_H
