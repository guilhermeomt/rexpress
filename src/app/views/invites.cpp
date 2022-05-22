#include "invites.h"
#include "ui_invites.h"

Invites::Invites(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Invites)
{
    ui->setupUi(this);
}

Invites::Invites(User* authUser, QVector<Invitation*>* invitations, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Invites),
    m_authUser(authUser),
    m_invitations(invitations)
{
    ui->setupUi(this);

    ui->btnBox->button(QDialogButtonBox::Ok)->setText("Aceitar");
    ui->btnBox->button(QDialogButtonBox::Cancel)->setText("Recusar");

    if(m_invitations->empty()) {
        return;
    }

    for(int i = 0; i < m_invitations->length(); ++i) {
        auto invitation = m_invitations->at(i);

        auto user = m_usersRepository->getById(invitation->getInviterId());

        auto project = m_projectRepository->getById(invitation->getProjectId());

        QDateTime utcDateTime = QDateTime::fromString(invitation->getCreatedAt(), Qt::ISODate);
        QDateTime localDateTime = utcDateTime.addSecs(-3 * 3600); // 3 hours

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->tree);
        item->setText(0, user->getFullName());
        item->setText(1, project->getName());
        item->setText(2, localDateTime.toString("dd/MM/yyyy HH:mm:ss"));
        ui->tree->addTopLevelItem(item);
    }
}

Invites::~Invites()
{
    delete ui;
}

void Invites::on_btnBox_accepted()
{
    auto items = ui->tree->selectedItems();

    QMessageBox msg;
    if(items.empty()) {
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Erro!");
        msg.setText("Você deve selecionar algum convite.");
        msg.exec();
        return;
    }

    auto inviteItem = items.first();
    int index = ui->tree->indexFromItem(inviteItem).row();
    auto invitation = m_invitations->at(index);

    auto project = m_projectRepository->getById(invitation->getProjectId());

    m_projectRepository->addUserToProject(project->getId(), m_authUser->getId());

    invitation->setStatus("accepted");

    bool ok = m_invitationsRepository->updateStatus(invitation->getId(), invitation->getStatus());

    if(ok) {
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle("Convite aceito!");
        msg.setText("Agora você faz parte do projeto " + project->getName() + ".");
        msg.exec();
    }

    ui->tree->takeTopLevelItem(index);
    emit accept(index);
}


void Invites::on_btnBox_rejected()
{
    auto items = ui->tree->selectedItems();

    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setWindowTitle("Erro!");
    if(items.empty()) {
        msg.setText("Você deve selecionar algum convite.");
        msg.exec();
        return;
    }

    auto inviteItem = items.first();
    int index = ui->tree->indexFromItem(inviteItem).row();
    auto invitation = m_invitations->at(index);

    invitation->setStatus("rejected");

    bool ok = m_invitationsRepository->updateStatus(invitation->getId(), invitation->getStatus());

    if(!ok) {
        msg.setText("Ocorreu algum erro inesperado. Tente novamente mais tarde.");
        msg.exec();
    }

    ui->tree->takeTopLevelItem(index);
    emit reject(index);
}

