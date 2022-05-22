#ifndef INVITATIONSREPOSITORY_H
#define INVITATIONSREPOSITORY_H

#include "irepository.h"
#include "models/invitation.h"

class InvitationsRepository final : public QObject, public IRepository<Invitation, int>
{
public:
    InvitationsRepository(DBManager* dbmanager, QObject* parent = nullptr);
    ~InvitationsRepository() {};

    std::list<Invitation> getAll() override;
    Invitation* getById(int id) override;
    Invitation* getByIds(QString inviterId, QString inviteeId, QString projectId);
    QVector<Invitation*>* getByInviteeId(QString inviteeId);
    Invitation* create(Invitation entity) override;
    Invitation* update(Invitation entity) override;
    bool updateStatus(QString id, QString status);
    Invitation* remove(int id) override;
};

#endif // INVITATIONSREPOSITORY_H
