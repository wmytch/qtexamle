#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDataWidgetMapper>
#include "qwcomboboxdelegate.h"
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
    QSqlDatabase DB;
    QSqlTableModel *tabModel{nullptr};
    QSqlQueryModel *queryModel{nullptr};
    QSqlRelationalTableModel *relationModel;
    QItemSelectionModel *theSelection{nullptr};
    QItemSelectionModel *querySelection{nullptr};
    QItemSelectionModel *relationSelection;
    QDataWidgetMapper *dataMapper{nullptr};
    QWComboBoxDelegate delegateSex;
    QWComboBoxDelegate delegateDepart;
    QSqlRecord mRecord;

    enum Mode {table,query,relation} curMode;
    enum QueryMode {UPDATE,INSERT} queryMode;
    void openTable();
    void openQuery();
    void openRelation();
    void setHead(QSqlQueryModel *theModel);
    void getFieldNames();
    void updateRecord();
    void setUpdateRecord();
    void setInsertRecord();
    void getRecordData();

private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_currentRowChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_actOpenDB_triggered();
    void on_actAppend_triggered();
    void on_actInsert_triggered();
    void on_actDelete_triggered();
    void on_actSubmit_triggered();
    void on_actRevert_triggered();
    void on_actSetPhoto_triggered();
    void on_actClearPhoto_triggered();
    void on_actSalary_triggered();
    void on_comboFields_currentIndexChanged(int index);
    void on_rbAsc_clicked();
    void on_rbDesc_clicked();
    void on_rbMan_clicked();
    void on_rbWoman_clicked();
    void on_rbBoth_clicked();
    void on_actOpenTable_triggered();
    void on_actOpenQuery_triggered();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_tableView_clicked(const QModelIndex &index);
    void on_actRelation_triggered();
};
#endif // MAINWINDOW_H
