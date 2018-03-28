#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCheckBox>

#include "addanimaldialog.h"
#include "adduserdialog.h"
#include "settingsdialog.h"
#include "databasesingleton.h"
#include "connectdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QTableWidget* users_table;
    QTableWidget* animals_table;
    QWidget* central;
    QString username;
    User user;
    QPushButton* add_user_btn;
    QPushButton* delete_user_btn;
    QPushButton* add_animal_btn;
    QPushButton* delete_animal_btn;
    Permission permissions;
    bool users_filled;
    bool animals_filled;

    void fill_users_table();
    void fill_animals_table();
};

#endif // MAINWINDOW_H
