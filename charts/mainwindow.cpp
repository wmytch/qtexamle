#include "mainwindow.h"
#include "ui_mainwindow.h"

#define FixedColumnCount 5
#define InitDataRowCount 6
#define ScoreLevel 5
#define Course 4
#define ColName 0
#define ColMath 1
#define ColChinese 2
#define ColEnglish 3
#define ColAverage 4

QString scoreLevel[ScoreLevel]={"less then 60","60-69","70-79","80-89","at least 90"};
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel=new QStandardItemModel(InitDataRowCount,FixedColumnCount,this);
    initData();
    surveyData();

    connect(theModel,SIGNAL(itemChanged(QStandardItem *)),this,SLOT(on_itemChanged(QStandardItem *)));
    ui->tableView->setModel(theModel);
    initBarChart();
    initPieChart();
    initStackedBar();
    initPercentBar();
    initScatterChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initData()
{
    QStringList header;
    header<<"Name"<<"Math"<<"Chinese"<<"English"<<"Average";
    theModel->setHorizontalHeaderLabels(header);
    qsrand(QTime::currentTime().second());

    for(int i=0;i<theModel->rowCount();i++)
    {
        QString student=QString::asprintf("Student%2d",i+1);
        QStandardItem *item=new QStandardItem(student);
        item->setTextAlignment(Qt::AlignHCenter);
        theModel->setItem(i,ColName,item);

        qreal average=0;
        for(int j=ColMath;j<=ColEnglish;j++)
        {
            qreal score=50.0+(qrand()%50);
            average+=score;
            item=new QStandardItem(QString::asprintf("%.0f",score));
            item->setTextAlignment(Qt::AlignHCenter);
            theModel->setItem(i,j,item);
        }

        item=new QStandardItem(QString::asprintf("%.1f",average/3));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setFlags(item->flags()& !Qt::ItemIsEditable);
        theModel->setItem(i,ColAverage,item);
    }
}

void MainWindow::surveyData()
{
    ui->treeWidget->clear();

    int scoreStat[ScoreLevel][Course]{{0}};

    for(int i=0;i<theModel->rowCount();i++)
    {
        for(int j=ColMath;j<=ColEnglish;j++)
        {
            int curScore=theModel->item(i,j)->text().toInt();
            int level=0;
            if(curScore<60)
            {
                level=0;
            }
            else if(curScore<70)
            {
                level=1;
            }
            else if(curScore<80)
            {
                level=2;
            }
            else if(curScore<90)
            {
                level=3;
            }
            else
            {
                level=4;
            }
            scoreStat[level][j-1]++;
        }
        qreal curScore=theModel->item(i,ColAverage)->text().toFloat();
        int level=0;
        if(curScore<60)
        {
            level=0;
        }
        else if(curScore<70)
        {
            level=1;
        }
        else if(curScore<80)
        {
            level=2;
        }
        else if(curScore<90)
        {
            level=3;
        }
        else
        {
            level=4;
        }
        scoreStat[level][ColAverage-1]++;
    }

    for(int i=0;i<ScoreLevel;i++)
    {
        QTreeWidgetItem *item=new QTreeWidgetItem;
        item->setText(0,scoreLevel[i]);
        for(int j=1;j<=Course;j++)
        {
            item->setText(j,QString::asprintf("%d",scoreStat[i][j-1]));
        }
        ui->treeWidget->addTopLevelItem(item);
    }
}

void MainWindow::on_itemChanged(QStandardItem *item)
{
    if(item->column()<ColMath || item->column()>ColEnglish)
    {
        return;
    }

    int rowNo=item->row();
    qreal avg=0;
    QStandardItem *tmpItem;
    for(int i=ColMath;i<=ColEnglish;i++)
    {
        tmpItem=theModel->item(rowNo,i);
        avg+=tmpItem->text().toDouble();
    }
    avg/=3;
    tmpItem=theModel->item(rowNo,ColAverage);
    tmpItem->setText(QString::asprintf("%.1f",avg));

    surveyData();

    int currentTab=ui->tabWidget->currentIndex();
    on_tabWidget_tabBarClicked(currentTab);
}

