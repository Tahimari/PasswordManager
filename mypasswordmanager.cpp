#include "mypasswordmanager.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>

MyPasswordManager::MyPasswordManager()
{
    passwordWidget = new PasswordWidget;
    setCentralWidget(passwordWidget);
    createMenus();
    setWindowTitle(tr("Address Book"));
}

void MyPasswordManager::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MyPasswordManager::openFile);

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MyPasswordManager::saveFile);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Tools"));

    addAct = new QAction(tr("&Add Entry..."), this);
    toolMenu->addAction(addAct);
    connect(addAct, &QAction::triggered, passwordWidget, &PasswordWidget::showAddEntryDialog);

    editAct = new QAction(tr("&Edit Entry..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, &QAction::triggered, passwordWidget, &PasswordWidget::editEntry);

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Remove Entry"), this);
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
