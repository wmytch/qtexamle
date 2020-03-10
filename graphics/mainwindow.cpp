#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QGraphicsItem>
#include <QColorDialog>
#include <QFontDialog>
#include <QGraphicsItemGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labViewCord=new QLabel("View cord:");
    labViewCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labViewCord);

    labSceneCord=new QLabel("Scene cord:");
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);

    labItemCord=new QLabel("Item cord:");
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);

    labItemInfo=new QLabel("ItemInfo cord:");
    labItemInfo->setMinimumWidth(200);
    ui->statusbar->addWidget(labItemInfo);

    scene=new QGraphicsScene(-300,-200,600,200);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    this->setCentralWidget(ui->graphicsView);

    QObject::connect(ui->graphicsView,SIGNAL(mouseMovePoint(QPoint)),
                     this,SLOT(on_mouseMovePoint(QPoint)));
    QObject::connect(ui->graphicsView,SIGNAL(mouseClicked(QPoint)),
                     this,SLOT(on_mouseClicked(QPoint)));
    QObject::connect(ui->graphicsView,SIGNAL(mouseDoubleClicked(QPoint)),
                     this,SLOT(on_mouseDoubleClicked(QPoint)));
    QObject::connect(ui->graphicsView,SIGNAL(keyPress(QKeyEvent*)),
                     this,SLOT(on_keyPress(QKeyEvent*)));

    qsrand(QTime::currentTime().second());

}

MainWindow::~MainWindow()
{
    delete ui;
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
    QGraphicsItem *item=scene->itemAt(pointScene,ui->graphicsView->transform());
    if(item)
    {
        QPointF pointItem=item->mapFromScene(pointScene);
        labItemCord->setText(QString::asprintf("Item cord:%.0f,%.0f",pointItem.x(),pointItem.y()));
        labItemInfo->setText(item->data(itemDesc).toString()
                             +",itemID=" + item->data(itemID).toString());
    }
}

template<typename T>
void setBrushColor(T* item)
{
    QColor color=item->brush().color();
    color=QColorDialog::getColor(color,NULL,"select brush color");
    if(color.isValid())
    {
        item->setBrush(QBrush(color));
    }
}
void MainWindow::on_mouseDoubleClicked(QPoint point)
{
    QPointF pointScene=ui->graphicsView->mapToScene(point);
    QGraphicsItem *item=scene->itemAt(pointScene,ui->graphicsView->transform());
    if(!item)
        return;
    switch(item->type())
    {
    case QGraphicsRectItem::Type:
    {
        QGraphicsRectItem *theItem=qgraphicsitem_cast<QGraphicsRectItem*>(item);
        setBrushColor(theItem);
        break;
    }
    case QGraphicsEllipseItem::Type:
    {
        QGraphicsEllipseItem *theItem=qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        setBrushColor(theItem);
        break;
    }
    case QGraphicsPolygonItem::Type:
    {
        QGraphicsPolygonItem *theItem=qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
        setBrushColor(theItem);
        break;
    }
    case QGraphicsLineItem::Type:
    {
        QGraphicsLineItem *theItem=qgraphicsitem_cast<QGraphicsLineItem*>(item);
        QPen pen=theItem->pen();
        QColor color=theItem->pen().color();
        color=QColorDialog::getColor(color,this,"select line color");
        if(color.isValid())
        {
            pen.setColor(color);
            theItem->setPen(pen);
        }
        break;
    }
    case QGraphicsTextItem::Type:
    {
        QGraphicsTextItem *theItem=qgraphicsitem_cast<QGraphicsTextItem*>(item);
        QFont font=theItem->font();
        bool ok=false;
        font=QFontDialog::getFont(&ok,font,this,"set font");
        if(ok)
            theItem->setFont(font);
        break;
    }
    }
}

