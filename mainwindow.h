#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "adduserdialog.h"
#include "settingsdialog.h"
#include "databasesingleton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QWidget* central;
private slots:
    void create_user(QString username, QString password);
};

#endif // MAINWINDOW_H
