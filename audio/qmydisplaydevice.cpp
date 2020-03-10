#include "qmydisplaydevice.h"

QmyDisplayDevice::QmyDisplayDevice(QXYSeries *series,qint64 pointsCount,QObject *parent)
{
    mSeries=series;
    range=pointsCount;
}

qint64 QmyDisplayDevice::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)
    return -1;
}

qint64 QmyDisplayDevice::writeData(const char *data, qint64 len)
{
    QVector<QPointF> oldPoints=mSeries->pointsVector();
    QVector<QPointF> points;
    if(oldPoints.count()<range)
    {
        points=mSeries->pointsVector();
    }
    else
    {
        for(int i=len;i<oldPoints.count();i++)
        {
            points.append(QPointF(i-len,oldPoints[i].y()));
        }
    }

    qint64 size=points.count();
    for(int k=0;k<len;k++)
    {
        points.append(QPointF(k+size,(quint8)data[k]));
    }

    mSeries->replace(points);
    emit updateBlockSize(len);
    return len;
}
