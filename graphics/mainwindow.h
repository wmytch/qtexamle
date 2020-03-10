#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QPoint>
#include <QKeyEvent>

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
    Ui::MainWindow *ui;
    static const int itemID=1;
    static const int itemDesc=2;
    int seqNum=0;
    int frontZ=0;
    int backZ=0;
    QGraphicsScene *scene;
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;
    QLabel * labItemInfo;

private slots:
    void on_mouseMovePoint(QPoint point);
    void on_mouseClicked(QPoint point);
    void on_mouseDoubleClicked(QPoint point);
    void on_keyPress(QKeyEvent *event);
    void on_actAddEllipse_triggered();
    void on_actRotateLeft_triggered();
    void on_actRotateRight_triggered();
    void on_actRestore_triggered();
    void on_actZoomIn_triggered();
    void on_actZoomOut_triggered();
    void on_actPutFront_triggered();
    void on_actPutBack_triggered();
    void on_actCompose_triggered();
    void on_actDecompose_triggered();
    void on_actDelete_triggered();
};
#endif // MAINWINDOW_H
