#include "adddialog.h"
#include "newpasswordtab.h"

#include <QtWidgets>

//! [0]
NewPasswordTab::NewPasswordTab(QWidget *parent)
{
    Q_UNUSED(parent);

    descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
                                      "\nClick Add to add new contacts."));

    addButton = new QPushButton(tr("Add"));

    connect(addButton, &QAbstractButton::clicked, this, &NewPasswordTab::addEntry);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}
//! [0]

//! [1]
void NewPasswordTab::addEntry()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString login = aDialog.loginText->text();
        QString password = aDialog.passwordText->text();

        emit sendDetails(name, login, password);
    }
}
