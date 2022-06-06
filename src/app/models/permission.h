#ifndef PERMISSION_H
#define PERMISSION_H

#include <QObject>

class Permission
{
public:
    explicit Permission();
    Permission(QString id, QString title, QString description)
        : m_id(id), m_title(title), m_description(description) {};
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getTitle() const { return m_title; }
    void setTitle(QString title) { m_title = title; }
    QString getDescription() const { return m_description; }
    void setDescription(QString description) { m_description = description; }
private:
    QString m_id;
    QString m_title;
    QString m_description;
};

#endif // PERMISSION_H
