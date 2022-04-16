#include "usersrepository.h"

UsersRepository::UsersRepository(QSettings &config) : Repository<User,int>(config) {
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

User* UsersRepository::getById(int id) {
    return nullptr;
}

User* UsersRepository::getByEmailAndPassword(const char* email,const char* password) {

    QSqlQuery query;
    query.prepare("SELECT id, email, first_name, last_name FROM users "
                  "WHERE email LIKE :email AND password LIKE :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.exec();

    auto err = query.lastError();
    qDebug() << err;

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
   return nullptr;
}

User* UsersRepository::update(User entity) {
   return nullptr;
}

User* UsersRepository::remove(int id) {
   return nullptr;
}
