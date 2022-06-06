#include "invitationsrepository.h"

InvitationsRepository::InvitationsRepository(DBManager* dbmanager, QObject* parent) : QObject(parent), IRepository<Invitation,int>(dbmanager)
{
    m_dbmanager->open();
};

std::list<Invitation> InvitationsRepository::getAll() {
   return std::list<Invitation>();
}

Invitation* InvitationsRepository::getById(int id) {
    return nullptr;
}

Invitation* InvitationsRepository::getByIds(QString inviterId, QString inviteeId, QString projectId) {
    QSqlQuery query;

    query.prepare("SELECT * FROM invitations WHERE inviter_id = :inviterId AND invitee_id"
                  " = :inviteeId AND project_id = :projectId");
    query.bindValue(":inviterId", inviterId);
    query.bindValue(":inviteeId", inviteeId);
    query.bindValue(":projectId", projectId);
    query.exec();

    if(query.next()) {
        QString id = query.value(0).toString();
        QString status = query.value(3).toString();
        QString createdAt = query.value(4).toString();

        Invitation* invitation = new Invitation(id, inviterId, inviteeId, projectId, status, createdAt);
        return invitation;
    }
    return nullptr;
}


QVector<Invitation*>* InvitationsRepository::getByInviteeId(QString inviteeId) {
    QSqlQuery query;

    query.prepare("SELECT id, inviter_id, invitee_id, project_id, status, created_at FROM invitations"
                  " WHERE invitee_id = :inviteeId AND status LIKE \"pending\"");
    query.bindValue(":inviteeId", inviteeId);
    query.exec();

    QVector<Invitation*>* vector = new QVector<Invitation*>();
    while(query.next()) {
        QString id = query.value(0).toString();
        QString inviterId = query.value(1).toString();
        QString inviteeId = query.value(2).toString();
        QString projectId = query.value(3).toString();
        QString status = query.value(4).toString();
        QString createdAt = query.value(5).toString();

        Invitation* invitation = new Invitation(id, inviterId, inviteeId, projectId, status, createdAt);
        vector->push_front(invitation);
    }
    if(!vector->empty()) {
        return vector;
    }

    return nullptr;
}

Invitation* InvitationsRepository::create(Invitation entity) {
    QSqlQuery query;

    query.prepare("INSERT INTO invitations(inviter_id, invitee_id, project_id)"
                  " VALUES (:inviterId, :inviteeId, :projectId)");
    query.bindValue(":inviterId", entity.getInviterId());
    query.bindValue(":inviteeId", entity.getInviteeId());
    query.bindValue(":projectId", entity.getProjectId());
    auto ok = query.exec();

    if(!ok) {
        return nullptr;
    }

    return new Invitation(entity);
}

Invitation* InvitationsRepository::update(Invitation entity) {
    QSqlQuery query;

    qDebug() << entity.getId() << entity.getInviterId() << entity.getInviteeId()
             << entity.getProjectId() << entity.getStatus() << entity.getCreatedAt();
    query.prepare("UPDATE invitations SET inviter_id = :inviterId, invitee_id = :inviteeId"
                  " project_id = :projectId, status = :status, created_at = :createdAt"
                  " WHERE id = :id");
    query.bindValue(":inviterId", entity.getInviterId());
    query.bindValue(":inviteeId", entity.getInviteeId());
    query.bindValue(":projectId", entity.getProjectId());
    query.bindValue(":status", entity.getStatus());
    query.bindValue(":createdAt", entity.getCreatedAt());
    query.bindValue(":id", entity.getId());

    auto ok = query.exec();

    if(!ok) {
        return nullptr;
    }

    return new Invitation(entity);
}


bool InvitationsRepository::updateStatus(QString id, QString status) {
    QSqlQuery query;

    query.prepare("UPDATE invitations SET status = :status"
                  " WHERE id = :id");
    query.bindValue(":status", status);
    query.bindValue(":id", id);

    auto ok = query.exec();

    return ok;
}

Invitation* InvitationsRepository::remove(int id) {
   return nullptr;
}


