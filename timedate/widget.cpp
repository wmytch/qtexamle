#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    fTimer=new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000);
    connect(fTimer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_calendarWidget_selectionChanged()
{
    QDate dt=ui->calendarWidget->selectedDate();
    QString str=dt.toString("yyyy年M月d日");
    ui->editCalendar->setText(str);
}

void Widget::on_btnGetTime_clicked()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    ui->timeEdit->setTime(curDateTime.time());
    ui->lineTime->setText(curDateTime.toString("hh:mm:ss"));
    ui->dateEdit->setDate(curDateTime.date());
    ui->lineDate->setText(curDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(curDateTime);
    ui->lineDateTime->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void Widget::on_btnSetDateTime_clicked()
{
    QString str=ui->lineDateTime->text();
    str=str.trimmed();
    if(!str.isEmpty())
    {
        QDateTime datetime=QDateTime::fromString(str,"yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(datetime);
        ui->timeEdit->setTime(datetime.time());
        ui->lineTime->setText(datetime.toString("hh:mm:ss"));
        ui->dateEdit->setDate(datetime.date());
        ui->lineDate->setText(datetime.toString("yyyy-MM-dd"));
    }
}

void Widget::on_timer_timeout()
{
    QTime curTime=QTime::currentTime();
    ui->lcdHour->display(curTime.hour());
    ui->lcdMinute->display(curTime.minute());
    ui->lcdSecond->display(curTime.second());
    int va=ui->progressBar->value();
    va++;
    if(va>100)
        va=0;
    ui->progressBar->setValue(va);
}
void Widget::on_btnStart_clicked()
{
    fTimer->start();
    fTimeCounter.start();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnSetIntv->setEnabled(false);
}

void Widget::on_btnStop_clicked()
{
    fTimer->stop();
    int tmMsec=fTimeCounter.elapsed();
    int ms=tmMsec%1000;
    int sec=tmMsec/1000;
    QString str=QString::asprintf("流逝时间: %d秒，%d毫秒",sec,ms);
    ui->labElaps->setText(str);
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnSetIntv->setEnabled(true);
}
