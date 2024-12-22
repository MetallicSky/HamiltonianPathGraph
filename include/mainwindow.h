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

    void on_spinBox_vNum_valueChanged(int arg1);

    void on_spinBox_eMax_valueChanged(int arg1);

    void on_spinBox_eMin_valueChanged(int arg1);

    void on_comboBox_pStart_currentIndexChanged(int index);

    void on_comboBox_pFinish_currentIndexChanged(int index);

    void on_pushButton_calculate_clicked();

    void on_comboBox_pNum_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui = nullptr;
    GraphScene* scene = nullptr;
    CoordGraphBuilder* graphBuilder = nullptr;
};
#endif // MAINWINDOW_H
