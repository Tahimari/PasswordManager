#ifndef NEWPASSWORDTAB_H
#define NEWPASSWORDTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

//! [0]
class NewPasswordTab : public QWidget
{
    Q_OBJECT

public:
    NewPasswordTab(QWidget *parent = 0);

public slots:
    void addEntry();

signals:
    void sendDetails(QString name, QString login, QString password);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;

};

#endif // NEWPASSWORDTAB_H
