#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitterMain);

    labCellIndex=new QLabel("当前单元格坐标：",this);
    labCellIndex->setMinimumWidth(250);
    labCellType=new QLabel("当前单元格类型：",this);
    labCellType->setMinimumWidth(200);
    labStuId=new QLabel("学生ID：",this);
    labStuId->setMinimumWidth(200);
    ui->statusbar->addWidget(labCellIndex);
    ui->statusbar->addWidget(labCellType);
    ui->statusbar->addWidget(labStuId);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSetHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"姓名"<<"性别"<<"出生日期"<<"民族"<<"分数"<<"是否党员";
    ui->tableWidget->setColumnCount(headerText.count());
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        headerItem=new QTableWidgetItem(headerText.at(i));
        QFont font=headerItem->font();
        font.setBold(true);
        font.setPointSize(12);
        headerItem->setForeground(Qt::red);
        headerItem->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
}

void MainWindow::on_btnInitData_clicked()
{
    QString strName,strSex;
    bool isParty=false;
    QDate birth;
    birth.setDate(1970,1,1);
    ui->tableWidget->clearContents();
    int rows=ui->tableWidget->rowCount();
    for(int i=0;i<rows;i++)
    {
        strName=QString::asprintf("学生%d",i+1);
        if(i%2==0)
        {
            strSex="男";
        }
        else
        {
            strSex="女";
        }
        createItemsARow(i,strName,strSex,birth,"汉",isParty,70);
        birth=birth.addDays(20);
        isParty=!isParty;
    }
}

void MainWindow::createItemsARow(int rowNo, QString Name, QString Sex, QDate birth, QString Nation, bool isPM, int score)
{
    QTableWidgetItem *item;
    QString str;
    uint stuID=201605000;

    item=new QTableWidgetItem(Name,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    stuID+=rowNo;
    item->setData(Qt::UserRole,QVariant(stuID));
    ui->tableWidget->setItem(rowNo,MainWindow::colName,item);

    item=new QTableWidgetItem(Sex,MainWindow::ctSex);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colSex,item);

    str=birth.toString("yyyy-MM-dd");
    item=new QTableWidgetItem(str,MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colBirth,item);

    item=new QTableWidgetItem(Nation,MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colNation,item);

    item=new QTableWidgetItem("党员",MainWindow::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    if(isPM)
    {
        item->setCheckState(Qt::Checked);
    }
    else
    {
        item->setCheckState(Qt::Unchecked);
    }
    item->setBackground(Qt::yellow);
    ui->tableWidget->setItem(rowNo,MainWindow::colPartyM,item);

    str.setNum(score);
    item=new QTableWidgetItem(str,MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colScore,item);
}
void MainWindow::on_btnSetRowCount_clicked()
{
    if(ui->spinRowCount->value())
    {
        ui->tableWidget->setRowCount(ui->spinRowCount->value());
    }
}

void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    QTableWidgetItem *item=ui->tableWidget->item(currentRow,currentColumn);
    if(!item)
        return;
    labCellIndex->setText(QString::asprintf("当前单元格坐标：%d行，%d列",currentRow+1,currentColumn+1));
    int cellType=item->type();
    labCellType->setText(QString::asprintf("当前单元格类型：%d",cellType));
    item=ui->tableWidget->item(currentRow,MainWindow::colName);
    int ID=item->data(Qt::UserRole).toInt();
    labStuId->setText(QString::asprintf("学生ID：%d",ID));
}

void MainWindow::on_btnInsertRow_clicked()
{
    int curRow=ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(curRow);
    createItemsARow(curRow,"新学生","男",QDate::fromString("1990-1-1","yyyy-M-d"),"苗族",true,70);
}

void MainWindow::on_btnAppendRow_clicked()
{
    int curRow=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(curRow);
    createItemsARow(curRow,"新生","女",QDate::fromString("1991-1-1","yyyy-M-d"),"满族",false,70);

}

void MainWindow::on_btnDelCurRow_clicked()
{
    int curRow=ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(curRow);
}

void MainWindow::on_chkTabEditable_clicked(bool checked)
{
    if(checked)
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
    else
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_btnReadToEdit_clicked()
{
    QString str;
    QTableWidgetItem *cellItem;
    ui->plainTextEdit->clear();
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        str=QString::asprintf("第%d行：",i+1);
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            cellItem=ui->tableWidget->item(i,j);
            str=str+cellItem->text()+"   ";
        }
        cellItem=ui->tableWidget->item(i,colPartyM);
        if(cellItem->checkState()==Qt::Checked)
            str+="党员";
        else
            str+="群众";
        ui->plainTextEdit->appendPlainText(str);
    }
}

void MainWindow::on_chkRowHeader_clicked(bool checked)
{
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}

void MainWindow::on_chkColHeader_clicked(bool checked)
{
    ui->tableWidget->verticalHeader()->setVisible(checked);
}

void MainWindow::on_chkRowColor_clicked(bool checked)
{
    ui->tableWidget->setAlternatingRowColors(checked);
}

void MainWindow::on_rBtnSelectRow_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::on_rBtnSelectItem_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}
