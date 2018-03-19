#include "databasesingleton.h"

DatabaseSingleton::DatabaseSingleton()
{
    db_params = QSqlDatabase::addDatabase("QSQLITE", "params");

}


DatabaseSingleton::~DatabaseSingleton()
{
}
