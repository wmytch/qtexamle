#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextDocument>
#include <QTextBlock>
#include <QMenu>

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
    void on_btnInitItems_clicked();

    void on_btnClearItems_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
