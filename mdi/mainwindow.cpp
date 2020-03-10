#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formdoc.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->mdiArea);
    this->setWindowState(Qt::WindowMaximized);
   // this->setAttribute(Qt::WA_DeleteOnClose);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

MainWindow::~MainWindow()
{
    QMessageBox::information(this,"note","main window closed");
    delete ui;
}


void MainWindow::on_actNewDoc_triggered()
{
    FormDoc *formDoc=new FormDoc(this);
    ui->mdiArea->addSubWindow(formDoc);
    formDoc->show();
}



void MainWindow::on_actOpenDoc_triggered()
{
    bool needNew=false;
    FormDoc *formDoc;

    if(ui->mdiArea->subWindowList().count()>0)
    {
        formDoc=(FormDoc*)ui->mdiArea->activeSubWindow()->widget();
        if(formDoc)
            needNew=formDoc->isFileOpened();
        else
            return;
    }
    else
    {
        needNew=true;
    }

    QString curPath=QDir::currentPath();
    QString fileName=QFileDialog::getOpenFileName(this,"open file",
                                                  curPath,"C(*.h *cpp);;all file(*.*)");
    if(fileName.isEmpty())
        return;

    if(needNew)
    {
        formDoc=new FormDoc(this);
        ui->mdiArea->addSubWindow(formDoc);
    }

    formDoc->loadFromFile(fileName);
    formDoc->show();
    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);

}

void MainWindow::on_actCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_actCloseAll_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actMdi_triggered(bool checked)
{
    if(checked)
    {
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
        ui->mdiArea->setTabsClosable(true);
        ui->actCascade->setEnabled(false);
        ui->actTile->setEnabled(false);
    }
    else
    {
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
        ui->actCascade->setEnabled(true);
        ui->actTile->setEnabled(true);
    }
}

void MainWindow::on_actCut_triggered()
{
    FormDoc *formDoc=(FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formDoc->cutText();
}

void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    Q_UNUSED(arg1)
    if(ui->mdiArea->subWindowList().count()==0)
    {
        ui->actCut->setEnabled(false);
        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actFont->setEnabled(false);
        ui->statusbar->clearMessage();
    }
    else
    {
        FormDoc *formDoc=static_cast<FormDoc*>(ui->mdiArea->activeSubWindow()->widget());
        ui->statusbar->showMessage(formDoc->currentFileName());
    }
}

void MainWindow::on_actFont_triggered()
{
    FormDoc *formDoc=(FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formDoc->setEditFont();
}

void MainWindow::on_actQuit_triggered()
{
    if(ui->mdiArea->subWindowList().count()>0)
    {
        ui->mdiArea->closeAllSubWindows();
    }
    MainWindow::close();
}

