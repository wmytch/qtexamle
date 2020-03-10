#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpClient=new QTcpSocket(this);
    labSocketState=new QLabel("Socket status:");
    labSocketState->setMidLineWidth(250);
    ui->statusbar->addWidget(labSocketState);

    QString localIP=getLocalIP();
    this->setWindowTitle(this->windowTitle()+"----Local IP:"+localIP);
    ui->comboBox->addItem(localIP);

    connect(tcpClient,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(tcpClient,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actConnect_triggered()
{
    QString addr=ui->comboBox->currentText();
    quint16 port=ui->spinBox->value();
    tcpClient->connectToHost(addr,port);
}

void MainWindow::on_actClose_triggered()
{
    if(tcpClient->state()==QAbstractSocket::ConnectedState)
    {
        tcpClient->disconnectFromHost();
    }
}

void MainWindow::onConnected()
{
    ui->plainTextEdit->appendPlainText("**Connected to server");
    ui->plainTextEdit->appendPlainText("**Peer address:"+tcpClient->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**Peer Port:"+QString::number(tcpClient->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actClose->setEnabled(true);
}

void MainWindow::onDisconnected()
{
    ui->plainTextEdit->appendPlainText("**Disconnected from server");
    ui->actConnect->setEnabled(true);
    ui->actClose->setEnabled(false);
}

void MainWindow::onSocketReadyRead()
{
    while(tcpClient->canReadLine())
        ui->plainTextEdit->appendPlainText("[in]"+tcpClient->readLine());
}
void MainWindow::on_pushButton_clicked()
{
    QString msg=ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[out]"+msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();
    QByteArray str=msg.toUtf8();
    str.append('\n');
    tcpClient->write(str);
}

QString MainWindow::getLocalIP()
{
    QString hostName=QHostInfo::localHostName();
    QHostInfo hostInfo=QHostInfo::fromName(hostName);
    QString localIP{""};
    QList<QHostAddress> addList=hostInfo.addresses();
    if(!addList.isEmpty())
    {
        for(auto host:addList)
        {
            if(host.protocol()==QAbstractSocket::IPv4Protocol)
            {
                localIP=host.toString();
                break;
            }
        }
    }
    return localIP;
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        labSocketState->setText("Socket Status:UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        labSocketState->setText("Socket Status:HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        labSocketState->setText("Socket Status:ConnectingState");
        break;
    case QAbstractSocket::ConnectedState:
        labSocketState->setText("Socket Status:ConnectedState");
        break;
    case QAbstractSocket::BoundState:
        labSocketState->setText("Socket Status:BoundState");
        break;
    case QAbstractSocket::ClosingState:
        labSocketState->setText("Socket Status:ClosingState");
        break;
    case QAbstractSocket::ListeningState:
        labSocketState->setText("Socket Status:ListeningState");
        break;
    }
}