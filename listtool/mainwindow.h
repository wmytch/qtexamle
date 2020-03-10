#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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
    void on_actListInit_triggered();

    void on_actListInsert_triggered();

    void on_actListDel_triggered();

    void on_actSelAll_triggered();

    void on_actSelNone_triggered();

    void on_actSelInvs_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);


    void on_actListAppend_triggered();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);



private:
    Ui::MainWindow *ui;

    void createSelectionPopMenu();
};
#endif // MAINWINDOW_H
