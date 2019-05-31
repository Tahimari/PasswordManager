#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QLineEdit;
QT_END_NAMESPACE

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = nullptr);
    QLineEdit *nameText;
    QLineEdit *loginText;
    QLineEdit *passwordText;
    void generatePassword(int length);

private:
    QLabel *nameLabel;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *generateButton;
};

#endif // ADDDIALOG_H
