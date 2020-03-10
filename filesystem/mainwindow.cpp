#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpenIODevice_triggered()
{
    QString curPath=QDir::currentPath();
    QString dlgTitle="Open a file";
    QString filter="source file(*.h *.cpp);;text file(*.txt);;all file(*.*)";
    QString fileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(fileName.isEmpty())
        return;
    openTextByIODevice(fileName);
}

bool MainWindow::openTextByIODevice(QString &fileName)
{
    QFile file(fileName);
    if(!file.exists())
    {
        return false;
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return false;
    }
    ui->textEditDevice->setPlainText(file.readAll());
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

void MainWindow::on_actSaveIODevice_triggered()
{
    QString curPath=QDir::currentPath();
    QString dlgTitle="Save File";
    QString filter="header(*.h);;C++ file(*.cpp);;all file(*.*)";
    QString fileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(fileName.isEmpty())
    {
        return;
    }
    saveTextByIODevice(fileName);
}

bool MainWindow::saveTextByIODevice(QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return false;
    }
    QString str=ui->textEditDevice->toPlainText();
    QByteArray strBytes=str.toUtf8();
    file.write(strBytes,strBytes.length());
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

bool MainWindow::openTextByStream(const QString &fileName)
{
    QFile file(fileName);
    if(!file.exists())
    {
        return false;
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return false;
    }
    QTextStream stream(&file);
    ui->textEditStream->setPlainText(stream.readAll());
    file.close();
    ui->tabWidget->setCurrentIndex(1);
    return true;
}

bool MainWindow::saveTextByStream(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return false;
    }
    QTextStream stream(&file);
    QString str=ui->textEditStream->toPlainText();
    stream<<str;
    file.close();
    return true;
}
void MainWindow::on_actOpenStream_triggered()
{
    QString curPath=QDir::currentPath();
    QString dlgTitle="Open a file";
    QString filter="source file(*.h *.cpp);;text file(*.txt);;all file(*.*)";
    QString fileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(fileName.isEmpty())
        return;
    openTextByStream(fileName);
}

void MainWindow::on_actSaveStream_triggered()
{
    QString curPath=QDir::currentPath();
    QString dlgTitle="Save File";
    QString filter="header(*.h);;C++ file(*.cpp);;all file(*.*)";
    QString fileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(fileName.isEmpty())
    {
        return;
    }
    saveTextByStream(fileName);
}
