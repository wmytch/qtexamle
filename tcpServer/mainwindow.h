#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QtNetwork/QtNetwork>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *labListen;
    QLabel *labSocketState;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QString getLocalIP();
protected:
//    void closeEvent(QCloseEvent *event);

private slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onClientConnected();
    void onClientDisconnected();
    void onSocketReadyRead();
    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_pushButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
