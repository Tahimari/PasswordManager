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

class PasswordWidget : public QTabWidget
{
    Q_OBJECT

public:
    PasswordWidget(QWidget *parent = nullptr);
    void readFromFile(const QString &fileName, const QString password);
    void writeToFile(const QString &fileName, const QString password);

public slots:
    void showAddEntryDialog();
    QString showPasswordDialog();
    void showInfoDialog();
    void addEntry(QString name, QString login, QString password);
    void editEntry();
    void removeEntry();
    void hideEntry();

signals:
    void selectionChanged (const QItemSelection &selected);

private:
    void setupTab();

    TableModel *table;
    NewPasswordTab *newPasswordTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // PASSWORDWIDGET_H
