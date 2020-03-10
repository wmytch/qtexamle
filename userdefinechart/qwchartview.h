#ifndef QWCHARTVIEW_H
#define QWCHARTVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts/QtCharts>

using namespace QtCharts;
class QWChartView : public QChartView
{
    Q_OBJECT
private:
    QPoint beginPoint;
    QPoint endPoint;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
public:
    QWChartView(QWidget *parent=0);
signals:
    void mouseMovePoint(QPoint point);
};

#endif // QWCHARTVIEW_H
