#ifndef QWINTSPINDELEGATE_H
#define QWINTSPINDELEGATE_H
#include <QStyledItemDelegate>

class QWintSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWintSpinDelegate();

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // QWINTSPINDELEGATE_H
