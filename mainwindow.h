#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>

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
    void fill_users_table();
    QPushButton* add_user_btn;
};

#endif // MAINWINDOW_H
