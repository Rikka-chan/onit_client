#include "connectdialog.h"

ConnectDialog::ConnectDialog(QWidget* parent): QDialog(parent)
{
 connected = false;
 QGridLayout* main_layout = new QGridLayout(this);
 setLayout(main_layout);

 QPushButton* login_btn = new QPushButton("Login", this);
 user_name = new QLineEdit(this);
 password = new QLineEdit(this);
 warning = new QLabel(this);

 password->setEchoMode(QLineEdit::Password);

 main_layout->addWidget(new QLabel("Username", this), main_layout->rowCount(), 0);
 main_layout->addWidget(user_name, main_layout->rowCount() - 1, 1);
 main_layout->addWidget(new QLabel("Password", this), main_layout->rowCount(), 0);
 main_layout->addWidget(password, main_layout->rowCount() - 1, 1);

 main_layout->addWidget(warning, main_layout->rowCount(), 0 , 1, 2, Qt::AlignCenter);
 main_layout->addWidget(login_btn, main_layout->rowCount(), 0, 1, 2, Qt::AlignRight);

 connect(login_btn, &QPushButton::clicked, this, &ConnectDialog::login);
 this->setWindowTitle("Sign in");
}


void ConnectDialog::login(){
    DatabaseSingleton& db_instance = DatabaseSingleton::Instance();
    connected = db_instance.login(user_name->text(),
                                  QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Md5));

    if(connected){
        emit logedin(user_name->text());
        close();
    }
    else
        warning->setText("Wrong username or password");
}
