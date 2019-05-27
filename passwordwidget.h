#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include "newpasswordtab.h"
#include "tablemodel.h"

#include <QItemSelection>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

//! [0]
class PasswordWidget : public QTabWidget
{
    Q_OBJECT

public:
    PasswordWidget(QWidget *parent = nullptr);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void showInfoDialog();
    void addEntry(QString name, QString login, QString password);
    void editEntry();
    void removeEntry();

signals:
    void selectionChanged (const QItemSelection &selected);

private:
    void setupTabs();

    TableModel *table;
    NewPasswordTab *newPasswordTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // PASSWORDWIDGET_H
