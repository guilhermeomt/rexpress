#ifndef INVITATION_H
#define INVITATION_H

#include <QObject>

class Invitation
{
public:
    explicit Invitation();
    Invitation(Invitation* i);
    Invitation(QString inviterId, QString inviteeId, QString projectId) :
        m_inviterId(inviterId),
        m_inviteeId(inviteeId),
        m_projectId(projectId) {}
    Invitation(QString id, QString inviterId, QString inviteeId, QString projectId,
               QString status, QString createdAt) :
        m_id(id),
        m_inviterId(inviterId),
        m_inviteeId(inviteeId),
        m_projectId(projectId),
        m_status(status),
        m_createdAt(createdAt) {}
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getInviterId() const { return m_inviterId; }
    void setInviterId(QString inviterId) { m_inviterId = inviterId; }
    QString getInviteeId() const { return m_inviteeId; }
    void setInviteeId(QString inviteeId) { m_inviteeId = inviteeId; }
    QString getProjectId() const { return m_projectId; }
    void setProjectId(QString projectId) { m_projectId = projectId; }
    QString getStatus() const { return m_status; }
    void setStatus(QString status) { m_status = status; }
    QString getCreatedAt() const { return m_createdAt; }
    void setCreatedAt(QString createdAt) { m_createdAt = createdAt; }

private:
    QString m_id;
    QString m_inviterId;
    QString m_inviteeId;
    QString m_projectId;
    QString m_status;
    QString m_createdAt;
};

#endif // INVITATION_H
