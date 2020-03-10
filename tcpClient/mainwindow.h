#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QtNetwork>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTcpSocket *tcpClient;
    QLabel *labSocketState;
    QString getLocalIP();

private slots:
    void onConnected();
    void onDisconnected();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();
    void on_actConnect_triggered();

    void on_actClose_triggered();

    void on_pushButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
