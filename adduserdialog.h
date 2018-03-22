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
signals:
    void created(QString username, QString password);
private slots:
    void check();
};

#endif // ADDUSERDIALOG_H
