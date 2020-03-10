#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include "qdicethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT
private:
    QDiceThread mThread;
protected:
    void closeEvent(QCloseEvent *);
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
private slots:
    void onThreadStarted();
    void onThreadFinished();
    void onNewValue(int seq,int diceValue);
    void on_btnStartThread_clicked();
    void on_btnStart_clicked();
    void on_btnPause_clicked();
    void on_btnEnd_clicked();
    void on_btnClear_clicked();
};
#endif // DIALOG_H
