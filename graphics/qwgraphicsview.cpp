#include "qwgraphicsview.h"

QWGraphicsView::QWGraphicsView(QWidget *parent)
{
    Q_UNUSED(parent)
}

void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    emit mouseMovePoint(point);
    QGraphicsView::mouseMoveEvent(event);
}

void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint point=event->pos();
        emit mouseClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}

void QWGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint point=event->pos();
        emit mouseDoubleClicked(point);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void QWGraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}