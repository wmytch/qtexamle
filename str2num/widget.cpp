#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QObject::connect(ui->SliderGreen,SIGNAL(valueChanged(int)),this,SLOT(on_SliderRed_valueChanged(int)));
    QObject::connect(ui->SliderBlue,SIGNAL(valueChanged(int)),this,SLOT(on_SliderRed_valueChanged(int)));
    QObject::connect(ui->SliderAlpha,SIGNAL(valueChanged(int)),this,SLOT(on_SliderRed_valueChanged(int)));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnCal_clicked()
{
    QString str=ui->editNum->text();
    int num=str.toInt();
    str=ui->editPrice->text();
    float price=str.toFloat();
    float total=num*price;
    str=str.asprintf("%.2f",total);
    ui->editTotal->setText(str);
}

void Widget::on_btnDec_clicked()
{
    QString str=ui->editDec->text();
    int val=str.toInt();
    str=str.setNum(val,16);
    str=str.toUpper();
    ui->editHex->setText(str);
    str=str.setNum(val,2);
    ui->editBin->setText(str);
}

void Widget::on_btnBin_clicked()
{
    QString str=ui->editBin->text();
    bool ok;
    int val=str.toInt(&ok,2);
    str=QString::number(val,10);
    ui->editDec->setText(str);

    str=str.setNum(val,16);
    str=str.toUpper();
    ui->editHex->setText(str);
}

void Widget::on_btnHex_clicked()
{
    QString str=ui->editHex->text();
    bool ok;
    int val=str.toInt(&ok,16);
    str=QString::number(val,10);
    ui->editDec->setText(str);

    str=str.setNum(val,2);
    str=str.toUpper();
    ui->editBin->setText(str);
}

void Widget::on_btnCal_2_clicked()
{
    int num=ui->spinNum->value();
    float price=ui->spinPrice->value();
    float total=num*price;
    ui->spinTotal->setValue(total);
}

void Widget::on_btnDec_2_clicked()
{
    int val=ui->spinDec->value();
    ui->spinBin->setValue(val);
    ui->spinHex->setValue(val);
}

void Widget::on_btnBin_2_clicked()
{
    int val=ui->spinBin->value();
    ui->spinDec->setValue(val);
    ui->spinHex->setValue(val);
}

void Widget::on_btnHex_2_clicked()
{
    int val=ui->spinHex->value();
    ui->spinDec->setValue(val);
    ui->spinBin->setValue(val);
}

void Widget::on_SliderRed_valueChanged(int value)
{
    Q_UNUSED(value);
    QColor color;
    int R=ui->SliderRed->value();
    int G=ui->SliderGreen->value();
    int B=ui->SliderBlue->value();
    int alpha=ui->SliderAlpha->value();
    color.setRgb(R,G,B,alpha);
    QPalette pal=ui->textEdit->palette();
    pal.setColor(QPalette::Base,color);
    ui->textEdit->setPalette(pal);
}

void Widget::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}

void Widget::on_radiaBtnDec_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setDecMode();
}

void Widget::on_radioBtnBin_clicked()
{
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setBinMode();
}

void Widget::on_radioBtnOct_clicked()
{
    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->setOctMode();
}

void Widget::on_radioBtnHex_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setHexMode();
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->progressBarH->setValue(value);
}

void Widget::on_horizontalScrollBar_valueChanged(int value)
{
    ui->progressBarH->setValue(value);
}

void Widget::on_verticalSlider_valueChanged(int value)
{
    ui->progressBarV->setValue(value);
}

void Widget::on_verticalScrollBar_valueChanged(int value)
{
    ui->progressBarV->setValue(value);
}
