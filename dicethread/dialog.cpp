#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&mThread,SIGNAL(started()),this,SLOT(onThreadStarted()));
    connect(&mThread,SIGNAL(finished()),this,SLOT(onThreadFinished()));
    connect(&mThread,SIGNAL(newValue(int,int)),this,SLOT(onNewValue(int,int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onThreadStarted()
{
    ui->label->setText("Thread status:thread started");
}

void Dialog::onThreadFinished()
{
    ui->label->setText("Thread status:thread finished");
}

void Dialog::onNewValue(int seq,int diceValue)
{
    QString str=QString::asprintf("No %d dicing,result is:%d",seq,diceValue);
    ui->plainTextEdit->appendPlainText(str);
}
void Dialog::on_btnStartThread_clicked()
{
    mThread.start();
    ui->btnStartThread->setEnabled(false);
    ui->btnEnd->setEnabled(true);
    ui->btnStart->setEnabled(true);
    ui->btnPause->setEnabled(false);
}

void Dialog::on_btnStart_clicked()
{
    mThread.beginDice();
    ui->btnStart->setEnabled(false);
    ui->btnPause->setEnabled(true);
}

void Dialog::on_btnPause_clicked()
{
    mThread.pauseDice();
    ui->btnStart->setEnabled(true);
    ui->btnPause->setEnabled(false);
}

void Dialog::on_btnEnd_clicked()
{
    mThread.stopThread();
    mThread.wait();
    ui->btnStartThread->setEnabled(true);
    ui->btnEnd->setEnabled(false);
    ui->btnStart->setEnabled(false);
    ui->btnPause->setEnabled(false);

}


void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if(mThread.isRunning())
    {
        mThread.stopThread();
        mThread.wait();
    }
    event->accept();
}