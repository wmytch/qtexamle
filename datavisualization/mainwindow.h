#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDataVisualization/QtDataVisualization>
using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *graphContainer;
//    Q3DBars *graph3D;
    Q3DScatter *graph3D;
    QBar3DSeries *series;
    Q3DScatter *scatter;
    QScatter3DSeries *scatterSeries;
    void initGraph3D();
    void initScatter();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_sliderH_valueChanged(int value);

    void on_sliderV_valueChanged(int value);

    void on_sliderZoom_valueChanged(int value);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_8_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