void MainWindow::initBarChart()
{
    QChart *chart=new QChart;
    chart->setTitle("Barchart Show");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->barChartView->setChart(chart);
    ui->barChartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildBarChart()
{
    QChart *chart=ui->barChartView->chart();
    chart->removeAllSeries();
    for(auto ax:chart->axes())
    {
        chart->removeAxis(ax);
    }
    chart->axes().clear();
//    chart->removeAxis(chart->axes());
//    chart->removeAxis(chart->axisY());

    QBarSet *setMath=new QBarSet(theModel->horizontalHeaderItem(ColMath)->text());
    QBarSet *setChinese=new QBarSet(theModel->horizontalHeaderItem(ColChinese)->text());
    QBarSet *setEnglish=new QBarSet(theModel->horizontalHeaderItem(ColEnglish)->text());
    QLineSeries *line=new QLineSeries;
    line->setName(theModel->horizontalHeaderItem(ColAverage)->text());
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    line->setPen(pen);

    for(int i=0;i<theModel->rowCount();i++)
    {
        setMath->append(theModel->item(i,ColMath)->text().toInt());
        setChinese->append(theModel->item(i,ColChinese)->text().toInt());
        setEnglish->append(theModel->item(i,ColEnglish)->text().toInt());
        line->append(QPointF(i,theModel->item(i,ColAverage)->text().toFloat()));
    }

    QBarSeries *series=new QBarSeries;
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);
    chart->addSeries(series);
    chart->addSeries(line);

    QStringList categories;
    for(int i=0;i<theModel->rowCount();i++)
    {
        categories<<theModel->item(i,ColName)->text();
    }

    QBarCategoryAxis *axisX=new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setRange(categories[0],categories[categories.count()-1]);
    chart->addAxis(axisX,Qt::AlignBottom);
    series->attachAxis(axisX);
    line->attachAxis(axisX);
    //chart->setAxisX(axisX,series);
    //chart->setAxisX(axisX,line);


    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(0,100);
    axisY->setTitleText("Score");
    axisY->setTickCount(6);
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);
    line->attachAxis(axisY);
