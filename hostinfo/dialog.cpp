#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString hostName=QHostInfo::localHostName();
    ui->plainTextEdit->appendPlainText("Local host name:"+hostName+"\n");
    QHostInfo hostInfo=QHostInfo::fromName(hostName);

    QList<QHostAddress> addList=hostInfo.addresses();
    if(!addList.isEmpty())
    {
        for(auto host:addList)
        {
            if(ui->checkBox->isChecked() && QAbstractSocket::IPv4Protocol!=host.protocol())
            {
                continue;
            }
            else
            {
                ui->plainTextEdit->appendPlainText("Protocol:"+protocolName(host.protocol()));
                ui->plainTextEdit->appendPlainText("Host IP Address:"+host.toString());
                ui->plainTextEdit->appendPlainText("");
            }
        }
    }
}

QString Dialog::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    switch(protocol)
    {
    case QAbstractSocket::IPv4Protocol:
        return "IPv4";
    case QAbstractSocket::IPv6Protocol:
        return "IPv6";
    case QAbstractSocket::AnyIPProtocol:
        return "Any IP Procotol";
    default:
        return "Unknown IP protocol";
    }
}

void Dialog::on_pushButton_5_clicked()
{
    ui->plainTextEdit->clear();
}


void Dialog::on_pushButton_4_clicked()
{
    QString hostName=ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText("Looking for host info for host:"+hostName);
    QHostInfo::lookupHost(hostName,this,SLOT(lookedUpHostInfo(QHostInfo)));
}

void Dialog::lookedUpHostInfo(const QHostInfo &remoteHost)
{
    QList<QHostAddress> addList=remoteHost.addresses();
    if(!addList.isEmpty())
    {
        for(auto host:addList)
        {
            if(ui->checkBox->isChecked() && QAbstractSocket::IPv4Protocol!=host.protocol())
            {
                continue;
            }
            else
            {
                ui->plainTextEdit->appendPlainText("Protocol:"+protocolName(host.protocol()));
                ui->plainTextEdit->appendPlainText("Host IP Address:"+host.toString());
                ui->plainTextEdit->appendPlainText("");
            }
        }
    }
}

void Dialog::on_pushButton_3_clicked()
{
    QList<QNetworkInterface> list=QNetworkInterface::allInterfaces();
    for(auto hostIF:list)
    {
        if(!hostIF.isValid())
            continue;
        ui->plainTextEdit->appendPlainText("Interface Name:"+hostIF.humanReadableName());
        ui->plainTextEdit->appendPlainText("Hardware Address:"+hostIF.hardwareAddress());
        for(auto entry:hostIF.addressEntries())
        {
            ui->plainTextEdit->appendPlainText("IP Address:"+entry.ip().toString());
            ui->plainTextEdit->appendPlainText("Subnet Mask:"+entry.netmask().toString());
            ui->plainTextEdit->appendPlainText("Broadcast Address:"+entry.broadcast().toString()+"\n");
        }
        ui->plainTextEdit->appendPlainText("\n");
    }
}

void Dialog::on_pushButton_2_clicked()
{
    QList<QHostAddress> addList=QNetworkInterface::allAddresses();
    if(!addList.isEmpty())
    {
        for(auto add:addList)
        {
            if(ui->checkBox->isChecked() && QAbstractSocket::IPv4Protocol!=add.protocol())
            {
                continue;
            }
            else
            {
                ui->plainTextEdit->appendPlainText("Protocol:"+protocolName(add.protocol()));
                ui->plainTextEdit->appendPlainText("Host IP Address:"+add.toString());
                ui->plainTextEdit->appendPlainText("");
            }
        }
    }
}
