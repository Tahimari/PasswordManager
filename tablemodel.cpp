#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::TableModel(QList<Pass> passes, QObject *parent)
    : QAbstractTableModel(parent)
    , passes(passes)
{
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return passes.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= passes.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &pass = passes.at(index.row());

        if (index.column() == 0)
            return pass.name;
        else if (index.column() == 1)
            return pass.login;
        else if (index.column() == 2)
            return pass.password;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Nazwa");

            case 1:
                return tr("Login");

            case 2:
                return tr("Hasło");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        passes.insert(position, { QString(), QString(), QString() });

    endInsertRows();
    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        passes.removeAt(position);

    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto pass = passes.value(row);

        if (index.column() == 0)
            pass.name = value.toString();
        else if (index.column() == 1)
            pass.login = value.toString();
        else if (index.column() == 2)
            pass.password = value.toString();
        else
            return false;

        passes.replace(row, pass);
        emit dataChanged(index, index, {role});

        return true;
    }

    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<Pass> TableModel::getPasses() const
{
    return passes;
}