//    chart->setAxisY(axisY,series);
//    chart->setAxisY(axisY,line);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::initPieChart()
{
    QChart *chart=new QChart;
    chart->setTitle("PieChart Show");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->pieChartView->setChart(chart);
    ui->pieChartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildPieChart()
{
    QChart *chart=ui->pieChartView->chart();
    chart->removeAllSeries();


    QPieSeries *series=new QPieSeries;
    series->setHoleSize(ui->spinHoleSize->value());

    int colNo=1+ui->boxCourse->currentIndex();
    for(int i=0;i<=4;i++)
    {
        QTreeWidgetItem *item=ui->treeWidget->topLevelItem(i);
        series->append(item->text(0),item->text(colNo).toFloat());
    }

    QPieSlice *slice;
    for(int i=0;i<=4;i++)
    {
        slice=series->slices()[i];
        slice->setLabel(slice->label()+QString::asprintf(": %.0f person,%.1f%%",slice->value(),slice->percentage()*100));
        connect(slice,SIGNAL(hovered(bool)),this,SLOT(on_PieSliceHighlight(bool)));
    }
    slice->setExploded(true);
    series->setLabelsVisible(true);
    chart->addSeries(series);
    chart->setTitle("Piechart----"+ui->boxCourse->currentText());
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
}

void MainWindow::on_PieSliceHighlight(bool show)
{
    QPieSlice *slice=(QPieSlice*)sender();
    slice->setExploded(show);
}

void MainWindow::initStackedBar()
{
    QChart *chart=new QChart;
    chart->setTitle("StackedBar Show");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->stackedChartView->setChart(chart);
    ui->stackedChartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildStackedBar()
{
    QChart *chart=ui->stackedChartView->chart();
    chart->removeAllSeries();
    for(auto ax:chart->axes())
    {
        chart->removeAxis(ax);
    }

    QBarSet *setMath=new QBarSet(theModel->horizontalHeaderItem(ColMath)->text());
    QBarSet *setChinese=new QBarSet(theModel->horizontalHeaderItem(ColChinese)->text());
    QBarSet *setEnglish=new QBarSet(theModel->horizontalHeaderItem(ColEnglish)->text());

    for(int i=0;i<theModel->rowCount();i++)
    {
        setMath->append(theModel->item(i,ColMath)->text().toInt());
        setChinese->append(theModel->item(i,ColChinese)->text().toInt());
        setEnglish->append(theModel->item(i,ColEnglish)->text().toInt());
    }

    QStackedBarSeries *series=new QStackedBarSeries;
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);
    series->setLabelsVisible(true);
    chart->addSeries(series);

    QStringList categories;
    for(int i=0;i<theModel->rowCount();i++)
    {
        categories<<theModel->item(i,ColName)->text();
    }

    QBarCategoryAxis *axisX=new QBarCategoryAxis;
    axisX->append(categories);
    axisX->setRange(categories[0],categories[categories.count()-1]);
    chart->addAxis(axisX,Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(0,300);
    axisY->setTitleText("Total Score");
    axisY->setTickCount(6);
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::initPercentBar()
{
    QChart *chart=new QChart;
    chart->setTitle("PercentBar Show");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->percentChartView->setChart(chart);
    ui->percentChartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildPercentBar()
{
    QChart *chart=ui->percentChartView->chart();
    chart->removeAllSeries();
    for(auto ax:chart->axes())
    {
        chart->removeAxis(ax);
    }

    QBarSet *setMath=new QBarSet(theModel->horizontalHeaderItem(ColMath)->text());
    QBarSet *setChinese=new QBarSet(theModel->horizontalHeaderItem(ColChinese)->text());
    QBarSet *setEnglish=new QBarSet(theModel->horizontalHeaderItem(ColEnglish)->text());

    QStringList categories;
    QTreeWidgetItem *item;
    for(int i=0;i<=4;i++)
    {
        item=ui->treeWidget->topLevelItem(i);
        categories<<item->text(0);
        setMath->append(item->text(ColMath).toFloat());
        setChinese->append(item->text(ColChinese).toFloat());
        setEnglish->append(item->text(ColEnglish).toFloat());
    }

    QPercentBarSeries *series=new QPercentBarSeries;
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);
    series->setLabelsVisible(true);
    chart->addSeries(series);

    QBarCategoryAxis *axisX=new QBarCategoryAxis;
    axisX->append(categories);
    axisX->setRange(categories[0],categories[categories.count()-1]);
    chart->addAxis(axisX,Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(0,100);
    axisY->setTitleText("Percentage");
    axisY->setTickCount(6);
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

}

void MainWindow::initScatterChart()
{
    QChart *chart=new QChart;
    chart->setTitle("ScatterChart Show");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->scatterChartView->setChart(chart);
    ui->scatterChartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildScatterChart()
{
    QChart *chart=ui->scatterChartView->chart();
    chart->removeAllSeries();
    for(auto ax:chart->axes())
    {
        chart->removeAxis(ax);
    }

    QSplineSeries *seriesLine=new QSplineSeries;
    seriesLine->setName("spline");
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    seriesLine->setPen(pen);

    QScatterSeries *series0=new QScatterSeries;
    series0->setName("point");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setBrush(Qt::red);
    series0->setBorderColor(Qt::black);
    series0->setMarkerSize(12);

    qsrand(QTime::currentTime().second());
    for(int i=0;i<10;i++)
    {
        int x=(qrand()%20);
        int y=qrand()%20;
        series0->append(x,y);
        seriesLine->append(x,y);
    }
    chart->addSeries(series0);
    chart->addSeries(seriesLine);

    chart->createDefaultAxes();
    chart->axes()[0]->setTitleText("X");
    chart->axes()[0]->setRange(-2,22);
    chart->axes()[1]->setTitleText("Y");
    chart->axes()[1]->setRange(-2,22);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        buildBarChart();
        break;
    case 1:
        buildPieChart();
        break;
    case 2:
        buildStackedBar();
        break;
    case 3:
        buildPercentBar();
        break;
    case 4:
        buildScatterChart();
        break;
    default:
        break;
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    on_tabWidget_currentChanged(index);
}


void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    on_tabWidget_currentChanged(index);
}
