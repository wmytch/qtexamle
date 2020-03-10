#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    createSelectionPopMenu();
//    connect(ui->listWidget,SIGNAL(customContextMenuRequested(const QPoint)),this,SLOT(on_listWidget_customContextMenuRequested(const QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actListInit_triggered()
{
    QListWidgetItem *aItem;
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk=ui->chkListEditable->isChecked();
    ui->listWidget->clear();
    for(int i=0;i<10;i++)
    {
        QString str=QString::asprintf("Item %d",i);
        aItem=new QListWidgetItem();
        aItem->setText(str);
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);
        if(chk)
        {
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
        else
        {
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
        ui->listWidget->addItem(aItem);
    }
}

void MainWindow::on_actListInsert_triggered()
{
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk=ui->chkListEditable->isChecked();

    QListWidgetItem* aItem=new QListWidgetItem("New Inserted Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if(chk)
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    else
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem);
}

void MainWindow::on_actListDel_triggered()
{
    int row=ui->listWidget->currentRow();
    delete ui->listWidget->takeItem(row);
}

void MainWindow::on_actSelAll_triggered()
{
    int cnt=ui->listWidget->count();
    for(int i=0;i<cnt;i++)
    {
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_actSelNone_triggered()
{
    int cnt=ui->listWidget->count();
    for(int i=0;i<cnt;i++)
    {
        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_actSelInvs_triggered()
{
    int cnt=ui->listWidget->count();
    for(int i=0;i<cnt;i++)
    {
        if(ui->listWidget->item(i)->checkState()==Qt::Unchecked)
        {
            ui->listWidget->item(i)->setCheckState(Qt::Checked);
        }
        else
        {
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
        }
    }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if(current!=NULL)
    {
        if(previous==NULL)
        {
            str="当前项："+current->text();
        }
        else
        {
            str="前一项："+previous->text()+"；当前项："+current->text();
        }
        ui->editCurrentItem->setText(str);
    }
}


void MainWindow::on_actListAppend_triggered()
{
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk=ui->chkListEditable->isChecked();

    QListWidgetItem* aItem=new QListWidgetItem("New Appended Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if(chk)
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    else
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    ui->listWidget->addItem(aItem);
}

void MainWindow::createSelectionPopMenu()
{
    QMenu* menuSelection=new QMenu(this);
    menuSelection->addAction(ui->actSelAll);
    menuSelection->addAction(ui->actSelNone);
    menuSelection->addAction(ui->actSelInvs);

    ui->tBtnSelItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtnSelItem->setDefaultAction(ui->actSelPopMenu);
    ui->tBtnSelItem->setMenu(menuSelection);

    QToolButton *aBtn=new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->actSelPopMenu);
    aBtn->setMenu(menuSelection);
    ui->toolBar->addWidget(aBtn);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actQuit);
    ui->toolBar->addSeparator();
}
void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu* menuList=new QMenu(this);

    menuList->addAction(ui->actListInit);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDel);
    menuList->addSeparator();
    menuList->addAction(ui->actSelAll);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);

    menuList->exec(QCursor::pos());
    delete menuList;
}


