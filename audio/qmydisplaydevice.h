#ifndef QMYDISPLAYDEVICE_H
#define QMYDISPLAYDEVICE_H
#include <QtCharts>
#include <QIODevice>

class QmyDisplayDevice : public QIODevice
{
    Q_OBJECT
public:
    QmyDisplayDevice(QXYSeries *series,qint64 pointsCount,QObject *parent=0);
protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
private:
    QXYSeries *mSeries;
    qint64 range=4000;
signals:
    void updateBlockSize(qint64 blockSize);
};

#endif // QMYDISPLAYDEVICE_H
