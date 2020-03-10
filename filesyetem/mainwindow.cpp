#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model);
    ui->listView->setModel(model);
    ui->tableView->setModel(model);
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->listView,SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->tableView,SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->chkIsDir->setChecked(model->isDir(index));
    ui->labFileName->setText(model->fileName(index.siblingAtColumn(0)));
    ui->labFilePath->setText(model->filePath(index));
    ui->labFileType->setText(model->type(index));
    int size=model->size(index)/1024;
    if(size<1024)
    {
        ui->labFileSize->setText(QString("%1 KB").arg(size));
    }
    else
    {
        ui->labFileSize->setText(QString::asprintf("%.1f MB",size/1024.0));
    }
}
