#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QLineEdit;
QT_END_NAMESPACE


class PasswordDialog : public QDialog
{
public:
    PasswordDialog(QWidget *parent = nullptr);
    QLineEdit *passwordText;

private:
    QLabel *passwordLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // PASSWORDDIALOG_H
