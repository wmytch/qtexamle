#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>

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


void Dialog::on_btnOpen_clicked()
{
    QString curPath=QDir::currentPath();
    QString dlgTitle="select a file";
    QString filter="text(*.txt);;image(*.jpg *.gif);;all file(*.*)";
    QString fileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(!fileName.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(fileName);
    }
}

void Dialog::on_btnOpenMulti_clicked()
{
    QString curPath=QDir::currentPath();
    QString dlgTitle="select multi files";
    QString filter="text(*.txt);;image(*.jpg *.gif);;all file(*.*)";
    QStringList fileList=QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
    for(int i=0;i<fileList.count();i++)
    {
        ui->plainTextEdit->appendPlainText(fileList[i]);
    }
}

void Dialog::on_btnSelDir_clicked()
{
    QString curPath=QCoreApplication::applicationDirPath();
    QString dlgTitle="select a directory";
    QString selectedDir=QFileDialog::getExistingDirectory(this,dlgTitle,curPath,QFileDialog::ShowDirsOnly);
    if(!selectedDir.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(selectedDir);
    }
}

void Dialog::on_btnSave_clicked()
{
    QString curPath=QCoreApplication::applicationDirPath();
    QString dlgTitle="save file";
    QString filter="header(*.h);;source(*.cpp);;all file(*.*)";
    QString fileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(!fileName.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(fileName);
    }
}

void Dialog::on_btnColor_clicked()
{
    QPalette pal=ui->plainTextEdit->palette();
    QColor initColor=pal.color(QPalette::Text);
    QColor color=QColorDialog::getColor(initColor,this,"select color");
    if(color.isValid())
    {
        pal.setColor(QPalette::Text,color);
        ui->plainTextEdit->setPalette(pal);
    }
}

void Dialog::on_btnFont_clicked()
{
    QFont initFont=ui->plainTextEdit->font();
    bool ok=false;
    QFont font=QFontDialog::getFont(&ok,initFont);
    if(ok)
        ui->plainTextEdit->setFont(font);
}

void Dialog::on_btnInputString_clicked()
{
    QString dlgTitle="input literal dialog";
    QString txtLabel="input file name";
    QString defaultInput="newfile.txt";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;
    bool ok=false;
    QString text=QInputDialog::getText(this,dlgTitle,txtLabel,echoMode,defaultInput,&ok);
    if(ok&&!text.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(text);
    }
}

void Dialog::on_btnInputInt_clicked()
{
    QString dlgTitle="input integer";
    QString txtLebel="Set font size";
    int defaultValue=ui->plainTextEdit->font().pointSize();
    int minValue=6,maxValue=50,stepValue=1;
    bool ok=false;
    int inputValue=QInputDialog::getInt(this,dlgTitle,txtLebel,defaultValue,minValue,maxValue,stepValue,&ok);
    if(ok)
    {
        QString fontSize=QString::asprintf("font size:%d",inputValue);
        ui->plainTextEdit->appendPlainText(fontSize);
        QFont font=ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);

    }
}

void Dialog::on_btnInputFloat_clicked()
{
    QString dlgTitle="Input float number";
    QString txtLabel="Input a float Number";
    float defaultValue=3.13;
    float minValue=0,maxValue=10000;
    int decimals=2;
    bool ok=false;
    float inputValue=QInputDialog::getDouble(this,dlgTitle,txtLabel,defaultValue,minValue,maxValue,decimals,&ok);
    if(ok)
    {
        QString str=QString::asprintf("input a float number:%.2f",inputValue);
        ui->plainTextEdit->appendPlainText(str);
    }
}

void Dialog::on_btnInputItem_clicked()
{
    QStringList items;
    items<<"Excellent"<<"Fine"<<"Available"<<"Not Available";
    QString dlgTitle="items select dialog";
    QString txtLabel="Select level";
    int curIndex=0;
    bool editable=true;
    bool ok=false;
    QString text=QInputDialog::getItem(this,dlgTitle,txtLabel,items,curIndex,editable,&ok);
    if(ok&&!text.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(text);
    }
}

void Dialog::on_btnMsgQuestion_clicked()
{
    QString title="Question message box";
    QString strInfo="File changed,Save it?";
    QMessageBox::StandardButton defaultBtn=QMessageBox::NoButton;
    QMessageBox::StandardButton result;
    result=QMessageBox::question(this,title,strInfo,QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                 defaultBtn);
    if(result==QMessageBox::Yes)
        ui->plainTextEdit->appendPlainText("question message box:Yes");
    else if(result==QMessageBox::No)
        ui->plainTextEdit->appendPlainText("question message box:No");
    else if(result==QMessageBox::Cancel)
        ui->plainTextEdit->appendPlainText("question message box:Cancel");
    else
        ui->plainTextEdit->appendPlainText("question message box:No Choice");
}

void Dialog::on_btnMsgInfo_clicked()
{
    QString title="information";
    QString strInfo="file opened,font setted";
    QMessageBox::information(this,title,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}

void Dialog::on_btnMsgWarning_clicked()
{
    QString title="Warning";
    QString strInfo="file opened,font setted";
    QMessageBox::warning(this,title,strInfo);
}

void Dialog::on_btnMsgCritical_clicked()
{
    QString title="Critical";
    QString strInfo="file opened,font setted";
    QMessageBox::critical(this,title,strInfo);
}

void Dialog::on_btnMsgAbout_clicked()
{
    QString title="About";
    QString strInfo="file opened,font setted";
    QMessageBox::about(this,title,strInfo);
}

void Dialog::on_btnMsgQtAbout_clicked()
{
    QString title="AboutQt";
    QMessageBox::aboutQt(this,title);
}
