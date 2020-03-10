#include "qwintspindelegate.h"
#include <QSpinBox>
QWintSpinDelegate::QWintSpinDelegate()
{

}

QWidget * QWintSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor=new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(10000);
    return editor;
}

void QWintSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value=index.model()->data(index,Qt::EditRole).toInt();
    QSpinBox *spinBox=static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void QWintSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox=static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value=spinBox->value();
    model->setData(index,value,Qt::EditRole);
}

void QWintSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}