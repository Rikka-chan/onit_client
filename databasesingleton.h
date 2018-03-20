#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>


class DatabaseSingleton
{
public:
    static DatabaseSingleton& Instance()
    {
        static DatabaseSingleton s;
        return s;
    }
    
    bool connect();
    void create_connection(QString host, QString user, QString password, QString port, QString database);
    void add_param(QString name, QString value);
    void update_param(QString name, QString value);
    QString get_param(QString name);

private:
    QSqlDatabase db;
    QSqlDatabase db_params;

    DatabaseSingleton();
    ~DatabaseSingleton();

    DatabaseSingleton(DatabaseSingleton const&) = delete;
    DatabaseSingleton& operator= (DatabaseSingleton const&) = delete;
};

#endif // DATABASESINGLETON_H
