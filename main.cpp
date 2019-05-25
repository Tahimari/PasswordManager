#include "mypasswordmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyPasswordManager w;
    w.show();

    return a.exec();
}
