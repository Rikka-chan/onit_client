#include "adduserdialog.h"


AddUserDialog::AddUserDialog(QWidget* parent, QString message, bool is_admin): QDialog(parent)
{
    QGridLayout* main_layout = new QGridLayout(this);
    setLayout(main_layout);
    create = new QPushButton("Create", this);
    warning = new QLabel("", this);
    username = new QLineEdit(this);
    password = new QLineEdit(this);
    confirm =  new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);
    confirm->setEchoMode(QLineEdit::Password);

    if(is_admin){
        username->setText("ADMIN");
        username->setEnabled(false);
    }
    warning->setStyleSheet("color: #110000;");

    QLabel* message_lbl = new QLabel(message, this);
    message_lbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    main_layout->addWidget(message_lbl, 0,0, 1, 2);
    main_layout->addWidget(new QLabel("Username", this),main_layout->rowCount(), 0);
    main_layout->addWidget(username, main_layout->rowCount() -1, 1);
    main_layout->addWidget(new QLabel("Password", this),main_layout->rowCount(), 0);
    main_layout->addWidget(password, main_layout->rowCount() -1, 1);
    main_layout->addWidget(new QLabel("Confirm", this),main_layout->rowCount(), 0);
    main_layout->addWidget(confirm, main_layout->rowCount() -1, 1);

    main_layout->addWidget(warning, main_layout->rowCount() ,0, 1, 2);

    main_layout->addWidget(create, main_layout->rowCount(), 1, 1, 2,Qt::AlignLeft);

    connect(create, &QPushButton::clicked, [this]() {emit created(username->text(), password->text());});
    connect(username, &QLineEdit::textChanged, this, &AddUserDialog::check);
    connect(password, &QLineEdit::textChanged, this, &AddUserDialog::check);
    connect(confirm, &QLineEdit::textChanged, this, &AddUserDialog::check);
}

void AddUserDialog::check(){
    if(password->text() != confirm->text()){
        warning->setText("Passwords not matching!");
        create->setEnabled(false);
    }
    else if(username->text().length() == 0){
        warning->setText("Username is empty!");
        create->setEnabled(false);
    }
    else{
        warning->setText("");
        create->setEnabled(true);
    }
}
