#include "formdoc.h"
#include "ui_formdoc.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QFontDialog>
#include <QMessageBox>

FormDoc::FormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDoc)
{
    ui->setupUi(this);
    this->setWindowTitle("New Doc");
    //this->setAttribute(Qt::WA_DeleteOnClose);
}

FormDoc::~FormDoc()
{
    QMessageBox::information(this,"note","doc closed");
    delete ui;
}

void FormDoc::loadFromFile(QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(stream.readAll());
        file.close();
        currentFile=fileName;
        QFileInfo fileInfo(fileName);
        QString str=fileInfo.fileName();
        this->setWindowTitle(str);
        fileOpened=true;
    }
}

QString FormDoc::currentFileName()
{
    return currentFile;
}

bool FormDoc::isFileOpened()
{
    return fileOpened;
}

void FormDoc::setEditFont()
{
    QFont font=ui->plainTextEdit->font();
    bool ok;
    font=QFontDialog::getFont(&ok,font);
    ui->plainTextEdit->setFont(font);
}

void FormDoc::cutText()
{
    ui->plainTextEdit->cut();
}

void FormDoc::copyText()
{
    ui->plainTextEdit->copy();
}

void FormDoc::pasteText()
{
    ui->plainTextEdit->paste();
}