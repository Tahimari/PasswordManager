#include "mypasswordmanager.h"
#include "ui_mypasswordmanager.h"

MyPasswordManager::MyPasswordManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyPasswordManager)
{
    ui->setupUi(this);
    passwordWidget = new PasswordWidget;
}

MyPasswordManager::~MyPasswordManager()
{
    delete ui;
}

void MyPasswordManager::on_pushButton_4_clicked()
{
    passwordWidget->showAddEntryDialog();
}

void MyPasswordManager::on_pushButton_2_clicked()
{
    passwordWidget->showInfoDialog();
}
