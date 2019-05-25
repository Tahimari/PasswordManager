#ifndef MYPASSWORDMANAGER_H
#define MYPASSWORDMANAGER_H

#include <QMainWindow>

#include "passwordwidget.h"

namespace Ui {
class MyPasswordManager;
}

class MyPasswordManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyPasswordManager(QWidget *parent = nullptr);
    ~MyPasswordManager();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MyPasswordManager *ui;
    PasswordWidget *passwordWidget;
};

#endif // MYPASSWORDMANAGER_H
