#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class SettingsDialog: public QDialog
{
public:
    SettingsDialog(QWidget* parent=nullptr);
private:
    QLineEdit* host;
    QLineEdit* user;
    QLineEdit* password;
    QLineEdit* database;
    QLineEdit* port;
    QPushButton* apply;
};

#endif // SETTINGSDIALOG_H
