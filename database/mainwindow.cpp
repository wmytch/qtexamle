#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
    ui->actOpenDB->setEnabled(true);
    ui->actOpenQuery->setEnabled(false);
    ui->actOpenTable->setEnabled(false);
    ui->actRelation->setEnabled(false);
    ui->actAppend->setEnabled(false);
    ui->actInsert->setEnabled(false);
    ui->actDelete->setEnabled(false);
    ui->actSalary->setEnabled(false);
    ui->actSetPhoto->setEnabled(false);
    ui->actClearPhoto->setEnabled(false);
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
    ui->groupBoxSort->setVisible(false);
    ui->groupBoxFilter->setVisible(false);
    ui->groupBoxSort->setEnabled(false);
    ui->groupBoxFilter->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpenDB_triggered()
{
    QString file=QFileDialog::getOpenFileName(this,"Select a database file","","SQLite (*.db *.db3)");
    if(file.isEmpty())
        return;
    DB=QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(file);
    if(!DB.open())
    {
        QMessageBox::warning(this,"Error","Open database failed",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    ui->actOpenDB->setEnabled(false);
    ui->actOpenQuery->setEnabled(true);
    ui->actOpenTable->setEnabled(true);
    ui->actRelation->setEnabled(true);

}

void MainWindow::setHead(QSqlQueryModel *theModel)
{
    theModel->setHeaderData(0,Qt::Horizontal,"工号");
    theModel->setHeaderData(1,Qt::Horizontal,"姓名");
    theModel->setHeaderData(2,Qt::Horizontal,"性别");
    theModel->setHeaderData(3,Qt::Horizontal,"身高");
    theModel->setHeaderData(4,Qt::Horizontal,"出生日期");
    theModel->setHeaderData(5,Qt::Horizontal,"手机");
    theModel->setHeaderData(6,Qt::Horizontal,"省份");
    theModel->setHeaderData(7,Qt::Horizontal,"城市");
    theModel->setHeaderData(8,Qt::Horizontal,"部门");
    theModel->setHeaderData(9,Qt::Horizontal,"学历");
    theModel->setHeaderData(10,Qt::Horizontal,"工资");

}

void MainWindow::on_actOpenTable_triggered()
{
    openTable();
}

void MainWindow::on_actOpenQuery_triggered()
{
    openQuery();
}

void MainWindow::on_actRelation_triggered()
{
    openRelation();
}

void MainWindow::openRelation()
{
    curMode=relation;

    relationModel=new QSqlRelationalTableModel(this,DB);
    relationModel->setTable("studInfo");
    relationModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    relationModel->setSort(0,Qt::AscendingOrder);
    relationModel->setHeaderData(0,Qt::Horizontal,"学号");
    relationModel->setHeaderData(1,Qt::Horizontal,"姓名");
    relationModel->setHeaderData(2,Qt::Horizontal,"性别");
    relationModel->setHeaderData(3,Qt::Horizontal,"学院");
    relationModel->setHeaderData(4,Qt::Horizontal,"专业");

    relationModel->setRelation(3,QSqlRelation("departments","departID","departments"));
    relationModel->setRelation(4,QSqlRelation("majors","majorID","major"));

    relationSelection=new QItemSelectionModel(relationModel);
    connect(relationSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(relationModel);
    ui->tableView->setSelectionModel(relationSelection);

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    relationModel->select();

    ui->actOpenDB->setEnabled(false);
    ui->actOpenQuery->setEnabled(true);
    ui->actOpenTable->setEnabled(true);
    ui->actRelation->setEnabled(false);
    ui->actAppend->setEnabled(true);
    ui->actInsert->setEnabled(true);
    ui->actDelete->setEnabled(true);
    ui->actSalary->setEnabled(true);
    ui->actSetPhoto->setEnabled(true);
    ui->actClearPhoto->setEnabled(true);
    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
    ui->groupBoxSort->setVisible(false);
    ui->groupBoxFilter->setVisible(false);

}
void MainWindow::openQuery()
{
    queryModel=new QSqlQueryModel(this);
    queryModel->setQuery("select EmpNo,Name,Gender,Height,Birthday,Mobile,Province,City,Department,Education,Salary from employee order by Empno");
    if(queryModel->lastError().isValid())
    {
        QMessageBox::critical(this,"Error","Query table error.Error message:"+queryModel->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    curMode=query;
    setHead(queryModel);
    QSqlQuery fieldInfo;
    fieldInfo.exec("select * from employee where EmpNo=-1");
    mRecord=fieldInfo.record();

    querySelection=new QItemSelectionModel(queryModel);
    ui->tableView->setModel(queryModel);
    ui->tableView->setSelectionModel(querySelection);
    ui->actOpenDB->setEnabled(false);
    ui->actOpenQuery->setEnabled(false);
    ui->actOpenTable->setEnabled(true);
    ui->actRelation->setEnabled(true);
    ui->actAppend->setEnabled(true);
    ui->actInsert->setEnabled(true);
    ui->actDelete->setEnabled(true);
    ui->actSalary->setEnabled(true);
    ui->actSetPhoto->setEnabled(true);
    ui->actClearPhoto->setEnabled(true);
    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
    ui->groupBoxSort->setVisible(false);
    ui->groupBoxFilter->setVisible(false);

}

void MainWindow::openTable()
{
    tabModel=new QSqlTableModel(this,DB);
    tabModel->setTable("employee");
    tabModel->setSort(tabModel->fieldIndex("EmpNo"),Qt::AscendingOrder);
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!tabModel->select())
    {
        QMessageBox::critical(this,"Error","Open table error.Error message:"+tabModel->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    curMode=table;
    setHead(tabModel);

    theSelection=new QItemSelectionModel(tabModel);
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    connect(theSelection,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

    ui->tableView->setModel(tabModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("Memo"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("Photo"),true);

    QStringList strList;
    strList<<"男"<<"女";
    bool isEditable=false;
    delegateSex.setItems(strList,isEditable);
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("Gender"),&delegateSex);

    strList.clear();
    strList<<"销售部"<<"技术部"<<"生产部"<<"行政部";
    isEditable=true;
    delegateDepart.setItems(strList,isEditable);
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("Department"),&delegateDepart);

    dataMapper=new QDataWidgetMapper;
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbSpinEmpNo,tabModel->fieldIndex("EmpNo"));
    dataMapper->addMapping(ui->dbEditName,tabModel->fieldIndex("Name"));
    dataMapper->addMapping(ui->dbComboSex,tabModel->fieldIndex("Gender"));
    dataMapper->addMapping(ui->dbSpinHeight,tabModel->fieldIndex("Height"));
    dataMapper->addMapping(ui->dbEditBirth,tabModel->fieldIndex("Birthday"));
    dataMapper->addMapping(ui->dbEditMobile,tabModel->fieldIndex("Mobile"));
    dataMapper->addMapping(ui->dbComboProvince,tabModel->fieldIndex("Province"));
    dataMapper->addMapping(ui->dbEditCity,tabModel->fieldIndex("City"));
    dataMapper->addMapping(ui->dbComboDep,tabModel->fieldIndex("Department"));
    dataMapper->addMapping(ui->dbComboEdu,tabModel->fieldIndex("Education"));
    dataMapper->addMapping(ui->dbSpinSalary,tabModel->fieldIndex("Salary"));
    dataMapper->addMapping(ui->dbEditMemo,tabModel->fieldIndex("Memo"));
    dataMapper->addMapping(ui->dbLabPhoto,tabModel->fieldIndex("Photo"));

    dataMapper->toFirst();

    getFieldNames();
    ui->actOpenDB->setEnabled(false);
    ui->actOpenTable->setEnabled(false);
    ui->actOpenQuery->setEnabled(true);
    ui->actRelation->setEnabled(true);
    ui->actAppend->setEnabled(true);
    ui->actInsert->setEnabled(true);
    ui->actDelete->setEnabled(true);
    ui->actSalary->setEnabled(true);
    ui->actSetPhoto->setEnabled(true);
    ui->actClearPhoto->setEnabled(true);
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
    ui->groupBoxSort->setVisible(true);
    ui->groupBoxFilter->setVisible(true);
    ui->groupBoxSort->setEnabled(true);
    ui->groupBoxFilter->setEnabled(true);

}

void MainWindow::on_currentChanged(const QModelIndex &current,const QModelIndex &previous)
{
    Q_UNUSED(current)
    Q_UNUSED(previous)
    if(curMode==relation)
    {
        ui->actSubmit->setEnabled(relationModel->isDirty());
        ui->actRevert->setEnabled(relationModel->isDirty());
    }
    else
    {
        ui->actSubmit->setEnabled(tabModel->isDirty());
        ui->actRevert->setEnabled(tabModel->isDirty());
    }

}

void MainWindow::on_currentRowChanged(const QModelIndex &current,const QModelIndex &previous)
{
    Q_UNUSED(previous)
    ui->actDelete->setEnabled(current.isValid());
    ui->actSetPhoto->setEnabled(current.isValid());
    ui->actClearPhoto->setEnabled(current.isValid());

    if(!current.isValid())
    {
        ui->dbLabPhoto->clear();
        return;
    }

    dataMapper->setCurrentIndex(current.row());
    int curRecNo=current.row();
    QSqlRecord curRec=tabModel->record(curRecNo);
    if(curRec.isNull("Photo"))
    {
        ui->dbLabPhoto->clear();
    }
    else
    {
        QByteArray data=curRec.value("Photo").toByteArray();
        QPixmap pic;
        pic.loadFromData(data);
        ui->dbLabPhoto->setPixmap(pic.scaledToWidth(ui->dbLabPhoto->size().width()));
    }
}

void MainWindow::getFieldNames()
{
    QSqlRecord emptyRec=tabModel->record();
    for(int i=0;i<emptyRec.count();i++)
    {
        ui->comboFields->addItem(emptyRec.fieldName(i));
    }
}

void MainWindow::on_actAppend_triggered()
{
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    int curRow=curIndex.row();
    tabModel->setData(tabModel->index(curRow,0),2000+tabModel->rowCount());
    tabModel->setData(tabModel->index(curRow,2),"男");
    ui->actSubmit->setEnabled(true);

}

void MainWindow::on_actInsert_triggered()
{
    ui->actSubmit->setEnabled(true);

    switch (curMode)
    {
    case table:
    {
        QModelIndex curIndex=ui->tableView->currentIndex();
        tabModel->insertRow(curIndex.row(),QModelIndex());
        theSelection->clearSelection();
        theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
        break;
    case query:
    {
        queryMode=INSERT;
        QSqlQuery insert;
        mRecord.clearValues();
        mRecord.setValue("EmpNo",queryModel->rowCount()+3000);
        setInsertRecord();
    }
        break;
    }

}

void MainWindow::on_actDelete_triggered()
{
    if(curMode==query)
        return;
    QModelIndex curIndex=theSelection->currentIndex();
    tabModel->removeRow(curIndex.row());
}

void MainWindow::on_actSubmit_triggered()
{
    switch(curMode)
    {
    case table:
    {
        bool res=tabModel->submitAll();
        if(!res)
        {
            QMessageBox::information(this,"Note","Submit Failure:\n"+tabModel->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        }
        else
        {
            ui->actSubmit->setEnabled(false);
            ui->actRevert->setEnabled(false);
        }
    }
        break;
    case query:
    {
        getRecordData();
        QSqlQuery update;
        QString strMode;
        switch(queryMode)
        {
        case UPDATE:
        {
            strMode="Update:"+mRecord.value("Name").toString();
            update.prepare("update employee set Name=:Name,Gender=:Gengder,"
                           "Height=:Height,Birthday=:Birthday,Mobile=:Mobile,"
                           "Province=:Province,City=:City,Department=:Department,Education=:Education,"
                           "Salary=:Salary,Memo=:Memo,Photo=:Photo where EmpNo=:ID");
            update.bindValue(":ID",mRecord.value("EmpNo"));
        }
            break;
        case INSERT:
        {
            strMode="Insert:"+mRecord.value("Name").toString();
            update.prepare("insert into employee (EmpNo,Name,Gender,Height,Birthday,"
                           "Mobile,Province,City,Department,Education,Salary,Memo,Photo)"
                           " values(:EmpNo,:Name,:Gender,:Height,:Birthday,"
                           ":Mobile,:Province,:City,:Department,:Education,:Salary,:Memo,:Photo)");
            update.bindValue(":EmpNo",mRecord.value("EmpNo"));
        }
            break;
        }
        update.bindValue(":Name",mRecord.value("Name"));
        update.bindValue(":Gender",mRecord.value("Gender"));
        update.bindValue(":Height",mRecord.value("Height"));
        update.bindValue(":Birthday",mRecord.value("Birthday"));
        update.bindValue(":Mobile",mRecord.value("Mobile"));
        update.bindValue(":Province",mRecord.value("Province"));
        update.bindValue(":City",mRecord.value("City"));
        update.bindValue(":Department",mRecord.value("Department"));
        update.bindValue(":Education",mRecord.value("Education"));
        update.bindValue(":Salary",mRecord.value("Salary"));
        update.bindValue(":Memo",mRecord.value("Memo"));
        update.bindValue(":Photo",mRecord.value("Photo"));
        if(!update.exec())
        {
            QMessageBox::critical(this,"Error","Submit error:"+update.lastError().text());
        }
        else
        {
//            QMessageBox::information(this,"Note",strMode);
            ui->actSubmit->setEnabled(false);
            queryModel->setQuery("select EmpNo,Name,Gender,Height,Birthday,Mobile,Province,City,Department,Education,Salary from employee order by Empno");

//            queryModel->query().exec();
        }
    }
        break;
    }

}

void MainWindow::on_actRevert_triggered()
{
    tabModel->revertAll();
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}

void MainWindow::on_actSetPhoto_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,"Select a pic","","Photo(*.jpg)");
    if(fileName.isEmpty())
        return;
    QByteArray data;
    QFile *file=new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    data=file->readAll();
    file->close();
    switch(curMode)
    {
    case table:
        {
        int curRecNo=theSelection->currentIndex().row();
        QSqlRecord curRec=tabModel->record(curRecNo);
        curRec.setValue("Photo",data);
        tabModel->setRecord(curRecNo,curRec);
        }
        break;
    case query:
        mRecord.setValue("Photo",data);
        ui->actSubmit->setEnabled(true);

        break;
    }

    QPixmap pic;
    pic.load(fileName);
    ui->dbLabPhoto->setPixmap(pic.scaledToWidth(ui->dbLabPhoto->width()));
}

void MainWindow::on_actClearPhoto_triggered()
{

    switch(curMode)
    {
    case table:
        {
        int curRecNo=theSelection->currentIndex().row();
        QSqlRecord curRec=tabModel->record(curRecNo);
        curRec.setNull("Photo");
        tabModel->setRecord(curRecNo,curRec);
        }
        break;
    case query:
        mRecord.setNull("Photo");
        ui->actSubmit->setEnabled(true);

        break;
    }
    ui->dbLabPhoto->clear();

}

void MainWindow::on_actSalary_triggered()
{
    if(tabModel->rowCount()==0)
        return;
    for(int i=0;i<tabModel->rowCount();i++)
    {
        QSqlRecord rec=tabModel->record(i);
        float salary=rec.value("Salary").toFloat();
        salary*=1.1;
        rec.setValue("Salary",salary);
        tabModel->setRecord(i,rec);
    }
    if(tabModel->submitAll())
    {
        QMessageBox::information(this,"Note","Salary Changed",QMessageBox::Ok,QMessageBox::NoButton);
    }
}

void MainWindow::on_comboFields_currentIndexChanged(int index)
{
    if(ui->rbAsc->isChecked())
    {
        tabModel->setSort(index,Qt::AscendingOrder);
    }
    else
    {
        tabModel->setSort(index,Qt::DescendingOrder);
    }
    tabModel->select();
}



void MainWindow::on_rbAsc_clicked()
{
    tabModel->setSort(ui->comboFields->currentIndex(),Qt::AscendingOrder);
    tabModel->select();
}

void MainWindow::on_rbDesc_clicked()
{
    tabModel->setSort(ui->comboFields->currentIndex(),Qt::DescendingOrder);
    tabModel->select();
}

void MainWindow::on_rbMan_clicked()
{
    tabModel->setFilter(" Gender='男' ");
}

void MainWindow::on_rbWoman_clicked()
{
    tabModel->setFilter(" Gender='女' ");
}

void MainWindow::on_rbBoth_clicked()
{
    tabModel->setFilter("");
}



void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if(curMode!=query)
        return;
    on_tableView_doubleClicked(index);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(curMode!=query)
        return;
    queryMode=UPDATE;
    QSqlRecord curRec=queryModel->record(index.row());
    int empNo=curRec.value("EmpNo").toInt();
    QSqlQuery query;
    query.prepare("select * from employee where EmpNo=:ID");
    query.bindValue(":ID",empNo);
    query.exec();
    query.first();
    if(!query.isValid())
    {
        return;
        QMessageBox::information(this,"Query",query.lastError().text());
    }
    mRecord=query.record();
    ui->actSubmit->setEnabled(true);

    setUpdateRecord();
}

void MainWindow::setUpdateRecord()
{
    ui->dbSpinEmpNo->setEnabled(false);
    ui->dbSpinEmpNo->setValue(mRecord.value("EmpNo").toInt());
//    QMessageBox::information(this,"EmpNo",ui->dbSpinEmpNo->text());
    ui->dbEditName->setText(mRecord.value("Name").toString());
    ui->dbComboSex->setCurrentText(mRecord.value("Gender").toString());
    ui->dbSpinHeight->setValue(mRecord.value("Height").toFloat());
    ui->dbEditBirth->setDate(mRecord.value("Birthday").toDate());
    ui->dbEditMobile->setText(mRecord.value("Mobile").toString());
    ui->dbComboProvince->setCurrentText(mRecord.value("Province").toString());
    ui->dbEditCity->setText(mRecord.value("City").toString());
    ui->dbComboDep->setCurrentText(mRecord.value("Department").toString());
    ui->dbComboEdu->setCurrentText(mRecord.value("Education").toString());
    ui->dbSpinSalary->setValue(mRecord.value("Salary").toInt());
    ui->dbEditMemo->setPlainText(mRecord.value("Memo").toString());
    QVariant va=mRecord.value("Photo");
    if(!va.isValid())
    {
        ui->dbLabPhoto->clear();
    }
    else
    {
        QByteArray data=va.toByteArray();
        QPixmap pic;
        pic.loadFromData(data);
        ui->dbLabPhoto->setPixmap(pic.scaledToWidth(ui->dbLabPhoto->size().width()));
    }
}

void MainWindow::setInsertRecord()
{
    ui->dbSpinEmpNo->setEnabled(true);
    ui->dbSpinEmpNo->clear();
    ui->dbSpinEmpNo->setValue(mRecord.value("EmpNo").toInt());
//    QMessageBox::information(this,"EmpNo",ui->dbSpinEmpNo->text());
    ui->dbEditName->clear();
    ui->dbComboSex->clear();
    ui->dbSpinHeight->clear();
    ui->dbEditBirth->clear();
    ui->dbEditMobile->clear();
    ui->dbComboProvince->clear();
    ui->dbEditCity->clear();
    ui->dbComboDep->clear();
    ui->dbComboEdu->clear();
    ui->dbSpinSalary->setValue(0);
    ui->dbEditMemo->clear();
    ui->dbLabPhoto->clear();
}

void MainWindow::getRecordData()
{
    mRecord.setValue("EmpNo",ui->dbSpinEmpNo->value());
    mRecord.setValue("Name",QVariant(ui->dbEditName->text()));
    mRecord.setValue("Gender",ui->dbComboSex->currentText());
    mRecord.setValue("Height",ui->dbSpinHeight->value());
    mRecord.setValue("Birthday",ui->dbEditBirth->date());
    mRecord.setValue("Mobile",ui->dbEditMobile->text());
    mRecord.setValue("Province",ui->dbComboProvince->currentText());
    mRecord.setValue("City",ui->dbEditCity->text());
    mRecord.setValue("Department",ui->dbComboDep->currentText());
    mRecord.setValue("Education",ui->dbComboEdu->currentText());
    mRecord.setValue("Salary",ui->dbSpinSalary->value());
    mRecord.setValue("Memo",ui->dbEditMemo->toPlainText());
//    QMessageBox::information(this,"ui","ui:"+ui->dbEditName->text());
//    QMessageBox::information(this,"mRecord","mRecord:"+mRecord.value("Name").toString());

}

