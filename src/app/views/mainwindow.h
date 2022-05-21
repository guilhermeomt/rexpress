#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QWidgetAction>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>

#include "DockManager.h"
#include "DockAreaWidget.h"
#include "DockWidget.h"

#include "openproject.h"
#include "invites.h"
#include "inviteuser.h"
#include "models/user.h"
#include "database/dbmanager.h"
#include "database/repositories/projectsrepository.h"

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

private:
    Ui::CMainWindow *ui;

    void main();
    void getPendingInvites();
    void createProject();
    void chooseProject();
    void openProject();

    DBManager* DBManager = nullptr;

    ads::CDockManager* DockManager;
    QLabel* m_mainToolbarTitle = nullptr;
    QFrame* m_menu = nullptr;

    QPushButton* m_menuButtonInviteUser;
    QPushButton * m_menuButtonInvites = nullptr;

    ads::CDockAreaWidget* m_TableDockWidgetArea = nullptr;
    ads::CDockAreaWidget* m_PropertiesDockWidgetArea = nullptr;

    OpenProject* m_openProject = nullptr;
    Invites* m_invites = nullptr;

    User* m_authUser;
    Project* m_openedProject = nullptr;

    QVector<Invitation*>* m_pendingInvitations = nullptr;

    ProjectsRepository* m_projectsRepository = nullptr;
    InvitationsRepository* m_invitationsRepository = nullptr;

};
#endif // MAINWINDOW_H
