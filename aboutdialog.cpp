#include "aboutdialog.h"

#include <QtWidgets>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    info = new QLabel("My Password Manager 1.0\n"
                      "Prosty menadżer haseł \n stworzony do przechowywania informacji\n\n"
                      "Kamil Misiak\n"
                      "2019");

    cancelButton = new QPushButton("Anuluj");

    QGridLayout *gLayout = new QGridLayout;
    info->setAlignment(Qt::AlignCenter);
    gLayout->addWidget(info, 0, 0);

    gLayout->addWidget(cancelButton, 1, 0, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("O programie"));
}
