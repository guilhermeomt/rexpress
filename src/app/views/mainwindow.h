#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QWidgetAction>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QMenu>

#include "DockManager.h"
#include "DockAreaWidget.h"
#include "DockWidget.h"

#include "openproject.h"
#include "invites.h"
#include "inviteuser.h"
#include "about.h"
#include "properties.h"
#include "models/user.h"
#include "database/dbmanager.h"
#include "database/repositories/projectsrepository.h"
#include "database/repositories/requirementsrepository.h"

#include "ui_properties.h"

#include "src/Animation/Animation.h"
#include "src/StackedWidgetAnimation/StackedWidgetAnimation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWindow; }
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    CMainWindow(User* authUser, QWidget *parent = nullptr);
    ~CMainWindow();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    IOC_INJECTABLE(UsersRepository, m_usersRepository);
    IOC_INJECTABLE(ProjectsRepository, m_projectsRepository);
    IOC_INJECTABLE(RequirementsRepository, m_requirementsRepository);
    IOC_INJECTABLE(InvitationsRepository, m_invitationsRepository);

    void itemPressed(QTreeWidgetItem *item, int index)
    {
        auto id = item->text(0);

        auto requirementRow = m_requirementsRepository->getByIdAndProjectId(id, m_openedProject->getId());

        QFont f1("Arial", 16, QFont::Bold);
        QFont f2("Arial", 12);

        QString definitionLabel = requirementRow->getRequirementLabel(id) + " - " + requirementRow->getDefinition();
        m_propertiesWidget->ui->lblDefinition->setFont(f1);
        m_propertiesWidget->ui->lblDefinition->setText(definitionLabel);

        m_propertiesWidget->ui->lblEspecification->setFont(f2);
        m_propertiesWidget->ui->lblEspecification->setText(requirementRow->getEspecification());
        m_propertiesWidget->ui->lblStatus->setText(requirementRow->getStatus());
        m_propertiesWidget->ui->lblType->setText(requirementRow->getType());
        m_propertiesWidget->ui->lblPriority->setText(requirementRow->getPriority());

        auto userRow = m_usersRepository->getById(requirementRow->getCreatedBy());

        QDateTime createdAtUtcDateTime = QDateTime::fromString(requirementRow->getCreatedAt(), Qt::ISODate);
        QDateTime createdAtLocalDateTime = createdAtUtcDateTime.addSecs(-3 * 3600); // 3 hours
        m_propertiesWidget->ui->lblCreatedAt->setText(createdAtLocalDateTime.toString("dd/MM/yyyy HH:mm:ss"));

        m_propertiesWidget->ui->lblCreatedBy->setText(userRow->getFullName());

        if(requirementRow->getUpdatedAt() != requirementRow->getCreatedAt()) {
            auto updatedAt = requirementRow->getUpdatedAt();
            QDateTime updatedAtUtcDateTime = QDateTime::fromString(updatedAt, Qt::ISODate);
            QDateTime updatedAtLocalDateTime = updatedAtUtcDateTime.addSecs(-3 * 3600); // 3 hours
            m_propertiesWidget->ui->lblUpdatedAt->setText(updatedAtLocalDateTime.toString("dd/MM/yyyy HH:mm:ss"));
        }  else {
            m_propertiesWidget->ui->lblUpdatedAt->setText(" - ");
        }

        if(requirementRow->getUpdatedBy() != "0") {
            auto userTwoRow = m_usersRepository->getById(requirementRow->getUpdatedBy());
            m_propertiesWidget->ui->lblUpdatedBy->setText(userTwoRow->getFullName());
        } else {
            m_propertiesWidget->ui->lblUpdatedBy->setText(" - ");
        }

        m_propertiesWidget->show();
    }

    void showTreeContextMenu(const QPoint &point) {
        QMenu menu(this);
        QModelIndex index = m_treeWidget->indexAt(point);
        menu.menuAction()->setIconVisibleInMenu(true);

        menu.addAction("Adicionar requisito", this, [&, this]{ createRequirementFromContextMenu(index); });
        menu.addAction("Editar requisito", this, [&, this]{ editRequirement(index); } );
        menu.addAction("Remover requisito", this, [&, this]{ removeRequirement(index); } );
        if (index.isValid()) {
            menu.exec(m_treeWidget->viewport()->mapToGlobal(point));
        }
    }

    void createRequirementFromContextMenu(QModelIndex index) {
        this->createRequirement(index);
    }

    void editRequirement(QModelIndex index) {
        qDebug() << index.row();
    }

    void removeRequirement(QModelIndex index) {
        auto item = m_treeWidget->itemFromIndex(index);

        if(item) {
        auto id = item->text(0);

        m_requirementsRepository->removeWithIdAndProjectId(id, m_openedProject->getId());

        m_treeWidget->takeTopLevelItem(index.row());
        }
    }

    void on_actionLogout_triggered() {
        this->logout();
    }

    void on_actionQuit_triggered() {
        this->quit();
    }

    void on_actionSettings_triggered() {

    }

    void on_actionCreateProject_triggered() {
        this->createProject();
    }

    void on_actionOpenProject_triggered() {
        this->chooseProject();
    }

    void on_actionInviteUser_triggered() {
        this->inviteUser();
    }

    void on_actionShowInvite_triggered() {
        this->showInvites();
    }

    void on_actionAddRequirementAction_triggered() {
        this->createRequirement();
    }

    void on_actionHelp_triggered() {

    }

    void on_actionAbout_triggered() {
        if (!m_about) m_about = new About();
        if (!m_about->isVisible()) m_about->show();
    }

private:
    Ui::CMainWindow *ui;

    void main();
    void getPendingInvites();
    void inviteUser();
    void showInvites();
    void createProject();
    void chooseProject();
    void openProject();
    void logout();
    void quit();
    int treeCount(QTreeWidgetItem *parent);
    void createRequirement(QModelIndex parentIndex = QModelIndex());
    void getRequirements();

    ads::CDockManager* DockManager;
    QLabel* m_mainToolbarTitle = nullptr;
    QFrame* m_menu = nullptr;
    QTreeWidget* m_treeWidget = nullptr;
    Properties* m_propertiesWidget = nullptr;

    QPushButton* m_menuButtonInviteUser = nullptr;
    QPushButton* m_menuButtonInvites = nullptr;
    QPushButton* m_menuButtonAddRequirement = nullptr;

    QAction* m_addRequirementAction = nullptr;
    QAction* m_inviteUserAction = nullptr;

    ads::CDockAreaWidget* m_TableDockWidgetArea = nullptr;
    ads::CDockAreaWidget* m_PropertiesDockWidgetArea = nullptr;

    OpenProject* m_openProject = nullptr;
    Invites* m_invites = nullptr;
    About* m_about = nullptr;

    User* m_authUser;
    Project* m_openedProject = nullptr;

    QVector<Invitation*>* m_pendingInvitations = nullptr;

    ProjectsRepository* m_projectsRepository = nullptr;
    RequirementsRepository* m_requirementsRepository = nullptr;
    UsersRepository* m_usersRepository = nullptr;
    InvitationsRepository* m_invitationsRepository = nullptr;
};
#endif // MAINWINDOW_H
