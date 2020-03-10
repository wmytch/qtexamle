#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_btnListInsert_clicked();

    void on_btnDelCurItem_clicked();

    void on_btnClearList_clicked();

    void on_btnListAppend_clicked();

    void on_btnTextImport_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QStringListModel *model;
};
#endif // WIDGET_H
