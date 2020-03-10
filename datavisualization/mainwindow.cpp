#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    initGraph3D();
    initScatter();
    graph3D=scatter;
    QSplitter *splitter=new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->groupBox);
    splitter->addWidget(graphContainer);
    this->setCentralWidget(splitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initScatter()
{
    scatter=new Q3DScatter;
    graphContainer=QWidget::createWindowContainer(scatter);
    auto proxy=new QScatterDataProxy;
    scatterSeries=new QScatter3DSeries(proxy);
    scatterSeries->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    scatterSeries->setMeshSmooth(true);
    scatter->addSeries(scatterSeries);

    scatter->axisX()->setTitle("axis X");
    scatter->axisX()->setTitleVisible(true);
    scatter->axisY()->setTitle("axis Y");
    scatter->axisY()->setTitleVisible(true);
    scatter->axisZ()->setTitle("axis Z");
    scatter->axisZ()->setTitleVisible(true);
    scatter->activeTheme()->setLabelBackgroundEnabled(false);
    scatterSeries->setMesh(QAbstract3DSeries::MeshSphere);
    scatterSeries->setItemSize(0.2);

    int N=41;
    int itemCount=N*N;
    auto dataArray=new QScatterDataArray;
    dataArray->resize(itemCount);
    auto ptrToDataArray=&dataArray->first();

    float x,y,z;
    int i,j;
    x=-10;
    for(i=1;i<=N;i++)
    {
        y=-10;
        for(j=1;j<=N;j++)
        {
            z=qSqrt(x*x+y*y);
            if(z!=0)
                z=10*qSin(z)/z;
            else
                z=10;
            ptrToDataArray->setPosition(QVector3D(x,z,y));
            ptrToDataArray++;
            y+=0.5;
        }
        x+=0.5;
    }
    scatterSeries->dataProxy()->resetArray(dataArray);
}
//void MainWindow::initGraph3D()
//{
//    graph3D=new Q3DBars;
//    graphContainer=QWidget::createWindowContainer(graph3D);

//    QStringList rowLabs;
//    QStringList colLabs;
//    rowLabs<<"row1"<<"row2"<<"row3";
//    colLabs<<"col1"<<"col2"<<"col3"<<"col4"<<"col5";

//    QValue3DAxis *axisV=new QValue3DAxis;
//    axisV->setTitle("Value");
//    axisV->setTitleVisible(true);

//    QCategory3DAxis *axisRow=new QCategory3DAxis;
//    axisRow->setTitle("Row axis");
//    axisRow->setLabels(rowLabs);
//    axisRow->setTitleVisible(true);

//    auto axisCol=new QCategory3DAxis;
//    axisCol->setTitle("Column axis");
//    axisCol->setLabels(colLabs);
//    axisCol->setTitleVisible(true);

//    graph3D->setValueAxis(axisV);
//    graph3D->setRowAxis(axisRow);
//    graph3D->setColumnAxis(axisCol);

//    series=new QBar3DSeries;
//    series->setMesh(QAbstract3DSeries::MeshCylinder);
//    series->setItemLabelFormat("(@rowLabel,@colLabel):%.1f");
//    graph3D->addSeries(series);

//    auto dataSet=new QBarDataArray;
//    dataSet->reserve(rowLabs.count());

//    auto dataRow=new QBarDataRow;
//    *dataRow<<1<<2<<3<<4<<5;
//    dataSet->append(dataRow);

//    auto dataRow2=new QBarDataRow;
//    *dataRow<<5<<5<<5<<5<<5;
//    dataSet->append(dataRow2);

//    auto dataRow3=new QBarDataRow;
//    *dataRow3<<1<<5<<9<<5<<1;
//    dataSet->append(dataRow3);

//    series->dataProxy()->resetArray(dataSet);
//}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    auto cameraPos=Q3DCamera::CameraPreset(index);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value)
    auto xRot=ui->sliderH->value();
    auto yRot=ui->sliderV->value();
    auto zoom=ui->sliderZoom->value();
    graph3D->scene()->activeCamera()->setCameraPosition(xRot,yRot,zoom);
}

void MainWindow::on_sliderV_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

void MainWindow::on_sliderZoom_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    auto currentTheme=graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    graph3D->activeTheme()->setGridEnabled(checked);
}

void MainWindow::on_checkBox_8_clicked(bool checked)
{
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}

void MainWindow::on_checkBox_3_clicked(bool checked)
{
    graph3D->activeTheme()->setLabelBorderEnabled(checked);
}
