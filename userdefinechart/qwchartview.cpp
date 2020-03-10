#include "qwchartview.h"

QWChartView::QWChartView(QWidget *parent):QChartView(parent)
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setMouseTracking(true);
}

void QWChartView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        beginPoint=event->pos();
    QChartView::mousePressEvent(event);
}

void QWChartView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    emit mouseMovePoint(point);
    QChartView::mouseMoveEvent(event);
}

void QWChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        endPoint=event->pos();
        QRectF rect;
        rect.setTopLeft(this->beginPoint);
        rect.setBottomRight(this->endPoint);
        this->chart()->zoomIn(rect);
    }
    else if(event->button()==Qt::RightButton)
    {
        this->chart()->zoomReset();
    }
    QChartView::mouseReleaseEvent(event);
}

void QWChartView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Plus:
        chart()->zoom(1.2);
        break;
    case Qt::Key_Minus:
        chart()->zoom(0.8);
        break;
    case Qt::Key_Left:
        chart()->scroll(10,0);
        break;
    case Qt::Key_Right:
        chart()->scroll(-10,0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0,-10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0,10);
        break;
    case Qt::Key_PageUp:
        chart()->scroll(0,50);
        break;
    case Qt::Key_PageDown:
        chart()->scroll(0,-50);
        break;
    case Qt::Key_Home:
        chart()->zoomReset();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}