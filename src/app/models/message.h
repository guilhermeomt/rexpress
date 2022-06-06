#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message
{
public:
    explicit Message();
    Message(QString id, QString content, QString createdAt, QString conversationId, QString createdBy)
        : m_id(id), m_content(content), m_createdAt(createdAt), m_conversationId(conversationId), m_createdBy(createdBy) {};
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getContent() const { return m_content; }
    void setContent(QString content) { m_content = content; }
    QString getCreatedAt() const { return m_createdAt; }
    void setCreatedAt(QString createdAt) { m_createdAt = createdAt; }
    QString getConversationId() const { return m_conversationId; }
    void setConversationId(QString conversationId) { m_conversationId = conversationId; }
    QString getCreatedBy() const { return m_createdBy; }
    void setCreatedBy(QString createdBy) { m_createdBy = createdBy; }

private:
    QString m_id;
    QString m_content;
    QString m_createdAt;
    QString m_conversationId;
    QString m_createdBy;
};

#endif // MESSAGE_H
