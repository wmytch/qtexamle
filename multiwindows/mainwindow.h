#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actEmbedWidget_triggered();

    void on_actIndWidget_triggered();

    void on_actEmbedWindow_triggered();

    void on_actIndWindow_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
};
#endif // MAINWINDOW_H
