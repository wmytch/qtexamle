#ifndef QMYVIDEOWIDGET_H
#define QMYVIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QMouseEvent>

class QmyVideoWidget : public QVideoWidget
{

private:
    QMediaPlayer *thePlayer;
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
public:
    explicit QmyVideoWidget(QWidget *parent=nullptr);
    void setMediaPlayer(QMediaPlayer *player);
};

#endif // QMYVIDEOWIDGET_H
