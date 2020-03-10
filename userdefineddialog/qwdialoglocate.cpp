#include "qwdialoglocate.h"
#include "mainwindow.h"
#include "ui_qwdialoglocate.h"

QWdialogLocate::QWdialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWdialogLocate)
{
    ui->setupUi(this);
}

QWdialogLocate::~QWdialogLocate()
{
    delete ui;
}

void QWdialogLocate::on_btnSetText_clicked()
{
    int row=ui->spinBoxRow->value();
    int col=ui->spinBoxColumn->value();
//    MainWindow *parWind=(MainWindow*) parentWidget();
//    parWind->setACellText(row,col,ui->edtCaption->text());
    QString text=ui->edtCaption->text();
    emit changeCellText(row,col,text);
    if(ui->checkBoxRow->isChecked())
    {
        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());
    }
    if(ui->checkBoxColumn->isChecked())
    {
        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());
    }

}

void QWdialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}

void QWdialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBoxRow->setMaximum(rowCount);
    ui->spinBoxColumn->setMaximum(colCount);
}

void QWdialogLocate::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    emit changeActionEnable(true);
//    MainWindow *parWind=(MainWindow*)parentWidget();
//    parWind->setActLocateEnable(true);
//    parWind->setDlgLocateNull();
}

void QWdialogLocate::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    emit changeActionEnable(false);
}