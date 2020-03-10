#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwchartview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QLabel *labXYValue;
    void createChart();
    void prepareData();
private:
    Ui::MainWindow *ui;
private slots:
    void on_lengendMarkerClicked();
    void on_mouseMovePoint(QPoint point);
    void on_actZoomIn_triggered();
    void on_actOriginSize_triggered();
    void on_actZoomOut_triggered();
};
#endif // MAINWINDOW_H
