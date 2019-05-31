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
    void removeAll();
    void connectMenus(PasswordWidget *passwordWidget);

    PasswordWidget *passwordWidget;
    QToolBar *toolBar;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *otherMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;
    QAction *hideAct;
    QAction *removeAllAct;
    QAction *aboutAct;
};

#endif // MYPASSWORDMANAGER_H
