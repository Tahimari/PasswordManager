#include "adddialog.h"
#include "aboutdialog.h"
#include "passwordwidget.h"

#include <QtWidgets>

//! [0]
PasswordWidget::PasswordWidget(QWidget *parent)
    : QTabWidget(parent)
{
//    table = new TableModel(this);
//    newAddressTab = new NewAddressTab(this);
//    connect(newAddressTab, &NewAddressTab::sendDetails,
//        this, &AddressWidget::addEntry);

//    addTab(newAddressTab, "Address Book");

//    setupTabs();
}

void PasswordWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.loginText->text();
        QString address = aDialog.passwordText->text();

        //addEntry(name, address);
    }
}

void PasswordWidget::showInfoDialog()
{
    AboutDialog aDialog;
    aDialog.exec();
}
