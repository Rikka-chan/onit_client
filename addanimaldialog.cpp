#include "addanimaldialog.h"

AddAnimalDialog::AddAnimalDialog(QWidget* parent, QString sel): QDialog(parent)
{
    selected = sel;
    QGridLayout* main_layout = new QGridLayout(this);
    setLayout(main_layout);

    name = new QLineEdit(this);
    food = new QLineEdit(this);
    save = new QPushButton("Save", this);

    save->setEnabled(false);

    main_layout->addWidget(new QLabel("Name", this), main_layout->rowCount(), 0);
    main_layout->addWidget(name, main_layout->rowCount() - 1, 1);

    main_layout->addWidget(new QLabel("Food", this), main_layout->rowCount(), 0);
    main_layout->addWidget(food, main_layout->rowCount() - 1, 1);
    main_layout->addWidget(save, main_layout->rowCount(), 1, 1 ,2, Qt::AlignRight);

    connect(name, &QLineEdit::textChanged, [this](){
        if(name->text() == "" )
            save->setEnabled(false);
        else
            save->setEnabled(true);
    });
    connect(save, &QPushButton::clicked, [this](){
        if(selected == "")
            DatabaseSingleton::Instance().add_animal(name->text(), food->text());
        close();
    });
}
