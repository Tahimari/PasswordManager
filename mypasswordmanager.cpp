#include "mypasswordmanager.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QDebug>

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
    toolBar = this->addToolBar(tr("&Narzędzie"));

    addAct = new QAction(tr("&Dodaj wpis..."), this);
    toolMenu->addAction(addAct);
    toolBar->addAction(addAct);
    connect(addAct, &QAction::triggered, passwordWidget, &PasswordWidget::showAddEntryDialog);


    editAct = new QAction(tr("&Edytuj wpis..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    toolBar->addAction(editAct);
    connect(editAct, &QAction::triggered, passwordWidget, &PasswordWidget::editEntry);

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Usuń wpis"), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    toolBar->addAction(removeAct);
    connect(removeAct, &QAction::triggered, passwordWidget, &PasswordWidget::removeEntry);

    toolMenu->addSeparator();

    hideAct = new QAction(tr("&Schowaj/pokaż hasło"), this);
    hideAct->setEnabled(false);
    toolMenu->addAction(hideAct);
    toolBar->addAction(hideAct);
    connect(hideAct, &QAction::triggered, passwordWidget, &PasswordWidget::hideEntry);

    removeAllAct = new QAction(tr("&Usuń wszystko"), this);
    toolBar->addAction(removeAllAct);
    connect(removeAllAct, &QAction::triggered, this, &MyPasswordManager::removeAll);

    otherMenu = menuBar()->addMenu(tr("&Inne"));

    aboutAct = new QAction(tr("&O programie"), this);
    otherMenu->addAction(aboutAct);
    connect(aboutAct, &QAction::triggered, passwordWidget, &PasswordWidget::showInfoDialog);

    connect(passwordWidget, &PasswordWidget::selectionChanged,
        this, &MyPasswordManager::updateActions);
}

void MyPasswordManager::connectMenus(PasswordWidget *passwordWidget)
{
    connect(addAct, &QAction::triggered, passwordWidget, &PasswordWidget::showAddEntryDialog);
    connect(editAct, &QAction::triggered, passwordWidget, &PasswordWidget::editEntry);
    connect(aboutAct, &QAction::triggered, passwordWidget, &PasswordWidget::showInfoDialog);
    connect(removeAct, &QAction::triggered, passwordWidget, &PasswordWidget::removeEntry);
    connect(hideAct, &QAction::triggered, passwordWidget, &PasswordWidget::hideEntry);
    connect(passwordWidget, &PasswordWidget::selectionChanged,
        this, &MyPasswordManager::updateActions);
}

void MyPasswordManager::removeAll()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdź", "Czy jesteś pewny że chcesz usunąć wszystkie wpisy?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          passwordWidget = new PasswordWidget;
          setCentralWidget(passwordWidget);
          removeAct->setEnabled(false);
          editAct->setEnabled(false);
          hideAct->setEnabled(false);
          connectMenus(passwordWidget);
      } else {
      }
}

void MyPasswordManager::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QString password = passwordWidget->showPasswordDialog();

    if (!fileName.isEmpty())
        passwordWidget->readFromFile(fileName, password);
}

void MyPasswordManager::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QString password = passwordWidget->showPasswordDialog();
    if (!fileName.isEmpty())
        passwordWidget->writeToFile(fileName, password);
}

void MyPasswordManager::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if (!indexes.isEmpty()) {
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
        hideAct->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
        hideAct->setEnabled(false);
    }
}
