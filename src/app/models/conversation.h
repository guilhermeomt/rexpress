#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>

class Conversation
{
public:
    explicit Conversation();
    Conversation(QString id, QString createdAt, QString userOneId, QString userTwoId)
        : m_id(id), m_createdAt(createdAt), m_userOneId(userOneId), m_userTwoId(userTwoId) {};
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getCreatedAt() const { return m_createdAt; }
    void setCreatedAt(QString createdAt) { m_createdAt = createdAt; }
    QString getUserOneId() const { return m_userOneId; }
    void setUserOneId(QString userOneId) { m_userOneId = userOneId; }
    QString getUserTwoId() const { return m_userTwoId; }
    void setUserTwoId(QString userTwoId) { m_userTwoId = userTwoId; }
private:
    QString m_id;
    QString m_createdAt;
    QString m_userOneId;
    QString m_userTwoId;
};

#endif // CONVERSATION_H
