#include "qwdialogsize.h"
#include "ui_qwdialogsize.h"
#include <QMessageBox>

QWdialogSize::QWdialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWdialogSize)
{
    ui->setupUi(this);
}

QWdialogSize::~QWdialogSize()
{
    QMessageBox::information(this,"提示","设置表格行列数对话框被删除");
    delete ui;
}

int QWdialogSize::rowCount()
{
    return ui->spinBoxRow->value();
}

int QWdialogSize::columnCount()
{
    return ui->spinBoxColumn->value();
}

void QWdialogSize::setRowColumn(int row, int column)
{
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColumn->setValue(column);
}