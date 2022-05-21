#ifndef INVITEUSER_H
#define INVITEUSER_H

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>

#include "models/project.h"
#include "database/repositories/invitationsrepository.h"
#include "database/repositories/usersrepository.h"
namespace Ui {
class InviteUser;
}

class InviteUser : public QDialog
{
    Q_OBJECT

public:
    explicit InviteUser(QWidget *parent = nullptr);
    InviteUser(User *authUser, Project *openedProject, QWidget *parent = nullptr);
    ~InviteUser();

private slots:
    void on_btnBox_accepted();

    void on_btnBox_rejected();

private:
    Ui::InviteUser *ui;
    Project* m_openedProject = nullptr;
    User* m_authUser = nullptr;

    InvitationsRepository* m_invitationsRepository = nullptr;
    UsersRepository* m_usersRepository = nullptr;
};

#endif // INVITEUSER_H
