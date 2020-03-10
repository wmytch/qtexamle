#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    void on_btnSetHeader_clicked();

    void on_btnInitData_clicked();

    void on_btnSetRowCount_clicked();

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();

    void on_btnAppendRow_clicked();

    void on_btnDelCurRow_clicked();

    void on_chkTabEditable_clicked(bool checked);

    void on_btnReadToEdit_clicked();

    void on_chkRowHeader_clicked(bool checked);

    void on_chkColHeader_clicked(bool checked);

    void on_chkRowColor_clicked(bool checked);

    void on_rBtnSelectRow_clicked();

    void on_rBtnSelectItem_clicked();

private:
    Ui::MainWindow *ui;

    enum FieldColNum{colName=0,colSex,colBirth,colNation,colScore,colPartyM};
    enum CellType{ctName=1000,ctSex,ctBirth,ctNation,ctPartyM,ctScore};

    QLabel *labCellIndex;
    QLabel *labCellType;
    QLabel *labStuId;

    void createItemsARow(int rowNo,QString Name,QString Sex,QDate birth,QString Nation,bool isPM,int score);
};
#endif // MAINWINDOW_H
