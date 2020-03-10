#ifndef QMYBATTERY_H
#define QMYBATTERY_H

#include <QWidget>
#include <QColor>

class QMyBattery : public QWidget
{
    Q_OBJECT
private:
    QColor mColorBack=Qt::white;
    QColor mColorBorder=Qt::black;
    QColor mColorPower=Qt::green;
    QColor mColorWarning=Qt::red;
    int mPowerLevel{60};
    int mWarnLevel{20};
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    explicit QMyBattery(QWidget *parent = nullptr);
    void setPowerLevel(int pow);
    int powerLevel();
    void setWarnLevel(int warn);
    int warnLevel();
    QSize sizeHint() const override;

signals:
    void powerLevelChanged(int);

};

#endif // QMYBATTERY_H
