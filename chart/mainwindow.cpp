#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();
    prepareData();
    updateFromChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createChart()
{
    QChart *chart=new QChart;
    chart->setTitle("simple function curve");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries;
    QLineSeries *series1=new QLineSeries;
    series0->setName("Sin curve");
    series1->setName("Cos curve");
    curSeries=series0;

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    series0->setPen(pen);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    series1->setPen(pen);
    chart->addSeries(series0);
    chart->addSeries(series1);

    QValueAxis *axisX=new QValueAxis;
    curAxis=axisX;
    axisX->setRange(0,10);
    axisX->setLabelFormat("%.1f");
    axisX->setTickCount(11);
    axisX->setMinorTickCount(4);
    axisX->setTitleText("time(secs)");

    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(-2,2);
    axisY->setLabelFormat("%.2f");
    axisY->setTickCount(5);
    axisY->setTitleText("value");

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
}

void MainWindow::prepareData()
{
    QLineSeries *series0=(QLineSeries*)ui->chartView->chart()->series()[0];
    QLineSeries *series1=(QLineSeries*)ui->chartView->chart()->series()[1];

    series0->clear();
    series1->clear();
    qsrand(QTime::currentTime().second());
    qreal t=0,y1,y2,intv=0.1;
    qreal rd;
    int cnt=100;
    for(int i=0;i<cnt;i++)
    {
        rd=(qrand()%10)-5;
        y1=qSin(t)+rd/50;
        series0->append(t,y1);
        rd=(qrand()%10)-5;
        y2=qCos(t)+rd/50;
        series1->append(t,y2);
        t+=intv;
    }

}

void MainWindow::updateFromChart()
{
    QChart *chart=ui->chartView->chart();
    ui->editTitle->setText(chart->title());
    QMargins mg=chart->margins();
    ui->spinMarginLeft->setValue(mg.left());
    ui->spinMarginRight->setValue(mg.right());
    ui->spinMarginTop->setValue(mg.top());
    ui->spinMarginBottom->setValue(mg.bottom());
}


//void MainWindow::createChart()
//{
//    QChartView *chartView=new QChartView(this);
//    QChart *chart=new QChart();
//    chart->setTitle("Simple function curve");
//    chartView->setChart(chart);
//    this->setCentralWidget(chartView);

//    QLineSeries *series0=new QLineSeries;
//    QLineSeries *series1=new QLineSeries;
//    series0->setName("Sin curve");
//    series1->setName("Cos curve");
////    chart->addSeries(series0);
////    chart->addSeries(series1);

//    qreal t=0,y1,y2,intv=0.1;
//    int cnt=100;
//    for(int i=0;i<cnt;i++)
//    {
//        y1=qSin(t);
//        series0->append(t,y1);
//        y2=qSin(t+20);
//        series1->append(t,y2);
//        t+=intv;
//    }

//    QValueAxis *axisX=new QValueAxis;
//    axisX->setRange(0,10);
//    axisX->setTitleText("time(secs)");

//    QValueAxis *axisY=new QValueAxis;
//    axisY->setRange(-2,2);
//    axisY->setTitleText("value");

////    chart->setAxisX(axisX,series0);
////    chart->setAxisY(axisY,series0);
////    chart->setAxisX(axisX,series1);
////    chart->setAxisY(axisY,series1);

//    chart->addAxis(axisX,Qt::AlignBottom);
//    chart->addAxis(axisY,Qt::AlignLeft);
//    chart->addSeries(series0);
//    chart->addSeries(series1);
//    series0->attachAxis(axisX);
//    series0->attachAxis(axisY);
//    series1->attachAxis(axisX);
//    series1->attachAxis(axisY);

//}