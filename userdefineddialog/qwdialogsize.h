#ifndef QWDIALOGSIZE_H
#define QWDIALOGSIZE_H

#include <QDialog>

namespace Ui {
class QWdialogSize;
}

class QWdialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit QWdialogSize(QWidget *parent = nullptr);
    ~QWdialogSize();

    int rowCount();
    int columnCount();
    void setRowColumn(int row,int column);

private:
    Ui::QWdialogSize *ui;
};

#endif // QWDIALOGSIZE_H
