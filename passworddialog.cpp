#include "passworddialog.h"

#include <QtWidgets>


PasswordDialog::PasswordDialog(QWidget *parent)
    : QDialog(parent)
{
    passwordLabel = new QLabel("Hasło");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Anuluj");

    passwordText = new QLineEdit;
    passwordText->setEchoMode(QLineEdit::Password);

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(passwordLabel, 0, 0);
    gLayout->addWidget(passwordText, 0, 1);


    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    okButton->setDefault(true);

    gLayout->addLayout(buttonLayout, 1, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Podaj hasło do pliku"));
}