void MainWindow::on_keyPress(QKeyEvent *event)
{
    if(scene->selectedItems().count()!=1)
    {
        return;
    }

    QGraphicsItem *item=scene->selectedItems().at(0);
    switch(event->key())
    {
    case Qt::Key_Delete:
    {
        scene->removeItem(item);
        break;
    }
    case Qt::Key_Space:
    {
        item->setRotation(90+item->rotation());
        break;
    }
    case Qt::Key_PageUp:
    {
        item->setScale(0.1+item->scale());
        break;
    }
    case Qt::Key_PageDown:
    {
        item->setScale(-0.1+item->scale());
        break;
    }
    case Qt::Key_Left:
    {
        item->setX(-1+item->x());
        break;
    }
    case Qt::Key_Right:
    {
        item->setX(1+item->x());
        break;
    }
    case Qt::Key_Up:
    {
        item->setY(-1+item->y());
        break;
    }
    case Qt::Key_Down:
    {
        item->setY(1+item->y());
        break;
    }
    }

}
void MainWindow::on_actAddEllipse_triggered()
{
    QGraphicsEllipseItem *item=new QGraphicsEllipseItem(-50,-30,100,60);
    item->setFlags(QGraphicsItem::ItemIsMovable
                   |QGraphicsItem::ItemIsSelectable
                   |QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::blue));
    item->setZValue(++frontZ);
    item->setPos(-50+(qrand()%100),-50+qrand()%100);
    item->setData(itemID,++seqNum);
    item->setData(itemDesc,"Ellipse");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void MainWindow::on_actRotateLeft_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==1)
    {
        QGraphicsItem* item=scene->selectedItems()[0];
        item->setRotation(-30+item->rotation());
    }
    else
    {
        ui->graphicsView->rotate(-30);
    }
}

void MainWindow::on_actRotateRight_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==1)
    {
        QGraphicsItem* item=scene->selectedItems()[0];
        item->setRotation(30+item->rotation());
    }
    else
    {
        ui->graphicsView->rotate(30);
    }
}

void MainWindow::on_actRestore_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==1)
    {
        QGraphicsItem* item=scene->selectedItems().at(0);
        item->resetTransform();
    }
    else
    {
        ui->graphicsView->resetTransform();
    }
}

void MainWindow::on_actZoomIn_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==1)
    {
        QGraphicsItem* item=scene->selectedItems()[0];
        item->setScale(0.1+item->scale());
    }
    else
    {
        ui->graphicsView->scale(1.1,1.1);
    }
}

void MainWindow::on_actZoomOut_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==1)
    {
        QGraphicsItem* item=scene->selectedItems()[0];
        item->setScale(-0.1+item->scale());
    }
    else
    {
        ui->graphicsView->scale(0.9,0.9);
    }
}

void MainWindow::on_actPutFront_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt>0)
    {
        QGraphicsItem* item=scene->selectedItems()[0];
        item->setZValue(++frontZ);
    }
}

void MainWindow::on_actPutBack_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt>0)
    {
        QGraphicsItem* item=scene->selectedItems()[0];
        item->setZValue(--backZ);
    }
}

void MainWindow::on_actCompose_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt>1)
    {
        QGraphicsItemGroup *group=new QGraphicsItemGroup;
        scene->addItem(group);
        QGraphicsItem *item;
        for(int i=0;i<cnt;i++)
        {
            item=scene->selectedItems()[0];
            item->setSelected(false);
            item->clearFocus();
            group->addToGroup(item);
        }
        group->setFlags(QGraphicsItem::ItemIsMovable
                        |QGraphicsItem::ItemIsSelectable
                        |QGraphicsItem::ItemIsFocusable);
        group->setZValue(++frontZ);
        scene->clearSelection();
        group->setSelected(true);

    }
}

void MainWindow::on_actDecompose_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==1)
    {
        QGraphicsItemGroup *group=(QGraphicsItemGroup*)scene->selectedItems()[0];
        scene->destroyItemGroup(group);
    }
}

void MainWindow::on_actDelete_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt>0)
    {
        QGraphicsItem *item;
        for(int i=0;i<cnt;i++)
        {
            item=scene->selectedItems()[0];
            scene->removeItem(item);
        }
    }
}
