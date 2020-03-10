#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    theModel=new QStandardItemModel(2,6,this);
    theSelection=new QItemSelectionModel(theModel);
    connect(theSelection,SIGNAL(currentChanged(const QModelIndex&,const QModelIndex&)),this,SLOT(on_currentChanged(const QModelIndex&,const QModelIndex&)));
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setItemDelegateForColumn(0,&intSpinDelegate);

    labCellPos=new QLabel("");
    labCurFile=new QLabel("");
    labCellText=new QLabel("");
    ui->statusbar->addWidget(labCurFile);
    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(labCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current,const QModelIndex &previous)
{
    Q_UNUSED(previous)
    if(current.isValid())
    {
        labCellPos->setText(QString::asprintf("当前单元格：%d行，%d列",current.row(),current.column()));
        QStandardItem *aItem=theModel->itemFromIndex(current);
        this->labCellText->setText("单元格内容："+aItem->text());
        QFont font=aItem->font();
        ui->actFontBold->setChecked(font.bold());
    }
}
void MainWindow::on_actOpen_triggered()
{
    QString curPath=QCoreApplication::applicationDirPath();
    QString aFileName=QFileDialog::getOpenFileName(this,"open file",curPath,"will data(*.txt);;allfile(*.*)");
    if(aFileName.isEmpty())
        return;
    QStringList fFileContent;
    QFile aFile(aFileName);

    if(aFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        while(!aStream.atEnd())
        {
            QString str=aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        this->labCurFile->setText("current file:"+aFileName);
        initModelFromStringList(fFileContent);
    }
}

void MainWindow::initModelFromStringList(QStringList &aFileContent)
{
    int rowCnt=aFileContent.count();
    theModel->setRowCount(rowCnt-1);

    QString header=aFileContent[0];
    QStringList headerList=header.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList);

    QStandardItem *aItem;
    QStringList tmpList;
    int j;
    for(int i=1;i<rowCnt;i++)
    {
        QString aLineText=aFileContent.at(i);
        tmpList=aLineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for(j=0;j<6-1;j++)
        {
            aItem=new QStandardItem(tmpList.at(j));
            theModel->setItem(i-1,j,aItem);
        }
        aItem=new QStandardItem(headerList.at(j));
        aItem->setCheckable(true);
        if(tmpList[j]=="0")
        {
            aItem->setCheckState(Qt::Unchecked);
        }
        else
        {
            aItem->setCheckState(Qt::Checked);
        }
        theModel->setItem(i-1,j,aItem);
    }

}