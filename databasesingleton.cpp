#include "databasesingleton.h"

DatabaseSingleton::DatabaseSingleton()
{
    db = QSqlDatabase::addDatabase("QPSQL", "main_connection");
}


DatabaseSingleton::~DatabaseSingleton()
{
}
