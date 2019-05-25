#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>

struct Row
{
    QString name;
    QString login;
    QString password;

    bool operator==(const Row &other) const
    {
        return name == other.name && login == other.login && password == other.password;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Row &contact)
{
    return stream << contact.name << contact.login << contact.password;
}

inline QDataStream &operator>>(QDataStream &stream, Row &contact)
{
    return stream >> contact.name >> contact.login >> contact.password;
}

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
    TableModel(QList<Row> contacts, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<Row> getContacts() const;

private:
    QList<Row> contacts;
};

#endif // TABLEMODEL_H
