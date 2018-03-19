#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QtSql/QSqlDatabase>


class DatabaseSingleton
{
public:
    static DatabaseSingleton& Instance()
    {
        static DatabaseSingleton s;
        return s;
    }


private:
    QSqlDatabase db;
    QSqlDatabase db_params;

    DatabaseSingleton();
    ~DatabaseSingleton();

    DatabaseSingleton(DatabaseSingleton const&) = delete;
    DatabaseSingleton& operator= (DatabaseSingleton const&) = delete;
};

#endif // DATABASESINGLETON_H
