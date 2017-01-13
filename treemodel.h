#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QtCore/QAbstractItemModel>

class TreeModelPrivate;
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TreeModel)
    Q_DISABLE_COPY(TreeModel)

public:
    explicit TreeModel(QObject *parent = 0);
    ~TreeModel();

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index = QModelIndex()) const;
    bool removeRows(int row, int count, const QModelIndex &parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

protected:
    TreeModelPrivate *d_ptr;
};

#endif // TREEMODEL_H
