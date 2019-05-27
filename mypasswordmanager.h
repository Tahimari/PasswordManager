#ifndef MYPASSWORDMANAGER_H
#define MYPASSWORDMANAGER_H

#include <QMainWindow>

#include "passwordwidget.h"

class MyPasswordManager : public QMainWindow
{
    Q_OBJECT

public:
    MyPasswordManager();

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();

private:
    void createMenus();

    PasswordWidget *passwordWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;
};

#endif // MYPASSWORDMANAGER_H
