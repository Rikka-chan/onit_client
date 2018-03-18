#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    central = new QWidget(this);
    QGridLayout* centralLayout =  new QGridLayout(central);
    central->setLayout(centralLayout);
    setCentralWidget(central);

    AddUserDialog* add_user_dialog = new AddUserDialog();
    add_user_dialog->exec();

    SettingsDialog* sd = new SettingsDialog(this);
    sd->exec();
}
MainWindow::~MainWindow()
{

}
