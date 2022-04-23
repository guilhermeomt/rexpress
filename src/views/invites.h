#ifndef INVITES_H
#define INVITES_H

#include <QWidget>
#include <QPushButton>
#include <QDateTime>
#include <QTimeZone>
#include <QMessageBox>

#include "database/repositories/invitationsrepository.h"
#include "database/repositories/usersrepository.h"
#include "database/repositories/projectsrepository.h"

namespace Ui {
class Invites;
}

class Invites : public QWidget
{
    Q_OBJECT

public:
    explicit Invites(QWidget *parent = nullptr);
    Invites(User* m_authUser, QVector<Invitation*>* invitations, QWidget *parent);
    ~Invites();

private slots:
    void on_btnBox_accepted();

    void on_btnBox_rejected();

signals:
    void accept(int removedInvitationIndex);
    void reject(int removedInvitationIndex);

private:
    Ui::Invites *ui;
    User* m_authUser = nullptr;
    QVector<Invitation*>* m_invitations = nullptr;

    InvitationsRepository* m_invitationsRepository = nullptr;
    UsersRepository* m_usersRepository = nullptr;
    ProjectsRepository* m_projectRepository = nullptr;

};

#endif // INVITES_H
