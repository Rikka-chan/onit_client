#ifndef ADDANIMALDIALOG_H
#define ADDANIMALDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "databasesingleton.h"

class AddAnimalDialog: public QDialog
{
    Q_OBJECT
public:
    AddAnimalDialog(QWidget* parent=nullptr, QString _selected="");
private:
    QString selected;
    QLineEdit* name;
    QLineEdit* food;
    QPushButton* save;
};

#endif // ADDANIMALDIALOG_H
