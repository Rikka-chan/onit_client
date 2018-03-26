#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    central = new QWidget(this);
    QGridLayout* central_layout =  new QGridLayout(central);
    central->setLayout(central_layout);
    setCentralWidget(central);

    DatabaseSingleton& db_instance = DatabaseSingleton::Instance();
    bool is_connected = db_instance.connect();

    if(!is_connected){
        SettingsDialog* settings =  new SettingsDialog(this);
        settings->exec();
    }
    qDebug()<< db_instance.count_users();
    if(db_instance.count_users() == 0){
        AddUserDialog* add_user = new AddUserDialog(this, "You need to create ADMIN user.", true);
        add_user->exec();
    }
    else{
        ConnectDialog* cd = new ConnectDialog(this);
        connect(cd, &ConnectDialog::logedin, [this](QString user){
            this->username = user;
        });
        cd->exec();
        if(username == "") QTimer::singleShot(0, this, SLOT(close()));
    }

    users_table = new QTableWidget(this);
    users_table->setRowCount(0);
    users_table->setColumnCount(1);
    users_table->setHorizontalHeaderLabels(QStringList("Username"));
    users_table->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    add_user_btn = new QPushButton("Add user", this);

    central_layout->addWidget(users_table, central_layout->rowCount(), 0);
    central_layout->addWidget(add_user_btn, central_layout->rowCount() -1, 1, Qt::AlignTop);
    fill_users_table();
}

void MainWindow::fill_users_table(){
    QStringList users = DatabaseSingleton::Instance().get_users();
    users_table->setRowCount(users.length());
    for(int i =0; i< users.length();i++){
        QTableWidgetItem* tmp = new QTableWidgetItem(users[i]);
        users_table->setItem(i, 0, tmp);
    }
}

MainWindow::~MainWindow()
{

}
