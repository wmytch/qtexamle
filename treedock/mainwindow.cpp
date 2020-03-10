#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->labFileName=new QLabel("");
    ui->statusbar->addWidget(this->labFileName);
    this->setCentralWidget(ui->scrollArea);
    initTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTree()
{
    QString dataStr="";
    ui->treeWidget->clear();
//    QIcon icon;
//    icon.addFile(":/images/icons/15.ico");

    QTreeWidgetItem* item=new QTreeWidgetItem(MainWindow::itTopItem);
//    item->setIcon(MainWindow::colItem,icon);
    item->setText(MainWindow::colItem,"图片文件");
    item->setText(MainWindow::colItemType,"type=itTopItem");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(MainWindow::colItem,Qt::UserRole,QVariant(dataStr));

    ui->treeWidget->addTopLevelItem(item);

}
void MainWindow::on_actAddFolder_triggered()
{
    QString dir=QFileDialog::getExistingDirectory();
    if(!dir.isEmpty())
    {
        QTreeWidgetItem *parItem=ui->treeWidget->currentItem();
        if(parItem)
        {
            addFolderItem(parItem,dir);
        }
    }
}

void MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)
{
//    QIcon icon(":/images/icons/open3.bmp");
    QString nodeText=getFinalFolderName(dirName);

    QTreeWidgetItem *item=new QTreeWidgetItem(MainWindow::itGroupItem);
//    item->setIcon(colItem,icon);
    item->setText(colItem,nodeText);
    item->setText(colItemType,"type=itGroupItem");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(colItem,Qt::UserRole,QVariant(dirName));
    parItem->addChild(item);
}

QString MainWindow::getFinalFolderName(const QString &fullPathName)
{
    int cnt=fullPathName.length();
    int i=fullPathName.lastIndexOf("/");
    QString str=fullPathName.right(cnt-i-1);
    return str;
}
void MainWindow::on_actAddFiles_triggered()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"","","Images(*.jpg)");
    if(files.isEmpty())
        return;
    QTreeWidgetItem *parItem,*item;
    item=ui->treeWidget->currentItem();
    if(item->type()==itImageItem)
    {
        parItem=item->parent();
    }
    else
    {
        parItem=item;
    }
    if(!parItem)
        return;
    for(int i=0;i<files.size();i++)
    {
        QString aFilename=files.at(i);
        addImageItem(parItem,aFilename);
    }
}

void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFilename)
{
    QIcon icon(":/images/icons/31.ico");
    QString nodeText=getFinalFolderName(aFilename);
    QTreeWidgetItem *item=new QTreeWidgetItem(MainWindow::itImageItem);
    item->setIcon(colItem,icon);
    item->setText(colItem,nodeText);
    item->setText(colItemType,"type=itImageItem");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(colItem,Qt::UserRole,QVariant(aFilename));
    parItem->addChild(item);
}
void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(current==NULL)
        return;
    int var=current->type();
    switch (var)
    {
        case itTopItem:
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDelItem->setEnabled(false);
            break;
        case itGroupItem:
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDelItem->setEnabled(true);
            break;
        case itImageItem:
            ui->actAddFolder->setEnabled(false);
            ui->actAddFiles->setEnabled(true);
            ui->actDelItem->setEnabled(true);
            displayImage(current);
            break;
    }
}


void MainWindow::on_actDelItem_triggered()
{
    QTreeWidgetItem *item=ui->treeWidget->currentItem();
    QTreeWidgetItem *parItem=item->parent();
    parItem->removeChild(item);
    delete item;
}

void MainWindow::on_actScanItems_triggered()
{
    for(int i=0;i<ui->treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=ui->treeWidget->topLevelItem(i);
        changeItemCaption(item);
    }
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str="*"+item->text(colItem);
    item->setText(colItem,str);
    if(item->childCount()>0)
    {
        for (int i=0;i<item->childCount();i++)
        {
            changeItemCaption(item->child(i));
        }
    }
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    QString filename=item->data(colItem,Qt::UserRole).toString();
    labFileName->setText(filename);
    curPixMap.load(filename);
    on_actZoomFitHeight_triggered();

}

void MainWindow::on_actZoomFitHeight_triggered()
{
    int height=ui->scrollArea->height();
    int realHeight=curPixMap.height();
    pixRatio=float(height)/realHeight;
    QPixmap pix=curPixMap.scaledToHeight(height-30);
    ui->labPicture->setPixmap(pix);
}


void MainWindow::on_actZoomIn_triggered()
{
    pixRatio*=1.2;
    int width=pixRatio*curPixMap.width();
    int height=pixRatio*curPixMap.height();
    QPixmap pix=curPixMap.scaled(width,height);
    ui->labPicture->setPixmap(pix);
}

void MainWindow::on_actZoomOut_triggered()
{
    pixRatio/=1.2;
    int width=pixRatio*curPixMap.width();
    int height=pixRatio*curPixMap.height();
    QPixmap pix=curPixMap.scaled(width,height);
    ui->labPicture->setPixmap(pix);
}

void MainWindow::on_actZoomRealSize_triggered()
{
    pixRatio=1;
    ui->labPicture->setPixmap(curPixMap);
}

void MainWindow::on_actDockVisible_triggered(bool arg1)
{
    ui->dockWidget_2->setVisible(arg1);
}

void MainWindow::on_actDockFloat_triggered(bool checked)
{
    ui->dockWidget_2->setFloating(checked);
}

void MainWindow::on_dockWidget_2_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}

void MainWindow::on_dockWidget_2_topLevelChanged(bool topLevel)
{
    ui->actDockFloat->setChecked(topLevel);
}
