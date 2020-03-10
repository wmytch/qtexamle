#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labViewCord=new QLabel("View cord:");
    labViewCord->setMidLineWidth(150);
    ui->statusbar->addWidget(labViewCord);
    labSceneCord=new QLabel("Scene cord:");
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);
    labItemCord=new QLabel("Item cord");
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);

    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    QObject::connect(ui->graphicsView,SIGNAL(mouseMovePoint(QPoint)),this,SLOT(on_mouseMovePoint(QPoint)));
    QObject::connect(ui->graphicsView,SIGNAL(mouseClicked(QPoint)),this,SLOT(on_mouseClicked(QPoint)));
    initGrahpicsSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGrahpicsSystem()
{
    QRectF rect(-200,-100,400,200);
    scene=new QGraphicsScene(rect);
    ui->graphicsView->setScene(scene);
    QGraphicsRectItem *item=new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsFocusable);
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene->addItem(item);

    QGraphicsEllipseItem *item2=new QGraphicsEllipseItem(-100,-50,200,100);
    item2->setPos(0,0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    QGraphicsEllipseItem *item3=new QGraphicsEllipseItem(-50,-50,100,100);
    item3->setPos(rect.right(),rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);

    scene->clearSelection();
}
void MainWindow::on_mouseMovePoint(QPoint point)
{
    labViewCord->setText(QString::asprintf("View cord:%d,%d",point.x(),point.y()));
    QPointF pointScene=ui->graphicsView->mapToScene(point);
    labSceneCord->setText(QString::asprintf("Scene cord:%.0f,%.0f",pointScene.x(),pointScene.y()));
}

void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene=ui->graphicsView->mapToScene(point);
    QGraphicsItem *item=nullptr;
    item=scene->itemAt(pointScene,ui->graphicsView->transform());
    if(item)
    {
        QPointF pointItem=item->mapFromScene(pointScene);
        labItemCord->setText(QString::asprintf("Item cord:%.0f,%.0f",pointItem.x(),pointItem.y()));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    ui->labViewSize->setText(QString::asprintf("Graphics View cord,left top always is(0,0),width=%d,height=%d",
                                               ui->graphicsView->width(),ui->graphicsView->height()));
    QRectF rectF=ui->graphicsView->sceneRect();
    ui->labSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect(left,top,width,height)=(%.0f,%.0f,%.0f,%.0f)",
                                                rectF.left(),rectF.top(),rectF.width(),rectF.height()));
}