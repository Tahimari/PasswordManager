#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = nullptr);

private:
    QLabel *info;
    QPushButton *cancelButton;
};

#endif // ABOUTDIALOG_H
