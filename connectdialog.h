#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>
#include "databasesingleton.h"
#include <QCryptographicHash>


class ConnectDialog: public QDialog
{
    Q_OBJECT
public:
    ConnectDialog(QWidget* parent);
private:
    QLineEdit* user_name;
    QLineEdit* password;
    QLabel* warning;
    bool connected;
    void login();

signals:
    void logedin(QString username);
};

#endif // CONNECTDIALOG_H
