#include "treemodel.h"
#include "treemodel_p.h"

QModelIndex TreeModelPrivate::index(TreeItem *item) const
{
    return q_func()->createIndex(item->row(), 0, item);
}

TreeItem * TreeModelPrivate::item(const QModelIndex &index) const
{
    if (!index.isValid())
        return rootItem;

    return static_cast<TreeItem*>(index.internalPointer());
}

TreeModel::TreeModel(QObject *parent) :
    QAbstractItemModel(parent),
    d_ptr(new TreeModelPrivate(this))
{
    Q_D(TreeModel);

    d->rootItem = new TreeItem();
}

TreeModel::~TreeModel()
{
    delete d_ptr->rootItem;
    delete d_ptr;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    if (role == Qt::DisplayRole || role == Qt::EditRole) {

    } else if (role == Qt::DecorationRole) {

    } else if (role == Qt::ToolTipRole) {

    }
    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool TreeModel::hasChildren(const QModelIndex &parent) const
{
    TreeItem::Type type = d_func()->item(parent)->type();
    return type == TreeItem::Folder || type == TreeItem::Root;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem = d_func()->item(parent);
    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    Q_D(const TreeModel);

    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == d->rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

bool TreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_D(TreeModel);

    if (row < 0 || count <= 0 || row + count > rowCount(parent))
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    TreeItem *parentItem = d->item(parent);
    for (int i = row + count - 1; i >= row; --i) {
        TreeItem *childItem = parentItem->child(i);
        delete childItem;
    }
    endRemoveRows();

    return true;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    return d_func()->item(parent)->childCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(TreeModel);

    if (!index.isValid() || (flags(index) & Qt::ItemIsEditable) == 0)
        return false;

    TreeItem *item = d->item(index);

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        break;
    default:
        break;
        return false;
    }

    emit dataChanged(index, index);
    return true;
}
