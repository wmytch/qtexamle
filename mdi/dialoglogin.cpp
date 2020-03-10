#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include <QSettings>
#include <QCryptographicHash>
#include <QMessageBox>

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
    ui->editPassword->setEchoMode(QLineEdit::Password);
    //this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::SplashScreen);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    readSettings();
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_btnOk_clicked()
{
    QString user=ui->editUser->text().trimmed();
    QString password=ui->editPassword->text().trimmed();
    QString enPassword=encrypt(password);
    if(user==this->user && enPassword==this->password)
    {
        writeSettings();
        this->accept();
    }
    else
    {
        countTry++;
        if(countTry>3)
        {
            QMessageBox::critical(this,"Error","Too many tries,abort.");
            this->reject();
        }
        else
        {
            QMessageBox::warning(this,"Warnning","user or password not match");
        }
    }
}

void DialogLogin::readSettings()
{
    QString organization="WWB-QT";
    QString appName="splash-mdi";
    QSettings settings(organization,appName);
    bool saved=settings.value("saved",false).toBool();
    this->user=settings.value("Username","user").toString();
    QString defaultPassword=encrypt("12345");
    this->password=settings.value("Password",defaultPassword).toString();
    if(saved)
    {
        ui->editUser->setText(this->user);
    }
    ui->checkBoxSave->setChecked(saved);
}

void DialogLogin::writeSettings()
{
    QSettings settings("WWB-QT","splash-mdi");
    settings.setValue("Username",this->user);
    settings.setValue("Password",this->password);
    settings.setValue("saved",ui->checkBoxSave->isChecked());
}

QString DialogLogin::encrypt(const QString &str)
{
    QByteArray array;
    array.append(str);
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(array);
    QByteArray result=hash.result();
    QString md5=result.toHex();
    return md5;
}

void DialogLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->isMoving=true;
        this->lastPos=event->globalPos()-pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void DialogLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(this->isMoving && event->buttons() && Qt::LeftButton
            && (event->globalPos()-this->lastPos).manhattanLength()>QApplication::startDragDistance())
    {
        move(event->globalPos()-this->lastPos);
        this->lastPos=event->globalPos()-pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void DialogLogin::mouseReleaseEvent(QMouseEvent *event)
{
    this->isMoving=false;
}