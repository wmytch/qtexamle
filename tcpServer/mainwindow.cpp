#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labListen=new QLabel("Listen status:");
    labListen->setMidLineWidth(250);
    ui->statusbar->addWidget(labListen);

    labSocketState=new QLabel("Socket status:");
    labSocketState->setMidLineWidth(300);
    ui->statusbar->addWidget(labSocketState);

    QString localIP=getLocalIP();
    this->setWindowTitle(this->windowTitle()+"----Local IP:"+localIP);
    ui->comboBox->addItem(localIP);
    tcpServer=new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_actStart_triggered()
{
    QString IP=ui->comboBox->currentText();
    quint16 port=ui->spinBox->value();
    QHostAddress addr(IP);
    tcpServer->listen(addr,port);
    ui->plainTextEdit->appendPlainText("**Begin Listen...**");
    ui->plainTextEdit->appendPlainText("**Server Address:"+tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("**Server Port:"+QString::number(tcpServer->serverPort()));
    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);
    labListen->setText("Listen status:Listenning");
}

void MainWindow::onNewConnection()
{
    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(onClientConnected()));
    onClientConnected();
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(onClientDisconnected()));
    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
    onSocketStateChanged(tcpSocket->state());
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
}

void MainWindow::onClientConnected()
{
    ui->plainTextEdit->appendPlainText("**Client Socket connected");
    ui->plainTextEdit->appendPlainText("**Peer address:"+tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**Peer port:"+QString::number(tcpSocket->peerPort()));
}

void MainWindow::onClientDisconnected()
{
    ui->plainTextEdit->appendPlainText("**Client Socket disconnected");
    ui->plainTextEdit->appendPlainText("**Peer address:"+tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**Peer port:"+QString::number(tcpSocket->peerPort()));
    tcpSocket->deleteLater();
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
void MainWindow::on_actStop_triggered()
{
    if(tcpServer->isListening())
    {
        tcpServer->close();
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(false);
        labListen->setText("Listennng status:Stopped");
    }
}

void MainWindow::onSocketReadyRead()
{
    while(tcpSocket->canReadLine())
    {
        ui->plainTextEdit->appendPlainText("[in]"+tcpSocket->readLine());
    }
}
void MainWindow::on_pushButton_clicked()
{
    QString msg=ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[out]"+msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();
    QByteArray str=msg.toUtf8();
    str.append('\n');
    tcpSocket->write(str);
}
