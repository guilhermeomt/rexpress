#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getFirstName() const { return m_firstname; }
    void setFirstName(QString firstname) { m_firstname = firstname; }
    QString getLastName() const { return m_lastname; }
    void setLastName(QString lastname) { m_lastname = lastname; }
    QString getFullName() const { return m_firstname + ' ' + m_lastname; }


signals:


private:
    QString m_id;
    QString m_firstname;
    QString m_lastname;
    QString m_email;

};

#endif // USER_H
