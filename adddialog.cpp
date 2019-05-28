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
    generateButton = new QPushButton("Generuj hasło");

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

    buttonLayout->addWidget(generateButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    okButton->setDefault(true);

    gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(generateButton, &QAbstractButton::clicked, this, &AddDialog::generatePassword);
    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Dodaj wpis"));
}

void AddDialog::generatePassword(int length)
{
    length = 16;
    QString str;
    str.resize(length);
    for (int s = 0; s < length ; ++s)
        if(qrand() % 3 == 0)
            str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));
        else if(qrand() % 3 == 1)
            str[s] = QString::number(qrand() % 10).at(0);
        else
            str[s] = QChar('a' + char(qrand() % ('z' - 'a')));

    passwordText->setText(str);
}
