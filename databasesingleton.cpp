#include "databasesingleton.h"

DatabaseSingleton::DatabaseSingleton()
{
    db_params = QSqlDatabase::addDatabase("QSQLITE", "params");
    db.open();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS params (name text NOT NULL PRIMARY KEY, value text);");
    add_param("user", "");
    add_param("password", "");
    add_param("host", "");
    add_param("port", "");
    add_param("database", "");
}

bool DatabaseSingleton::connect(){
    db =QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(get_param("host"));
    db.setDatabaseName(get_param("database"));
    db.setUserName(get_param("user"));
    db.setPassword(get_param("password"));
    db.setPort(get_param("port").toInt());

    bool ok = db.open();
    if(ok)
        db_params.close();
    return ok;
}


void DatabaseSingleton::create_connection(QString host, QString user, QString password, QString port, QString database){
    if(!db_params.isOpen())
        db_params.open();
    update_param("host", host);
    update_param("user", user);
    update_param("password", password);
    update_param("port", port);
    update_param("database", database);
}

void DatabaseSingleton::add_param(QString name, QString value){
    QSqlQuery query;
    query.prepare("INSERT INTO params (name, value) VALUES (:name, :value);");
    query.bindValue(":name", name);
    query.bindValue(":value", value);
    query.exec();
    qDebug() << query.lastError();
}
void DatabaseSingleton::update_param(QString name, QString value){
    QSqlQuery query;
    query.prepare("UPDATE params SET value =:value WHERE name =:name;");
    query.bindValue(":name", name);
    query.bindValue(":value", value);
    query.exec();
    qDebug() << query.lastError();
}

QString DatabaseSingleton::get_param(QString name){
    QSqlQuery query;
    query.prepare("SELECT value FROM params WHERE name =:name;");
    query.bindValue(":name", name);
    query.exec();
    qDebug() << query.lastError();
    return query.value(0).toString();
}

DatabaseSingleton::~DatabaseSingleton()
{
}
