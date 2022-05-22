#include "inviteuser.h"
#include "ui_inviteuser.h"

InviteUser::InviteUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InviteUser)
{
    ui->setupUi(this);
}


InviteUser::InviteUser(User *authUser, Project *openedProject, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InviteUser),
    m_openedProject(openedProject),
    m_authUser(authUser)
{
    ui->setupUi(this);

    ui->btnBox->button(QDialogButtonBox::Ok)->setText("Enviar");
    ui->btnBox->button(QDialogButtonBox::Cancel)->setText("Cancelar");
}

InviteUser::~InviteUser()
{
    delete ui;
}

void InviteUser::on_btnBox_accepted()
{
    QString email = ui->leEmail->text();

    QMessageBox msgError;
    msgError.setIcon(QMessageBox::Critical);
    msgError.setWindowTitle("Erro!");
    if(email.length() == 0) {
        msgError.setText("Por favor, preencha o campo de email do usuário a ser convidado.");
        msgError.exec();
        return;
    }

    auto* user = m_usersRepository->getByEmail(email);

    if(!user) {
        msgError.setText("Não existe nenhum usuário com este email.");
        msgError.exec();
        return;
    }

    Invitation* alreadyInvited = m_invitationsRepository->getByIds(m_authUser->getId(),
                                                                   user->getId(), m_openedProject->getId());
    if(alreadyInvited) {
        msgError.setText("Você já convidou esse usuário para este projeto.");
        msgError.exec();
        return;
    }

    Invitation invitation(m_authUser->getId(), user->getId(), m_openedProject->getId());

    auto* invitationRow = m_invitationsRepository->create(invitation);

    if(invitationRow) {
        QMessageBox msgSuccess;
        msgSuccess.setIcon(QMessageBox::Information);
        msgSuccess.setWindowTitle("Convite enviado!");
        msgSuccess.setText("O convite foi enviado com sucesso");
        msgSuccess.exec();
    }
}


void InviteUser::on_btnBox_rejected()
{
    this->close();
}

