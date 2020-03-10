#include <QWidget>
#include <QComboBox>
#include "qwcomboboxdelegate.h"

QWComboBoxDelegate::QWComboBoxDelegate()
{

}

void QWComboBoxDelegate::setItems(QStringList items, bool isEdit)
{
    mItemList=items;
    mIsEdit=isEdit;
}

QWidget* QWComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *editor=new QComboBox(parent);
    for(auto item:mItemList)
    {
        editor->addItem(item);
    }
    editor->setEditable(mIsEdit);
    return editor;
}

void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *combo=static_cast<QComboBox*>(editor);
    combo->setCurrentText(index.model()->data(index,Qt::EditRole).toString());
}

void QWComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *combo=static_cast<QComboBox*>(editor);
    model->setData(index,combo->currentText(),Qt::EditRole);
}

void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}