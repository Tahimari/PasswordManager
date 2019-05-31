#include "adddialog.h"
#include "passworddialog.h"
#include "aboutdialog.h"
#include "passwordwidget.h"

#include <QtWidgets>
#include <QCryptographicHash>

PasswordWidget::PasswordWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel(this);
    newPasswordTab = new NewPasswordTab(this);
    connect(newPasswordTab, &NewPasswordTab::sendDetails,
            this, &PasswordWidget::addEntry);

    addTab(newPasswordTab, "Password manager");

    setupTab();
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

QString PasswordWidget::showPasswordDialog()
{
    PasswordDialog pDialog;

    if (pDialog.exec()) {
        QString password = pDialog.passwordText->text();

        return password;
    }
    return "";
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
        table->setData(index, login, Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, password, Qt::EditRole);
        removeTab(indexOf(newPasswordTab));
    } else {
        QMessageBox::information(this, tr("Zła nazwa"),
                                 tr("Nazwa \"%1\" już istnieje.").arg(name));
    }
}

void PasswordWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString login;
    QString password;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex loginIndex = table->index(row, 1, QModelIndex());
        QVariant varLogin = table->data(loginIndex, Qt::DisplayRole);
        login = varLogin.toString();

        QModelIndex passwordIndex = table->index(row, 2, QModelIndex());
        QVariant varPassword = table->data(passwordIndex, Qt::DisplayRole);
        password = varPassword.toString();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edytuj wpis"));

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.loginText->setText(login);
    aDialog.passwordText->setText(password);

    if (aDialog.exec()) {
        QString newLogin = aDialog.loginText->text();
        if (newLogin != login) {
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newLogin, Qt::EditRole);
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
        insertTab(0, newPasswordTab, "Password manager");
    }
}

void PasswordWidget::hideEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
    }

    QModelIndex index = table->index(row, 2, QModelIndex());
    table->hidePassword(index, Qt::EditRole);
}

void PasswordWidget::removeAllEntry()
{
    if (table->rowCount(QModelIndex()) > 0) {
        table = new TableModel(this);
    }else {
        insertTab(0, newPasswordTab, "Password manager");
    }
}

void PasswordWidget::setupTab()
{
    QString str = "Twoje hasła";
    QString regExp = QString("^[%1].*").arg(str);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(table);
    //proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive));
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

void PasswordWidget::readFromFile(const QString &fileName, const QString password)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"),
                                 file.errorString());
        return;
    }

    QList<Pass> passes;
    QDataStream in(&file);

    QByteArray bytePassword = password.toUtf8();
    QString hashedPassword = QString(QCryptographicHash::hash(bytePassword, (QCryptographicHash::Md5)));

    QString filePassword;
    in >> filePassword;
    in >> passes;

    bool isPasswordValid = false;
    if (hashedPassword == filePassword){
        isPasswordValid = true;
    }

    if (!isPasswordValid) {
        QMessageBox::information(this, tr("Nie poprawne hasło"),
                                 tr("Podane hasło jest niepoprawne."));
    } else if (passes.isEmpty()) {
        QMessageBox::information(this, tr("Brak danych w pliku"),
                                 tr("Plik który próbujes otworzyć nie zawiera zapisanych haseł."));
    } else {
        for (const auto &pass: qAsConst(passes))
            addEntry(pass.name, pass.login, pass.password);
    }
}

void PasswordWidget::writeToFile(const QString &fileName, const QString password)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"), file.errorString());
        return;
    }

    QDataStream out(&file);
    QByteArray bytePassword = password.toUtf8();
    out << QString(QCryptographicHash::hash(bytePassword, (QCryptographicHash::Md5)));
    out << table->getPasses();
}
