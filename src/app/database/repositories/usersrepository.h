#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "irepository.h"
#include "models/user.h"

class UsersRepository final : public QObject, public IRepository<User, QString>
{
    Q_OBJECT
public:
    UsersRepository(DBManager* dbmanager, QObject* parent = nullptr);
    ~UsersRepository() override { delete m_dbmanager; }

    std::list<User> getAll() override;
    User* getById(QString id) override;
    User* getByEmailAndPassword(QString email, QString password);
    User* getByEmail(QString email);
    User* create(User entity) override;
    User* update(User entity) override;
    User* remove(QString id) override;
};

#endif // USERSREPOSITORY_H
