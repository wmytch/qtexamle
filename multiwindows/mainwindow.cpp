#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "formdoc.h"
#include "formtable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);
    setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

//    QRect rect(0,ui->toolBar->height(),this->width(),
//            this->height()-ui->toolBar->height()-ui->statusbar->height());
//    QPen pen;
//    pen.setWidth(3);
//    pen.setColor(Qt::red);
//    pen.setStyle(Qt::SolidLine);
//    pen.setCapStyle(Qt::FlatCap);
//    pen.setJoinStyle(Qt::BevelJoin);
//    painter.setPen(pen);

//    QBrush brush;
//    brush.setColor(Qt::blue);
//    brush.setStyle(Qt::SolidPattern);
//    painter.setBrush(brush);

//    painter.drawRect(rect);
    painter.drawPixmap(0,ui->toolBar->height(),this->width(),
                       this->height()-ui->toolBar->height()-ui->statusbar->height(),
                       QPixmap(":back.jpg"));
}
void MainWindow::on_actEmbedWidget_triggered()
{
    FormDoc *formDoc=new FormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    int cur=ui->tabWidget->addTab(formDoc,QString::asprintf("Doc %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_actIndWidget_triggered()
{
    FormDoc *formDoc=new FormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowTitle("QWidget-based window,no parent window,delete on close");
    formDoc->setWindowFlag(Qt::Window,true);
    formDoc->setWindowOpacity(0.9);
    formDoc->show();
}

void MainWindow::on_actEmbedWindow_triggered()
{
    FormTable *formTable=new FormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    int cur=ui->tabWidget->addTab(formTable,
                                  QString::asprintf("Table %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);

}

void MainWindow::on_actIndWindow_triggered()
{
    FormTable *formTable=new FormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("MainWindow-based window");
    formTable->show();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index<0)
        return;
    QWidget *form=ui->tabWidget->widget(index);
    form->close();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index)
    bool en=ui->tabWidget->count()>0;
    ui->tabWidget->setVisible(en);
}
