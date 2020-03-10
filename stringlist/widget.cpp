#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList strList;
    strList<<"北京"<<"上海"<<"天津"<<"河北"<<"山东"<<"四川"<<"重庆";
    model=new QStringListModel(this);
    model->setStringList(strList);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnListInsert_clicked()
{
    QModelIndex index=ui->listView->currentIndex();
    model->insertRow(index.row());
    model->setData(index,"inserted item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}

void Widget::on_btnDelCurItem_clicked()
{
    QModelIndex index=ui->listView->currentIndex();
    model->removeRow(index.row());
}

void Widget::on_btnClearList_clicked()
{
    model->removeRows(0,model->rowCount());
}

void Widget::on_btnListAppend_clicked()
{
    model->insertRow(model->rowCount());
    QModelIndex index=model->index(model->rowCount()-1,0);
    model->setData(index,"new item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}

void Widget::on_btnTextImport_clicked()
{
    QStringList tmpList=model->stringList();
    ui->plainTextEdit->clear();
    for(int i=0;i<tmpList.count();i++)
    {
        ui->plainTextEdit->appendPlainText(tmpList[i]);
    }
}

void Widget::on_listView_clicked(const QModelIndex &index)
{
    ui->label->setText(QString::asprintf("current item:row=%d,column=%d",index.row(),index.column()));
}
