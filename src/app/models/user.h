#ifndef USER_H
#define USER_H

#include <QObject>


class User
{
public:
    explicit User();
    User(QString id, QString firstname, QString lastname, QString email)
        : m_id(id), m_firstname(firstname), m_lastname(lastname), m_email(email) {};
    User(QString id, QString firstname, QString lastname, QString email, QString password)
        : m_id(id), m_firstname(firstname), m_lastname(lastname), m_email(email), m_password(password) {};
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getFirstName() const { return m_firstname; }
    void setFirstName(QString firstname) { m_firstname = firstname; }
    QString getLastName() const { return m_lastname; }
    void setLastName(QString lastname) { m_lastname = lastname; }
    QString getFullName() const { return m_firstname + ' ' + m_lastname; }
    QString getEmail() const { return m_email ; }
    void setEmail(QString email) { m_email = email; }
    QString getPassword() const { return m_password ; }
    void setPassword(QString password) { m_password = password; }

private:
    QString m_id;
    QString m_firstname;
    QString m_lastname;
    QString m_email;
    QString m_password;

};

#endif // USER_H
