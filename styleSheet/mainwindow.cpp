#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp regExp(".(.*)\\+?Style");
    QString defaultStyle=QApplication::style()->metaObject()->className();
    ui->statusbar->showMessage(defaultStyle);
    if(regExp.exactMatch(defaultStyle))
        defaultStyle=regExp.cap(1);
    ui->comboBoxSysStyle->addItems(QStyleFactory::keys());
    ui->comboBoxSysStyle->setCurrentIndex(ui->comboBoxSysStyle->findText(defaultStyle,Qt::MatchContains));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBoxSysStyle_currentIndexChanged(const QString &arg1)
{
    qApp->setStyle(arg1);
    QStyle *style=QStyleFactory::create(arg1);
    qApp->setStyle(style);
    ui->statusbar->showMessage(style->metaObject()->className());
}

void MainWindow::on_btnNormal_clicked()
{
    this->setStyleSheet("");
}

void MainWindow::on_btnStyleSheet_clicked()
{
    this->setStyleSheet("QPlainTextEdit{color: blue;font: 13pt '黑体';}"
                        "QPushButton:hover{background-color:lime;}"
                        "QLineEdit{border:2px groove red;background-color:rgb(170,255,127);border-radius:6px;}"
                        "QCheckBox:checked{color:red;}"
                        "QRadioButton:checked{color:red}");
}
