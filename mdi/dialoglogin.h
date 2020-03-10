#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT
private:
    bool isMoving=false;
    QPoint lastPos;
    QString user="user";
    QString password="12345";
    int countTry=0;
    void readSettings();
    void writeSettings();
    QString encrypt(const QString& str);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

private slots:
    void on_btnOk_clicked();

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
