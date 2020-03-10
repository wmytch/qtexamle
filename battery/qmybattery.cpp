#include "qmybattery.h"
#include <QPainter>

QMyBattery::QMyBattery(QWidget *parent) : QWidget(parent)
{

}

void QMyBattery::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QRect rect{0,0,width(),height()};

    painter.setViewport(rect);
    painter.setWindow(0,0,120,50);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(mColorBorder);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(mColorBack);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    rect.setRect(1,1,109,48);
    painter.drawRect(rect);

    brush.setColor(mColorBorder);
    painter.setBrush(brush);
    rect.setRect(110,15,10,20);
    painter.drawRect(rect);

    if(mPowerLevel>mWarnLevel)
    {
        brush.setColor(mColorPower);
        pen.setColor(mColorPower);
    }
    else
    {
        brush.setColor(mColorWarning);
        pen.setColor(mColorWarning);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    if(mPowerLevel>0)
    {
        rect.setRect(5,5,mPowerLevel,40);
        painter.drawRect(rect);
    }

    QFontMetrics textSize(this->font());
    QString powStr=QString::asprintf("%d%%",mPowerLevel);
    QRect textRect=textSize.boundingRect(powStr);
    painter.setFont(this->font());
    pen.setColor(mColorBorder);
    painter.setPen(pen);
    painter.drawText(55-textRect.width()/2,23+textRect.height()/2,powStr);
}

void QMyBattery::setPowerLevel(int pow)
{
    mPowerLevel=pow;
    emit powerLevelChanged(pow);
    repaint();
}

int QMyBattery::powerLevel()
{
    return mPowerLevel;
}

void QMyBattery::setWarnLevel(int warn)
{
    mWarnLevel=warn;
    repaint();
}

int QMyBattery::warnLevel()
{
    return mWarnLevel;
}

QSize QMyBattery::sizeHint() const
{
    int H=this->height();
    int W=H*12/5;
    return QSize{W,H};
}
