#ifndef QWBATTERY_H
#define QWBATTERY_H

#include <QWidget>
#include <QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT QwBattery : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int powerLevel READ powerLevel WRITE setPowerLevel NOTIFY powerLevelChanged DESIGNABLE true)
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
    void setPowerLevel(int pow);
    int powerLevel();
    void setWarnLevel(int warn);
    int warnLevel();
    QSize sizeHint() const override;

signals:
    void powerLevelChanged(int);
public:
    QwBattery(QWidget *parent = 0);
};

#endif // QWBATTERY_H
