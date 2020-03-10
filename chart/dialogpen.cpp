#include "dialogpen.h"
#include "ui_dialogpen.h"

DialogPen::DialogPen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPen)
{
    ui->setupUi(this);
}

DialogPen::~DialogPen()
{
    delete ui;
}

QPen DialogPen::getPen(QPen initPen,bool &ok)
{
    DialogPen *dlg=new DialogPen;
    dlg->setPen(initPen);
    QPen pen;
    int ret=dlg->exec();
    if(ret==QDialog::Accepted)
    {
        pen=dlg->getPen();
        ok=true;
    }
    else
    {
        pen=initPen;
        ok=false;
    }
    delete dlg;
    return pen;
}

void DialogPen::setPen(QPen pen)
{
    this->pen=pen;
    ui->spinWidth->setValue(pen.width());
    int i=static_cast<int>(pen.style());
    ui->comboPenStyle->setCurrentIndex(i);
    QColor color=pen.color();
    ui->btnColor->setAutoFillBackground(true);
    QString str=QString::asprintf("background color:rgb(%d,%d,%d)",color.red(),color.green(),color.blue());
    ui->btnColor->setStyleSheet(str);
}

QPen DialogPen::getPen()
{
    this->pen.setStyle(Qt::PenStyle(ui->comboPenStyle->currentIndex()));
    this->pen.setWidth(ui->spinWidth->value());
    QColor color=ui->btnColor->palette().color(QPalette::Button);
    this->pen.setColor(color);
    return this->pen;
}