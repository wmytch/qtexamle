#include "qwdialogheaders.h"
#include "ui_qwdialogheaders.h"

QWdialogHeaders::QWdialogHeaders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWdialogHeaders)
{
    ui->setupUi(this);
    model=new QStringListModel;
    ui->listView->setModel(model);
}

QWdialogHeaders::~QWdialogHeaders()
{
    delete ui;
}

void QWdialogHeaders::setHeaderList(QStringList &headers)
{
    model->setStringList(headers);
}

QStringList QWdialogHeaders::headerList()
{
    return model->stringList();
}