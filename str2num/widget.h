#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_btnCal_clicked();

    void on_btnDec_clicked();

    void on_btnBin_clicked();

    void on_btnHex_clicked();

    void on_btnCal_2_clicked();

    void on_btnDec_2_clicked();

    void on_btnBin_2_clicked();

    void on_btnHex_2_clicked();

    void on_SliderRed_valueChanged(int value);

    void on_dial_valueChanged(int value);

    void on_radiaBtnDec_clicked();

    void on_radioBtnBin_clicked();

    void on_radioBtnOct_clicked();

    void on_radioBtnHex_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalScrollBar_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_verticalScrollBar_valueChanged(int value);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
