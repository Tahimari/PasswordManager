#include "adddialog.h"
#include "aboutdialog.h"
#include "passwordwidget.h"

#include <QtWidgets>

PasswordWidget::PasswordWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel(this);
    newPasswordTab = new NewPasswordTab(this);
    connect(newPasswordTab, &NewPasswordTab::sendDetails,
        this, &PasswordWidget::addEntry);

    addTab(newPasswordTab, "Password manager");

    setupTabs();
}

void PasswordWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString login = aDialog.loginText->text();
        QString password = aDialog.passwordText->text();

        addEntry(name, login, password);
    }
}

void PasswordWidget::showInfoDialog()
{
    AboutDialog aDialog;
    aDialog.exec();
}

void PasswordWidget::addEntry(QString name, QString login, QString password)
{
    if (!table->getPasses().contains({ name, login, password })) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, password, Qt::EditRole);
        removeTab(indexOf(newPasswordTab));
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(name));
    }
}

void PasswordWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString address;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex addressIndex = table->index(row, 1, QModelIndex());
        QVariant varAddr = table->data(addressIndex, Qt::DisplayRole);
        address = varAddr.toString();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Contact"));

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.loginText->setText("test");
    aDialog.passwordText->setText(address);

    if (aDialog.exec()) {
        QString newAddress = aDialog.loginText->text();
        if (newAddress != address) {
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newAddress, Qt::EditRole);
        }
    }
}

void PasswordWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }

    if (table->rowCount(QModelIndex()) == 0) {
        insertTab(0, newPasswordTab, "Address Book");
    }
}

void PasswordWidget::setupTabs()
{
    QStringList groups;
    groups << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);
        QString regExp = QString("^[%1].*").arg(str);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(0);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);

        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        tableView->setSortingEnabled(true);

        connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &PasswordWidget::selectionChanged);

        connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
            auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
            if (tableView)
                emit selectionChanged(tableView->selectionModel()->selection());
        });

        addTab(tableView, str);
    }
}

void PasswordWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"),
            file.errorString());
        return;
    }

    QList<Pass> contacts;
    QDataStream in(&file);
    in >> contacts;

    if (contacts.isEmpty()) {
        QMessageBox::information(this, tr("Brak danych w pliku"),
                                 tr("Plik który próbujes otworzyć nie zawiera zapisanych haseł."));
    } else {
        for (const auto &contact: qAsConst(contacts))
            addEntry(contact.name, contact.login, contact.password);
    }
}

void PasswordWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << table->getPasses();
}
