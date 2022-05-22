#include "usersrepository.h"

UsersRepository::UsersRepository(DBManager* dbmanager, QObject* parent) : QObject(parent), IRepository<User,QString>(dbmanager)
{
    m_dbmanager->open();
};

std::list<User> UsersRepository::getAll() {
    QSqlQuery query("SELECT id, email, first_name, last_name FROM users");

    std::list<User> list;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString email = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();

        User user(id, firstname, lastname, email);
        list.push_front(user);
    }
    return list;
}

User* UsersRepository::getById(QString id) {
    QSqlQuery query;

    query.prepare("SELECT id, email, first_name, last_name FROM users WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if(query.next())
    {
        QString id = query.value(0).toString();
        QString email = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();

        return new User(id, firstname, lastname, email);
    }
    return nullptr;
}

User* UsersRepository::getByEmailAndPassword(QString email, QString password) {
    QSqlQuery query;
    query.prepare("SELECT id, email, first_name, last_name FROM users "
                  "WHERE email LIKE :email AND password LIKE :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.exec();

    if(query.first()) {
        QString id = query.value(0).toString();
        QString email = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();

        User* user = new User(id, firstname, lastname, email);
        return user;
    } else {
        return nullptr;
    }
}

User* UsersRepository::getByEmail(QString email) {

    QSqlQuery query;
    query.prepare("SELECT id, email, first_name, last_name FROM users "
                  "WHERE email LIKE :email");
    query.bindValue(":email", email);
    query.exec();

    if(query.first()) {
        QString id = query.value(0).toString();
        QString email = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();

        User* user = new User(id, firstname, lastname, email);
        return user;
    } else {
        return nullptr;
    }
}

User* UsersRepository::create(User entity) {
    QSqlQuery query;

    query.prepare("INSERT INTO users(first_name, last_name, email, password)"
                  " VALUES (:firstname, :lastname, :email, :password)");
    query.bindValue(":firstname", entity.getFirstName());
    query.bindValue(":lastname", entity.getLastName());
    query.bindValue(":email", entity.getEmail());
    query.bindValue(":password", entity.getPassword());
    auto ok = query.exec();

    if(ok) {
        return new User(entity);
    } else {
        return nullptr;
    }
}

User* UsersRepository::update(User entity) {
    return nullptr;
}

User* UsersRepository::remove(QString id) {
    return nullptr;
}
