#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget* parent): QDialog(parent)
{
    QGridLayout* main_layout = new QGridLayout(this);
    setLayout(main_layout);
    warning = new QLabel("", this);
    password = new QLineEdit(this);
    user = new QLineEdit(this);
    host = new QLineEdit(this);
    port = new QLineEdit(this);
    database = new QLineEdit(this);
    apply = new QPushButton("Apply", this);

    main_layout->addWidget(new QLabel("User", this), main_layout->rowCount(), 0);
    main_layout->addWidget(user, main_layout->rowCount() -1, 1);
    main_layout->addWidget(new QLabel("Password", this), main_layout->rowCount(), 0);
    main_layout->addWidget(password, main_layout->rowCount() -1, 1);
    main_layout->addWidget(new QLabel("Host", this), main_layout->rowCount(), 0);
    main_layout->addWidget(host, main_layout->rowCount() -1, 1);
    main_layout->addWidget(new QLabel("Port", this), main_layout->rowCount(), 0);
    main_layout->addWidget(port, main_layout->rowCount() -1, 1);
    main_layout->addWidget(new QLabel("Database", this), main_layout->rowCount(), 0);
    main_layout->addWidget(database, main_layout->rowCount() -1, 1);
    main_layout->addWidget(warning, main_layout->rowCount(), 0, 1, 2);

    main_layout->addWidget(apply, main_layout->rowCount(), 1, 1,1,Qt::AlignRight);
    setWindowTitle("Settings for database connection");

    connect(apply, &QPushButton::clicked, this, &SettingsDialog::save);
}

void SettingsDialog::save(){
    DatabaseSingleton& db_instance = DatabaseSingleton::Instance();
    bool is_connected = db_instance.connect(host->text(), user->text(), password->text(), port->text(),database->text());
    if(is_connected){
        db_instance.create_connection(host->text(), user->text(), password->text(), port->text(),database->text());
        close();
    }
    else
        warning->setText("Connection failed. Settings not saved.");
}

