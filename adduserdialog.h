#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

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
    bool check(QString);
};

#endif // ADDUSERDIALOG_H
