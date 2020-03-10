#ifndef QWCOMBOBOXDELEGATE_H
#define QWCOMBOBOXDELEGATE_H
#include <QStyledItemDelegate>

class QWComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWComboBoxDelegate();
    void setItems(QStringList items,bool isEdit);
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QStringList mItemList;
    bool mIsEdit;
};

#endif // QWCOMBOBOXDELEGATE_H
