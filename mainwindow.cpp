#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    users_filled = false;
    animals_filled = false;
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

    ConnectDialog* cd = new ConnectDialog(this);
    connect(cd, &ConnectDialog::logedin, [this](QString user){
        this->username = user;
        User u = DatabaseSingleton::Instance().get_user(username);
        permissions = DatabaseSingleton::Instance().get_permission(u.id);

    });
    cd->exec();
    if(username == "") QTimer::singleShot(0, this, SLOT(close()));



    users_table = new QTableWidget(this);
    users_table->setRowCount(0);
    users_table->setColumnCount(6);
    users_table->setHorizontalHeaderLabels(QStringList({"Username", "Admin", "Write", "Read", "Update", "Delete"}));

    add_user_btn = new QPushButton("Add user", this);
    add_user_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    delete_user_btn = new QPushButton("Delete user", this);
    delete_user_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    animals_table = new QTableWidget(this);
    animals_table->setRowCount(0);
    animals_table->setColumnCount(2);
    animals_table->setHorizontalHeaderLabels(QStringList({"Name", "Food"}));
    animals_table->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    add_animal_btn = new QPushButton("Add animal", this);
    add_animal_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    delete_animal_btn = new QPushButton("Delete animal", this);
    delete_animal_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QWidget* buttons = new QWidget(this);
    QGridLayout* buttons_layout = new QGridLayout(buttons);
    buttons->setLayout(buttons_layout);

    buttons_layout->addWidget(add_animal_btn, buttons_layout->rowCount(), 0);
    buttons_layout->addWidget(delete_animal_btn, buttons_layout->rowCount(), 0);

    QWidget* user_buttons = new QWidget(this);
    QGridLayout* user_buttons_layout = new QGridLayout(user_buttons);
    user_buttons->setLayout(user_buttons_layout);

    user_buttons_layout->addWidget(add_user_btn, user_buttons_layout->rowCount(), 0);
    user_buttons_layout->addWidget(delete_user_btn, user_buttons_layout->rowCount(), 0);

    central_layout->addWidget(users_table, central_layout->rowCount(), 0);
    central_layout->addWidget(user_buttons, central_layout->rowCount() -1, 1, Qt::AlignTop);

    central_layout->addWidget(animals_table, central_layout->rowCount(), 0);
    central_layout->addWidget(buttons, central_layout->rowCount() -1, 1, Qt::AlignTop);

    fill_users_table();
    fill_animals_table();

    connect(add_user_btn, &QPushButton::clicked, [this](){
        AddUserDialog* aud = new AddUserDialog(this);
        aud->exec();
        fill_users_table();
    });

    connect(add_animal_btn, &QPushButton::clicked, [this](){
        AddAnimalDialog* aad = new AddAnimalDialog(this);
        aad->exec();
        fill_animals_table();
    });

    connect(animals_table, &QTableWidget::cellChanged, [this](int cur_row){
        if (!animals_filled) return;
        QString name = animals_table->item(cur_row, 0)->text();
        QString food = animals_table->item(cur_row, 1)->text();
        int id = animals_table->item(cur_row, 0)->data(Qt::UserRole).toInt();
        Animal current_animal = DatabaseSingleton::Instance().get_animal(id);

        if(current_animal.name != name || current_animal.food != food){
            DatabaseSingleton::Instance().update_animal(id, name, food);
            current_animal = DatabaseSingleton::Instance().get_animal(id);
            animals_table->item(cur_row, 0)->setText(current_animal.name);
            animals_table->item(cur_row, 1)->setText(current_animal.food);
        }
    });

    connect(users_table, &QTableWidget::cellChanged, [this](int row, int col){
        if(!users_filled) return;
        int id = users_table->item(row, 0)->data(Qt::UserRole).toInt();
        qDebug() << row << "     " << col << id;
        if(col == 0){
            DatabaseSingleton::Instance().update_user(id,users_table->item(row, 0)->text());
            fill_users_table();
        }
        else{
            QStringList perms({"Username", "Admin", "Write", "Read", "Update", "Delete"});
            if(users_table->item(row, col)->checkState() == Qt::Checked)
                DatabaseSingleton::Instance().add_permission(id, perms[col].toUpper());
            else
                DatabaseSingleton::Instance().delete_permission(id, perms[col].toUpper());
        }
    });

    connect(delete_user_btn, &QPushButton::clicked, [this](){
        if(users_table->currentRow() == -1) return;
        int id = users_table->item(users_table->currentRow(), 0)->data(Qt::UserRole).toInt();
        DatabaseSingleton::Instance().delete_user(id);
        fill_users_table();
    });

    connect(delete_animal_btn, &QPushButton::clicked, [this](){
        if(animals_table->currentRow() == -1) return;
        int id = animals_table->item(animals_table->currentRow(), 0)->data(Qt::UserRole).toInt();
        DatabaseSingleton::Instance().delete_animal(id);
        fill_animals_table();
    });

    if(!permissions.admin){
        user_buttons->setVisible(false);
        users_table->setVisible(false);
    }
    if(!permissions.write)
        add_animal_btn->setEnabled(false);
    if(!permissions.del)
        delete_animal_btn->setEnabled(false);

}

void MainWindow::fill_users_table(){
    users_filled = false;
    std::vector<User> users = DatabaseSingleton::Instance().get_users();
    users_table->setRowCount(users.size());
    for(int i =0; i< users.size();i++){
        QTableWidgetItem* tmp = new QTableWidgetItem(users[i].name);

        tmp->setData(Qt::UserRole, users[i].id);
        users_table->setItem(i, 0, tmp);

        Permission permission = DatabaseSingleton::Instance().get_permission(users[i].id);

        qDebug() << permission.admin<< permission.write<< permission.read<< permission.read<< permission.update<< permission.del;
        users_table->setItem(i,1, new QTableWidgetItem());
        users_table->setItem(i,2, new QTableWidgetItem());
        users_table->setItem(i,3, new QTableWidgetItem());
        users_table->setItem(i,4, new QTableWidgetItem());
        users_table->setItem(i,5, new QTableWidgetItem());

        users_table->item(i, 1)->setCheckState(permission.admin ? Qt::Checked : Qt::Unchecked);
        users_table->item(i, 2)->setCheckState(permission.write ? Qt::Checked : Qt::Unchecked);
        users_table->item(i, 3)->setCheckState(permission.read ? Qt::Checked : Qt::Unchecked);
        users_table->item(i, 4)->setCheckState(permission.update ? Qt::Checked : Qt::Unchecked);
        users_table->item(i, 5)->setCheckState(permission.del ? Qt::Checked : Qt::Unchecked);
    }
    users_filled = true;
}

void MainWindow::fill_animals_table(){
    if(!permissions.read) return;
    animals_filled = false;
    std::vector<Animal> animals = DatabaseSingleton::Instance().get_animals();
    animals_table->setRowCount(animals.size());
    for(int i =0; i< animals.size();i++){
        QTableWidgetItem* name = new QTableWidgetItem(animals[i].name);
        QTableWidgetItem* food = new QTableWidgetItem(animals[i].food);
        name->setData(Qt::UserRole, animals[i].id);

        if(!permissions.update){
            name->setFlags(name->flags() ^ Qt::ItemIsEditable);
            food->setFlags(food->flags() ^ Qt::ItemIsEditable);
        }
        animals_table->setItem(i, 0, name);
        animals_table->setItem(i, 1, food);
    }
    animals_filled = true;
}

MainWindow::~MainWindow()
{

}
