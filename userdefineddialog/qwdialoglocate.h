#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class QWdialogLocate;
}

class QWdialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWdialogLocate(QWidget *parent = nullptr);
    ~QWdialogLocate();

    void setSpinRange(int rowCount,int colCount);

private slots:
    void on_btnSetText_clicked();

private:
    Ui::QWdialogLocate *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

public slots:
    void setSpinValue(int rowNo,int colNo);

signals:
    void changeCellText(int row,int column,QString &text);
    void changeActionEnable(bool enable);
};

#endif // QWDIALOGLOCATE_H
