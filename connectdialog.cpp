#include "connectdialog.h"

ConnectDialog::ConnectDialog(QWidget* parent): QDialog(parent)
{
 QGridLayout* main_layout = new QGridLayout(this);
 setLayout(main_layout);

 QPushButton* login_btn = new QPushButton("Login", this);
 QLabel* user_name_label = new QLabel("Username:", this);
 QLabel* password_label = new QLabel("Password:", this);


}
