#include "adduserdialog.h"


AddUserDialog::AddUserDialog(QWidget* parent, QString message): QDialog(parent)
{
    QGridLayout* main_layout = new QGridLayout(this);
    setLayout(main_layout);
    create = new QPushButton("Create", this);
    username = new QLineEdit(this);
    password = new QLineEdit(this);

    QLabel* message_lbl = new QLabel(message, this);
    message_lbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    main_layout->addWidget(message_lbl, 0,0);
    main_layout->addWidget(new QLabel("Username", this),main_layout->rowCount(), 0);
    main_layout->addWidget(username, main_layout->rowCount() -1, 1);
    main_layout->addWidget(new QLabel("Password", this),main_layout->rowCount(), 0);
    main_layout->addWidget(password, main_layout->rowCount() -1, 1);
}
