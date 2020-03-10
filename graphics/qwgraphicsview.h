#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>

class QWGraphicsView:public QGraphicsView
{
    Q_OBJECT
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
public:
    QWGraphicsView(QWidget *parent=nullptr);
signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);
    void mouseDoubleClicked(QPoint point);
    void keyPress(QKeyEvent *event);
};

#endif // QWGRAPHICSVIEW_H
