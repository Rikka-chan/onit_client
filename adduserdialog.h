#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include "databasesingleton.h"
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCryptographicHash>

class AddUserDialog: public QDialog
{
    Q_OBJECT
public:
    AddUserDialog(QWidget* parent=nullptr, QString message="", bool is_admin=false);
private:
    QLineEdit* username;
    QLineEdit* password;
    QLineEdit* confirm;
    QPushButton* create;
    QLabel* warning;

private slots:
    void check();
    void create_user();
};

#endif // ADDUSERDIALOG_H
