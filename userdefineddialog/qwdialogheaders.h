#ifndef QWDIALOGHEADERS_H
#define QWDIALOGHEADERS_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class QWdialogHeaders;
}

class QWdialogHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit QWdialogHeaders(QWidget *parent = nullptr);
    ~QWdialogHeaders();

    void setHeaderList(QStringList &headers);
    QStringList headerList();

private:
    Ui::QWdialogHeaders *ui;
    QStringListModel *model;
};

#endif // QWDIALOGHEADERS_H
