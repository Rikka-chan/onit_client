#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget* parent): QDialog(parent)
{
    QGridLayout* main_layout = new QGridLayout(this);
    setLayout(main_layout);
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

    main_layout->addWidget(apply, main_layout->rowCount(), 1, 1,1,Qt::AlignRight);
}