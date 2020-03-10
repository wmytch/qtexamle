#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

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

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QRect rect{0,0,width(),height()};
    painter.setViewport(rect);
    painter.setWindow(0,0,100,50);
    painter.drawRect(rect);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    battery.setPowerLevel(value);
    battery.repaint();
//    this->repaint();
}
