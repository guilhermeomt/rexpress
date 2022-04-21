#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>

class Project
{
public:
    explicit Project();
    Project(Project* project);
    Project(QString name, QString description)
        : m_name(name),
          m_description(description) {};
    Project(QString name, QString description, QString ownerId)
        : m_name(name),
          m_description(description),
          m_ownerId(ownerId) {};
    Project(QString id, QString name, QString description, QString ownerId, QString createdAt, QString updatedAt)
        : m_id(id),
          m_name(name),
          m_description(description),
          m_ownerId(ownerId),
          m_createdAt(createdAt),
          m_updatedAt(updatedAt) {};
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getName() const { return m_name; }
    void setName(QString name) { m_name = name; }
    QString getDescription() const { return m_description; }
    void setDescription(QString description) { m_description = description; }
    QString getOwnerId() const { return m_ownerId; }
    void setOwnerId(QString ownerId) { m_ownerId = ownerId; }
    QString getCreatedAt() const { return m_createdAt; }
    void setCreatedAt(QString createdAt) { m_createdAt = createdAt; }
    QString getUpdatedAt() const { return m_updatedAt; }
    void setUpdatedAt(QString updatedAt) { m_updatedAt = updatedAt; }
private:
    QString m_id;
    QString m_name;
    QString m_description;
    QString m_ownerId;
    QString m_createdAt;
    QString m_updatedAt;
};

#endif // PROJECT_H
