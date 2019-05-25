#include "adddialog.h"

#include <QtWidgets>

//! [0]
AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
{
    nameLabel = new QLabel("Nazwa");
    loginLabel = new QLabel("Login");
    passwordLabel = new QLabel("Hasło");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Anuluj");

    nameText = new QLineEdit;
    loginText = new QLineEdit;
    passwordText = new QLineEdit;

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    gLayout->addWidget(line, 1, 0, 1, 2);

    gLayout->addWidget(loginLabel, 2, 0);
    gLayout->addWidget(loginText, 2, 1);

    gLayout->addWidget(passwordLabel, 3, 0);
    gLayout->addWidget(passwordText, 3, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Dodaj wpis"));
}
