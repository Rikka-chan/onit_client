#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <vector>


struct User
{
    QString name;
    int id;
};

struct Animal{
    QString name;
    QString food;
    int id;
};

struct Permission{
    Permission(): admin(false), read(false), write(false), update(false), del(false){}
    bool admin;
    bool read;
    bool write;
    bool update;
    bool del;
};

class DatabaseSingleton
{
public:
    static DatabaseSingleton& Instance()
    {
        static DatabaseSingleton s;
        return s;
    }
    
    bool connect();
    bool connect(QString host, QString user, QString password, QString port, QString database);
    void create_connection(QString host, QString user, QString password, QString port, QString database);
    void create_db();
    void add_param(QString name, QString value);
    void update_param(QString name, QString value);
    int count_users();
    void add_user(QString username, QString password);
    void update_user(int id, QString login);
    bool login(QString username, QString password);
    QString get_param(QString name);
    std::vector<User> get_users();
    User get_user(QString username);
    void delete_user(int id);

    std::vector<Animal> get_animals();
    Animal get_animal(int id);
    void add_animal(QString name, QString food);
    void update_animal(int id, QString name, QString food);
    void delete_animal(int id);
    void set_permission(int id, Permission permission);
    Permission get_permission(int id);
    void add_permission(int id, QString perm);
    void delete_permission(int id, QString perm);


private:
    QSqlDatabase db;
    QSqlDatabase db_params;

    DatabaseSingleton();
    ~DatabaseSingleton();

    DatabaseSingleton(DatabaseSingleton const&) = delete;
    DatabaseSingleton& operator= (DatabaseSingleton const&) = delete;
};

#endif // DATABASESINGLETON_H
