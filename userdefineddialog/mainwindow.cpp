#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel=new QStandardItemModel(this);
    theSelection=new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actTab_SetSize_triggered()
{
    QWdialogSize *dlgTableSize=new QWdialogSize(this);
    Qt::WindowFlags flags=dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags|Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->setRowColumn(theModel->rowCount(),theModel->columnCount());
    int ret=dlgTableSize->exec();
    if(ret==QDialog::Accepted)
    {
        int cols=dlgTableSize->columnCount();
        theModel->setColumnCount(cols);
        int rows=dlgTableSize->rowCount();
        theModel->setRowCount(rows);
    }
    delete dlgTableSize;
}

void MainWindow::on_actTab_SetHeader_triggered()
{
    if(!dlgSetHeaders)
    {
        dlgSetHeaders=new QWdialogHeaders(this);
    }
    if(dlgSetHeaders->headerList().count()!=theModel->columnCount())
    {
        QStringList strList;
        for(int i=0;i<theModel->columnCount();i++)
        {
            strList.append(theModel->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
        }
        dlgSetHeaders->setHeaderList(strList);
    }

    int ret=dlgSetHeaders->exec();
    if(ret==QDialog::Accepted)
    {
        QStringList strList=dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}

void MainWindow::on_actTab_Locate_triggered()
{
//    ui->actTab_Locate->setEnabled(false);
    dlgLocate=new QWdialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags=dlgLocate->windowFlags();
    dlgLocate->setWindowFlags(flags|Qt::WindowStaysOnTopHint);
    dlgLocate->setSpinRange(theModel->rowCount(),theModel->columnCount());
    QModelIndex curIndex=theSelection->currentIndex();
    if(curIndex.isValid())
    {
        dlgLocate->setSpinValue(curIndex.row(),curIndex.column());
    }
    connect(dlgLocate,SIGNAL(changeCellText(int,int,QString&)),this,SLOT(setACellText(int,int,QString&)));
    connect(dlgLocate,SIGNAL(changeActionEnable(bool)),this,SLOT(setActLocateEnable(bool)));
    connect(this,SIGNAL(cellIndexChanged(int,int)),dlgLocate,SLOT(setSpinValue(int,int)));
    dlgLocate->show();
}

void MainWindow::setACellText(int row, int column, QString &text)
{
    QModelIndex index=theModel->index(row,column);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select);
    theModel->setData(index,text,Qt::DisplayRole);
}
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(),index.column());
//    if(dlgLocate)
//    {
//        dlgLocate->setSpinValue(index.row(),index.column());
//    }
}

void MainWindow::setActLocateEnable(bool enable)
{
    ui->actTab_Locate->setEnabled(enable);
}

void MainWindow::setDlgLocateNull()
{
    dlgLocate=nullptr;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton result=QMessageBox::question(this,"确认","确定要退出本程序吗？",
                                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                                      QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }

}