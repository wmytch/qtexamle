#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qwdialogheaders.h"
#include "qwdialogsize.h"
#include "qwdialoglocate.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDlgLocateNull();

public slots:
    void setACellText(int row,int column,QString &text);
    void setActLocateEnable(bool enable);

signals:
    void cellIndexChanged(int rowNo,int colNo);

private slots:

    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

    void on_actTab_Locate_triggered();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    QWdialogHeaders *dlgSetHeaders=nullptr;
    QWdialogLocate *dlgLocate=nullptr;

    void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H
