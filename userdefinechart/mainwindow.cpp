#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->graphicsView);
    labXYValue=new QLabel("X=, Y= ");
    labXYValue->setMinimumWidth(200);
    ui->statusbar->addWidget(labXYValue);
    createChart();
    prepareData();
    QObject::connect(ui->graphicsView,SIGNAL(mouseMovePoint(QPoint)),this,SLOT(on_mouseMovePoint(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    auto pt=ui->graphicsView->chart()->mapToValue(point);
    labXYValue->setText(QString::asprintf("X=%.1f,Y=%.2f",pt.x(),pt.y()));
}

void MainWindow::on_actZoomIn_triggered()
{
    ui->graphicsView->chart()->zoom(1.2);
}

void MainWindow::on_actOriginSize_triggered()
{
    ui->graphicsView->chart()->zoomReset();
}

void MainWindow::on_actZoomOut_triggered()
{
    ui->graphicsView->chart()->zoom(0.8);
}

void MainWindow::on_lengendMarkerClicked()
{
    auto marker=qobject_cast<QLegendMarker*>(sender());
    switch(marker->type())
    {
    case QLegendMarker::LegendMarkerTypeXY:
    {
        marker->series()->setVisible(!marker->series()->isVisible());
        marker->setVisible(true);
    }
    default:
        break;
    }
}

void MainWindow::createChart()
{
    QChart *chart=new QChart;
    chart->setTitle("simple function curve");
    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries;
    QLineSeries *series1=new QLineSeries;
    series0->setName("Sin curve");
    series1->setName("Cos curve");
//    curSeries=series0;

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
//    curAxis=axisX;
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
    QLineSeries *series0=(QLineSeries*)ui->graphicsView->chart()->series()[0];
    QLineSeries *series1=(QLineSeries*)ui->graphicsView->chart()->series()[1];

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

