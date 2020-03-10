#include "mainwindow.h"

#include <QApplication>
#include "dialoglogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogLogin *dlgLogin=new DialogLogin;
    if(dlgLogin->exec()==QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    else
        return 0;
}
