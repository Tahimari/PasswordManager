#include "mypasswordmanager.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>

MyPasswordManager::MyPasswordManager()
{
    passwordWidget = new PasswordWidget;
    setCentralWidget(passwordWidget);
    createMenus();
    setWindowTitle(tr("MyPasswordManager"));
}

void MyPasswordManager::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Plik"));

    openAct = new QAction(tr("&Otwórz..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MyPasswordManager::openFile);

    saveAct = new QAction(tr("&Zapisz jako..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MyPasswordManager::saveFile);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("&Zakończ"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Narzędzia"));

    addAct = new QAction(tr("&Dodaj wpis..."), this);
    toolMenu->addAction(addAct);
    connect(addAct, &QAction::triggered, passwordWidget, &PasswordWidget::showAddEntryDialog);

    editAct = new QAction(tr("&Edytuj wpis..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, &QAction::triggered, passwordWidget, &PasswordWidget::editEntry);

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Usuń wpis"), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    connect(removeAct, &QAction::triggered, passwordWidget, &PasswordWidget::removeEntry);

    connect(passwordWidget, &PasswordWidget::selectionChanged,
        this, &MyPasswordManager::updateActions);
}

void MyPasswordManager::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        passwordWidget->readFromFile(fileName);
}

void MyPasswordManager::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
        passwordWidget->writeToFile(fileName);
}

void MyPasswordManager::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if (!indexes.isEmpty()) {
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }
}
