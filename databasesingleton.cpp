#include "databasesingleton.h"

DatabaseSingleton::DatabaseSingleton()
{
    db_params = QSqlDatabase::addDatabase("QSQLITE", "params");
    db_params.setDatabaseName("params.db3");
    db_params.open();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS params (name text NOT NULL PRIMARY KEY, value text);");
    qDebug() << query.lastError();
    add_param("user", "");
    add_param("password", "");
    add_param("host", "");
    add_param("port", "");
    add_param("database", "");

}

bool DatabaseSingleton::connect(){
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(get_param("host"));
    db.setDatabaseName(get_param("database"));
    db.setUserName(get_param("user"));
    db.setPassword(get_param("password"));
    db.setPort(get_param("port").toInt());

    bool ok = db.open();

    return ok;
}

bool DatabaseSingleton::connect(QString host, QString user, QString password, QString port, QString database){
    db = QSqlDatabase::addDatabase("QPSQL", "client");
    db.setHostName(host);
    db.setDatabaseName(database);
    db.setUserName(user);
    db.setPassword(password);
    db.setPort(port.toInt());
    qDebug() << db.lastError();
    bool ok = db.open();
    return ok;
}


void DatabaseSingleton::create_connection(QString host, QString user, QString password, QString port, QString database){
    qDebug() << db_params.isOpen();
    
    update_param("host", host);
    update_param("user", user);
    update_param("password", password);
    update_param("port", port);
    update_param("database", database);

    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS \"user\"(id serial NOT NULL, login varchar NOT NULL, passwordhash varchar NOT NULL, CONSTRAINT id_pkey PRIMARY KEY (id), CONSTRAINT login_unq UNIQUE (login));");
    qDebug() << query.lastError();

    query.exec("CREATE TABLE IF NOT EXISTS user_role(\"user\" integer NOT NULL, role varchar NOT NULL, CONSTRAINT user_role_pkey PRIMARY KEY (\"user\",role));");
    qDebug() << query.lastError();

    query.exec("ALTER TABLE user_role ADD CONSTRAINT user_fkey FOREIGN KEY (\"user\") REFERENCES \"user\" (id) MATCH FULL ON DELETE RESTRICT ON UPDATE NO ACTION;");
    qDebug() << query.lastError();

    query.exec("CREATE TABLE IF NOT EXISTS animal(id serial NOT NULL, name varchar NOT NULL, food varchar, CONSTRAINT animal_pkey PRIMARY KEY (id), CONSTRAINT name_unq UNIQUE (name));");
    qDebug() << query.lastError();
}

void DatabaseSingleton::add_param(QString name, QString value){
    QSqlQuery query(db_params);
    query.prepare("INSERT INTO params (name, value) VALUES (:name, :value);");
    query.bindValue(":name", name);
    query.bindValue(":value", value);
    query.exec();
    qDebug() << query.lastError();
}
void DatabaseSingleton::update_param(QString name, QString value){
    QSqlQuery query(db_params);
    query.prepare("UPDATE params SET value =:value WHERE name =:name;");
    query.bindValue(":name", name);
    query.bindValue(":value", value);
    query.exec();
    qDebug() << query.lastError();
}

QString DatabaseSingleton::get_param(QString name){
    QSqlQuery query(db_params);
    query.prepare("SELECT value FROM params WHERE name =:name;");
    query.bindValue(":name", name);
    query.exec();
    query.first();
    qDebug() << query.lastError();
    return query.value(0).toString();
}

int DatabaseSingleton::count_users(){
    QSqlQuery query(db);
    query.exec("SELECT count(*) AS exact_count FROM \"user\";");
    query.first();
    qDebug() << query.lastError();
    return query.value(0).toInt();
}


void DatabaseSingleton::add_user(QString username, QString password){
    QSqlQuery query(db);
    query.prepare("INSERT INTO \"user\" VALUES (DEFAULT, :user, :password);");
    query.bindValue(":user", username);
    query.bindValue(":password", password);
    query.exec();
    query.first();
    qDebug() << query.lastError();
}

bool DatabaseSingleton::login(QString username, QString password){
    QSqlQuery query;
    query.prepare("SELECT passwordhash = :password as \"CORRECT\" FROM \"user\" where login = :user;");
    query.bindValue(":user", username);
    query.bindValue(":password", password);
    query.exec();
    query.first();
    qDebug() << query.lastError();
    return query.value(0).toBool();
}

DatabaseSingleton::~DatabaseSingleton()
{
}
