#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class AddUserDialog: public QDialog
{
public:
    AddUserDialog(QWidget* parent=nullptr, QString message="");
private:
    QLineEdit* username;
    QLineEdit* password;
    QPushButton* create;
};

#endif // ADDUSERDIALOG_H
