#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qwintspindelegate.h"

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
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_actOpen_triggered();

private:
    Ui::MainWindow *ui;

    QLabel *labCurFile;
    QLabel *labCellPos;
    QLabel *labCellText;
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;

    QWintSpinDelegate intSpinDelegate;

    void initModelFromStringList(QStringList&);


};
#endif // MAINWINDOW_H
