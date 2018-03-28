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
    if(ok)create_db();
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
    if(ok)create_db();
    return ok;
}


void DatabaseSingleton::create_connection(QString host, QString user, QString password, QString port, QString database){
    qDebug() << db_params.isOpen();
    
    update_param("host", host);
    update_param("user", user);
    update_param("password", password);
    update_param("port", port);
    update_param("database", database);

    create_db();
}

void DatabaseSingleton::create_db(){
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS \"user\"(id serial NOT NULL, login varchar NOT NULL, passwordhash varchar NOT NULL, CONSTRAINT id_pkey PRIMARY KEY (id), CONSTRAINT login_unq UNIQUE (login));");
    qDebug() << query.lastError();

    query.exec("CREATE TABLE IF NOT EXISTS user_role(\"user\" integer NOT NULL, role varchar NOT NULL, CONSTRAINT user_role_pkey PRIMARY KEY (\"user\",role));");
    qDebug() << query.lastError();

    query.exec("ALTER TABLE user_role ADD CONSTRAINT user_fkey FOREIGN KEY (\"user\") REFERENCES \"user\" (id) MATCH FULL ON DELETE CASCADE ON UPDATE NO ACTION;");
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

    User u = get_user(username);
    add_permission(u.id, "READ");
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

std::vector<User> DatabaseSingleton::get_users(){
    QSqlQuery query(db);
    std::vector<User> result;
    query.exec("SELECT * FROM \"user\";");
    while(query.next()){
        User tmp;
        tmp.id = query.value("id").toInt();
        tmp.name = query.value("login").toString();
        result.push_back(tmp);
    }
    qDebug() << query.lastError();
    return result;
}

std::vector<Animal> DatabaseSingleton::get_animals(){
    std::vector<Animal> result;
    QSqlQuery query(db);
    query.exec("SELECT * FROM animal;");
    while(query.next()){
        Animal tmp;
        tmp.name = query.value("name").toString();
        tmp.food = query.value("food").toString();
        tmp.id = query.value("id").toInt();
        result.push_back(tmp);
    }
    return result;
}

Animal DatabaseSingleton::get_animal(int id){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM animal WHERE id =:id;");
    query.bindValue(":id", id);
    query.exec();
    query.first();

    Animal result;
    result.name = query.value("name").toString();
    result.food = query.value("food").toString();
    result.id = query.value("id").toInt();
    return result;
}


void DatabaseSingleton::add_animal(QString name, QString food){
    QSqlQuery query(db);
    query.prepare("INSERT INTO animal VALUES (DEFAULT, :name, :food);");
    query.bindValue(":name", name);
    query.bindValue(":food", food);
    query.exec();
    qDebug() << query.lastError();
}

void DatabaseSingleton::update_animal(int id, QString name, QString food){
    QSqlQuery query(db);
    query.prepare("UPDATE animal SET food=:food, name=:name WHERE id =:id;");
    query.bindValue(":name", name);
    query.bindValue(":food", food);
    query.bindValue(":id", id);
    query.exec();
    qDebug() << query.lastError();
}


void DatabaseSingleton::delete_animal(int id){
    QSqlQuery query(db);
    query.prepare("DELETE FROM animal WHERE id =:id;");
    query.bindValue(":id", id);
    query.exec();
    qDebug() << query.lastError();
}

void DatabaseSingleton::set_permission(int id, Permission permission){
    if(permission.admin)
        add_permission(id, "ADMIN");
    else
        delete_permission(id, "ADMIN");

    if(permission.read)
        add_permission(id, "READ");
    else
        delete_permission(id, "READ");

    if(permission.del)
        add_permission(id, "DELETE");
    else
        delete_permission(id, "DELTE");

    if(permission.write)
        add_permission(id, "WRITE");
    else
        delete_permission(id, "WRITE");

    if(permission.update)
        add_permission(id, "UPDATE");
    else
        delete_permission(id, "UPDATE");

}

void DatabaseSingleton::add_permission(int id, QString perm){
    QSqlQuery query(db);
    query.prepare("INSERT INTO \"user_role\" VALUES (:id, :perm);");
    query.bindValue(":id", id);
    query.bindValue(":perm", perm);
    query.exec();
    qDebug() << query.lastError();
}

void DatabaseSingleton::delete_permission(int id, QString perm){
    QSqlQuery query(db);
    query.prepare("DELETE FROM \"user_role\" WHERE \"user\" =:id AND role =:role;");
    query.bindValue(":id", id);
    query.bindValue(":role", perm.toUpper());
    query.exec();
    qDebug() << query.lastError();
}

Permission DatabaseSingleton::get_permission(int id){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM \"user_role\" WHERE \"user\" =:id;");
    query.bindValue(":id", id);
    query.exec();

    Permission result;
    while(query.next()){
        if(query.value("role").toString() == "ADMIN")
            result.admin = true;
        if(query.value("role").toString() == "WRITE")
            result.write = true;
        if(query.value("role").toString() == "READ")
            result.read = true;
        if(query.value("role").toString() == "UPDATE")
            result.update = true;
        if(query.value("role").toString() == "DELETE")
            result.del = true;
    }
    return result;
}

User DatabaseSingleton::get_user(QString username){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM \"user\" WHERE login =:login;");
    query.bindValue(":login", username);
    query.exec();
    qDebug() << query.lastError();
    User result;
    query.first();
    result.id = query.value("id").toInt();
    result.name = query.value("name").toString();
    return result;
}

void DatabaseSingleton::update_user(int id, QString login){
    QSqlQuery query(db);
    query.prepare("UPDATE \"user\" SET login=:login WHERE id =:id;");
    query.bindValue(":id", id);
    query.bindValue(":login", login);
    query.exec();
    qDebug() << query.lastError();
}

void DatabaseSingleton::delete_user(int id){
    QSqlQuery query(db);
    query.prepare("DELETE FROM \"user\" WHERE id =:id;");
    query.bindValue(":id", id);
    query.exec();
    qDebug() << query.lastError();


}

DatabaseSingleton::~DatabaseSingleton()
{
}
