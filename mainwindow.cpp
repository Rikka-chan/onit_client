#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    central = new QWidget(this);
    QGridLayout* centralLayout =  new QGridLayout(central);
    central->setLayout(centralLayout);
    setCentralWidget(central);

    DatabaseSingleton& db_instance = DatabaseSingleton::Instance();
    bool is_connected = db_instance.connect();

    if(!is_connected){
        AddUserDialog* add_user = new AddUserDialog(this, "You need to create ADMIN user.", true);
        add_user->exec();
    }
}
MainWindow::~MainWindow()
{

}
