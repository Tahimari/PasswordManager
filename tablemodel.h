#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QCryptographicHash>
#include "simplecrypt.h"
struct Pass
{
    QString name;
    QString login;
    QString password;
    QString hidePassword;

    bool operator==(const Pass &other) const
    {
        return name == other.name && login == other.login && password == other.password;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Pass &contact)
{
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    return stream
            << crypto.encryptToString(contact.name)
            << crypto.encryptToString(contact.login)
            << crypto.encryptToString(contact.password);
}

inline QDataStream &operator>>(QDataStream &stream, Pass &contact)
{
    return stream >> contact.name >> contact.login >> contact.password;
}

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
    TableModel(QList<Pass> passes, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool hidePassword(const QModelIndex &index, int role);
    QList<Pass> getPasses() const;

private:
    QList<Pass> passes;
};

#endif // TABLEMODEL_H
