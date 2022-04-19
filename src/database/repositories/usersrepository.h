#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "repository.h"
#include "models/user.h"

class UsersRepository final : public Repository<User, int>
{
public:
    UsersRepository() : Repository<User, int>() {};
    UsersRepository(QSettings &config);
    ~UsersRepository() { delete m_dbmanager; };

    std::list<User> getAll() override;
    User* getById(int id) override;
    User* getByEmailAndPassword(QString email, QString password);
    User* getByEmail(QString email);
    User* create(User entity) override;
    User* update(User entity) override;
    User* remove(int id) override;
};

#endif // USERSREPOSITORY_H
