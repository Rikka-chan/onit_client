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
};

#endif // MAINWINDOW_H
