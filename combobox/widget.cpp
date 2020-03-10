#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnInitItems_clicked()
{
    ui->comboBox->clear();
    QStringList strList;
    strList<<"北京"<<"上海"<<"天津"<<"河北"<<"山东"<<"山西";
    ui->comboBox->addItems(strList);
}

void Widget::on_btnClearItems_clicked()
{
    ui->comboBox->clear();
}

void Widget::on_pushButton_clicked()
{
    QMap<QString ,int> cityZip;
    cityZip.insert("北京",10);
    cityZip.insert("上海",21);
    cityZip.insert("天津",22);
    cityZip.insert("大连",411);
    cityZip.insert("锦州",416);
    cityZip.insert("徐州",516);
    cityZip.insert("福州",592);
    cityZip.insert("青岛",532);

    ui->comboBox_2->clear();
    foreach(const QString &str,cityZip.keys())
    {
        ui->comboBox_2->addItem(str,cityZip.value(str));
    }

}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

void Widget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString zip=ui->comboBox_2->currentData().toString();
    ui->plainTextEdit->appendPlainText(arg1+":区号="+zip);
}

void Widget::on_pushButton_3_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_pushButton_2_clicked()
{
    QTextDocument* doc=ui->plainTextEdit->document();
    int cnt=doc->blockCount();
    ui->comboBox->clear();
    for(int i=0;i<cnt;i++)
    {
        QTextBlock textLine=doc->findBlockByNumber(i);
        QString str=textLine.text();
        ui->comboBox->addItem(str);
    }
}

void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu=ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}
