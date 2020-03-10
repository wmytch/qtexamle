#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_calendarWidget_selectionChanged();

    void on_btnGetTime_clicked();

    void on_btnSetDateTime_clicked();

    void on_timer_timeout();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::Widget *ui;
    QTimer *fTimer;
    QTime fTimeCounter;
};
#endif // WIDGET_H
