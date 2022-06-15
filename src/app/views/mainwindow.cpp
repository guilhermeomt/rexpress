#include "views/login.h"
#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "ui_form.h"

#include <QWidgetAction>
#include <QTreeView>
#include <QTimer>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QToolBar>
#include <QToolButton>
#include <QHeaderView>

#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "properties.h"

using namespace ads;

CMainWindow::CMainWindow( QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
    m_authUser = new User();
    this->main();
}

CMainWindow::CMainWindow(User* authUser, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::CMainWindow),
      m_authUser(authUser)
{
    this->main();
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::main() {
    ui->setupUi(this);
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    DockManager = new CDockManager(this);
    setWindowTitle(tr("Rexpress"));
    this->showMaximized();

    QWidget w;

    getPendingInvites();

    QTreeWidget* treeWidget = new QTreeWidget();
    m_treeWidget = treeWidget;
    QStringList labels;
    labels << "ID" << "Definição " << "Tipo "<< "Prioridade" << "Status";
    treeWidget->setHeaderLabels(labels);
    treeWidget->header()->resizeSection(1, 250);
    CDockWidget* TableDockWidget = new CDockWidget("Requisitos");
    TableDockWidget->setIcon(QIcon(":/icons/svg/file.svg"));
    TableDockWidget->setWidget(treeWidget);
    auto* TableDockWidgetArea = DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TableDockWidget);
    m_TableDockWidgetArea = TableDockWidgetArea;
    ui->menuView->addAction(TableDockWidget->toggleViewAction());
    TableDockWidgetArea->setDisabled(true);

    Properties* propertiesWidget = new Properties();
    m_propertiesWidget = propertiesWidget;
    CDockWidget* PropertiesDockWidget = new CDockWidget("Propriedades");
    PropertiesDockWidget->setIcon(QIcon(":/icons/svg/view_details.svg"));
    PropertiesDockWidget->setWidget(propertiesWidget);
    auto* PropertiesDockWidgetArea = DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget);
    m_PropertiesDockWidgetArea = PropertiesDockWidgetArea;
    ui->menuView->addAction(PropertiesDockWidget->toggleViewAction());

    QAction* settingsAction = new QAction(QIcon(":icons/svg/settings.svg"), "Configurações", ui->menuRexpress);
    connect(settingsAction, &QAction::triggered, this, &CMainWindow::on_actionSettings_triggered);
    QAction* logoutAction = new QAction(QIcon(":icons/svg/logout.svg"), "Logout", ui->menuRexpress);
    connect(logoutAction, &QAction::triggered, this, &CMainWindow::on_actionLogout_triggered);
    QAction* quitAction = new QAction(QIcon(":icons/svg/up_left.svg"), "Sair", ui->menuRexpress);
    connect(quitAction, &QAction::triggered, this, &CMainWindow::on_actionQuit_triggered);
    ui->menuRexpress->addAction(settingsAction);
    ui->menuRexpress->addSeparator();
    ui->menuRexpress->addAction(logoutAction);
    ui->menuRexpress->addAction(quitAction);

    QAction* createProjectAction = new QAction(QIcon(":icons/svg/add_folder.svg"), "Criar novo projeto", ui->menuActions);
    connect(createProjectAction, &QAction::triggered, this, &CMainWindow::on_actionCreateProject_triggered);
    QAction* openProjectAction = new QAction(QIcon(":icons/svg/opened_folder.svg"), "Abrir projeto", ui->menuActions);
    connect(openProjectAction, &QAction::triggered, this, &CMainWindow::on_actionOpenProject_triggered);
    QAction* inviteUserAction = new QAction(QIcon(":icons/svg/user_folder.svg"), "Convidar usuário ao projeto", ui->menuActions);
    m_inviteUserAction = inviteUserAction;
    inviteUserAction->setDisabled(true);
    connect(inviteUserAction, &QAction::triggered, this, &CMainWindow::on_actionInviteUser_triggered);
    QAction* showInvitesAction = new QAction(QIcon(":icons/svg/invite.svg"), "Convites", ui->menuActions);
    connect(showInvitesAction, &QAction::triggered, this, &CMainWindow::on_actionShowInvite_triggered);
    QAction* addRequirementAction = new QAction(QIcon(":icons/svg/plus.svg"), "Adicionar novo requisito", ui->menuActions);
    m_addRequirementAction = addRequirementAction;
    addRequirementAction->setDisabled(true);
    connect(addRequirementAction, &QAction::triggered, this, &CMainWindow::on_actionAddRequirementAction_triggered);
    QAction* showConversationsAction = new QAction(QIcon(":icons/svg/sms.svg"), "Conversas", ui->menuActions);
    ui->menuActions->addAction(createProjectAction);
    ui->menuActions->addAction(openProjectAction);
    ui->menuActions->addAction(inviteUserAction);
    ui->menuActions->addAction(showInvitesAction);
    ui->menuActions->addSeparator();
    ui->menuActions->addAction(addRequirementAction);
    ui->menuActions->addSeparator();
    ui->menuActions->addAction(showConversationsAction);

    QAction* helpAction = new QAction(QIcon(":icons/svg/info.svg"), "Conteúdo", ui->menuHelp);
    connect(helpAction, &QAction::triggered, this, &CMainWindow::on_actionHelp_triggered);
    QAction* aboutAction = new QAction(QIcon(":icons/svg/about.svg"), "Sobre", ui->menuHelp);
    connect(aboutAction, &QAction::triggered, this, &CMainWindow::on_actionAbout_triggered);
    ui->menuHelp->addAction(helpAction);
    ui->menuHelp->addAction(aboutAction);

    propertiesWidget->hide();
    PropertiesDockWidgetArea->setDisabled(true);

    QFrame* mainToolbar = new QFrame(&w);
    mainToolbar->setProperty("toolbar", true);
    mainToolbar->setFrameShape(QFrame::StyledPanel);
    QToolButton* mainToolbarMenuButton = new QToolButton(mainToolbar);
    mainToolbarMenuButton->setIcon(QIcon(":/icons/svg/menu.svg"));
    QLabel* mainToolbarTitle = new QLabel(mainToolbar);
    m_mainToolbarTitle = mainToolbarTitle;
    QHBoxLayout* mainToolbarLayout = new QHBoxLayout(mainToolbar);
    mainToolbarLayout->setContentsMargins(QMargins());
    mainToolbarLayout->setSpacing(10);
    mainToolbarLayout->addWidget(mainToolbarMenuButton);
    mainToolbarLayout->addWidget(mainToolbarTitle);
    CDockWidget* HeaderDockWidget = new CDockWidget("Cabeçalho");
    HeaderDockWidget->setWidget(mainToolbar);
    auto* HeaderDockArea = DockManager->addDockWidget(DockWidgetArea::OuterDockAreas, HeaderDockWidget);
    HeaderDockArea->setDockAreaFlag(CDockAreaWidget::eDockAreaFlag::HideSingleWidgetTitleBar, true);
    HeaderDockArea->setMaximumHeight(50);

    QFrame* menu = new QFrame(this);
    m_menu = menu;
    menu->setProperty("menu", true);
    menu->setFixedWidth(300);
    QFrame* menuToolbar = new QFrame(menu);
    menuToolbar->setStyleSheet(tr("border: 1px solid transparent;"));
    menuToolbar->setFrameShape(QFrame::StyledPanel);
    QLabel* menuToolbarLoggedIn = new QLabel(menuToolbar);
    menuToolbarLoggedIn->setFixedWidth(40);
    menuToolbarLoggedIn->setFixedHeight(40);
    menuToolbarLoggedIn->setScaledContents(true);
    menuToolbarLoggedIn->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QPixmap userIcon(":/icons/svg/account.svg");
    menuToolbarLoggedIn->setPixmap(userIcon.scaled(menuToolbarLoggedIn->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* menuToolbarTitle = new QLabel("<b>Logado como " + m_authUser->getFirstName(), menuToolbar);
    menuToolbarTitle->setStyleSheet(tr("color: #a1a1a1;"));
    QHBoxLayout* menuToolbarLayout = new QHBoxLayout(menuToolbar);
    menuToolbarLayout->setContentsMargins(2,2,2,10);
    menuToolbarLayout->setSpacing(15);
    menuToolbarLayout->addWidget(menuToolbarLoggedIn);
    menuToolbarLayout->addWidget(menuToolbarTitle);
    QPushButton* menuButtonLogout = new QPushButton(QIcon(":/icons/svg/logout.svg"), "Logout", menu);
    menuButtonLogout->setProperty("menu", true);
    QPushButton* menuButtonNewProject = new QPushButton(QIcon(":/icons/svg/add_folder.svg"), "Criar novo projeto", menu);
    QPushButton* menuButtonOpenProject = new QPushButton(QIcon(":/icons/svg/opened_folder.svg"), "Abrir projeto", menu);
    menuButtonOpenProject->setProperty("menu", true);
    QPushButton* menuButtonInviteUser = new QPushButton(QIcon(":/icons/svg/user_folder.svg"), "Convidar usuário ao projeto", menu);
    m_menuButtonInviteUser = menuButtonInviteUser;
    menuButtonInviteUser->setProperty("menu", true);
    menuButtonInviteUser->setDisabled(true);
    QPushButton* menuButtonAddRequirement = new QPushButton(QIcon(":/icons/svg/plus.svg"), "Adicionar novo requisito", menu);
    m_menuButtonAddRequirement = menuButtonAddRequirement;
    menuButtonAddRequirement->setProperty("menu", true);
    menuButtonAddRequirement->setDisabled(true);
    QPushButton* menuButtonInvites = new QPushButton(QIcon(":/icons/svg/invite.svg"), "Convites", menu);
    m_menuButtonInvites = menuButtonInvites;
    menuButtonInvites->setProperty("menu", true);
    QPushButton* menuButtonConversations = new QPushButton(QIcon(":/icons/svg/sms.svg"), "Conversas", menu);
    menuButtonConversations->setProperty("menu", true);
    if(!m_pendingInvitations->empty()) {
        auto length = std::to_string(m_pendingInvitations->length());
        menuButtonInvites->setText(tr("Convites ") + tr("(") + tr(length.c_str())  + tr(")"));
    }
    QPushButton* menuButtonExit = new QPushButton(QIcon(":/icons/svg/up_left.svg"), "Sair", menu);
    menuButtonExit->setProperty("menu", true);
    QVBoxLayout* menuLayout = new QVBoxLayout(menu);
    menuLayout->setSpacing(3);
    menuLayout->addWidget(menuToolbar);
    menuLayout->addWidget(menuButtonNewProject);
    menuLayout->addWidget(menuButtonOpenProject);
    menuLayout->addWidget(menuButtonAddRequirement);
    menuLayout->addWidget(menuButtonInviteUser);
    menuLayout->addWidget(menuButtonInvites);
    menuLayout->addWidget(menuButtonConversations);
    menuLayout->addWidget(menuButtonLogout);
    menuLayout->addWidget(menuButtonExit);
    menuLayout->addStretch();
    WAF::Animation::sideSlideIn(menu, WAF::LeftSide);

    connect(menuButtonLogout, &QPushButton::clicked, [=] {
        this->logout();
    });

    connect(menuButtonExit, &QPushButton::clicked, [=] {
        this->quit();
    });

    connect(mainToolbarMenuButton, &QToolButton::clicked, [=] {
        WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
    });

    connect(menuButtonNewProject, &QPushButton::clicked, [this] {
        this->createProject();
    });

    connect(menuButtonAddRequirement, &QPushButton::clicked, [this] {
        this->createRequirement();
    });

    connect(menuButtonInviteUser, &QPushButton::clicked, [this] {
        this->inviteUser();
    });

    connect(menuButtonInvites, &QPushButton::clicked, [this] {
        this->showInvites();
    });

    connect(mainToolbarMenuButton, &QToolButton::clicked, [=] {
        WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
    });

    connect(menuButtonOpenProject, &QPushButton::clicked, [this] { chooseProject(); } );

    connect(m_treeWidget, &QTreeWidget::itemClicked, this, &CMainWindow::itemPressed);

    m_treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_treeWidget, &QTreeWidget::customContextMenuRequested, this, &CMainWindow::showTreeContextMenu);
}

void CMainWindow::getPendingInvites() {
    m_pendingInvitations = m_invitationsRepository->getByInviteeId(m_authUser->getId());

    if(!m_pendingInvitations) {
        m_pendingInvitations = new QVector<Invitation*>();
    }
}

void CMainWindow::inviteUser() {
    InviteUser* inviteUser = new InviteUser(m_authUser, m_openedProject, this);
    inviteUser->show();
}

void CMainWindow::showInvites() {
    Invites* m_invites = new Invites(m_authUser, m_pendingInvitations, this);
    WAF::Animation::sideSlideIn(m_invites, WAF::TopSide);

    connect(m_invites, &Invites::accept, [&, this](int removedInvitationIndex) {
        m_pendingInvitations->removeAt(removedInvitationIndex);
        if(!m_pendingInvitations->empty()) {
            auto length = std::to_string(m_pendingInvitations->length());
            m_menuButtonInvites->setText(tr("Convites ") + tr("(") + tr(length.c_str())  + tr(")"));
        } else {
            m_menuButtonInvites->setText(tr("Convites"));
        }
    });

    connect(m_invites, &Invites::reject, [&, this](int removedInvitationIndex) {
        m_pendingInvitations->removeAt(removedInvitationIndex);
        if(!m_pendingInvitations->empty()) {
            auto length = std::to_string(m_pendingInvitations->length());
            m_menuButtonInvites->setText(tr("Convites ") + tr("(") + tr(length.c_str())  + tr(")"));
        } else {
            m_menuButtonInvites->setText(tr("Convites"));
        }
    });
}

void CMainWindow::createProject() {
    QFrame* newProjectMenu = new QFrame(this);
    newProjectMenu->setProperty("menu", true);
    QFrame* newProjectMenuHeader = new QFrame(newProjectMenu);
    newProjectMenuHeader->setStyleSheet("background-color: rgb(68,68,68);");
    QLabel* menuHeaderTitle = new QLabel("Criar novo projeto", newProjectMenuHeader);
    menuHeaderTitle->setAlignment(Qt::AlignHCenter);
    menuHeaderTitle->setStyleSheet(tr("font-size: 28px;"));
    QHBoxLayout* menuHeaderLayout = new QHBoxLayout(newProjectMenuHeader);
    menuHeaderLayout->setContentsMargins(2,14,2,14);
    menuHeaderLayout->setSpacing(5);
    menuHeaderLayout->addWidget(menuHeaderTitle);
    QFrame* newProjectForm = new QFrame(newProjectMenu);
    QLineEdit* leName = new QLineEdit(newProjectForm);
    leName->setPlaceholderText(tr("Nome do projeto "));
    leName->setFixedWidth(350);
    QTextEdit* qeDescription = new QTextEdit(newProjectForm);
    qeDescription->setPlaceholderText("Descrição");
    qeDescription->setFixedWidth(350);
    qeDescription->setFixedHeight(100);
    QLabel* lblAuthor = new QLabel(newProjectForm);
    lblAuthor->setText(tr("<b>Autor: </b>") + m_authUser->getFullName());
    QDialogButtonBox* btnBox = new QDialogButtonBox(newProjectForm);
    btnBox->addButton("Confirmar", QDialogButtonBox::AcceptRole);
    btnBox->addButton("Cancelar", QDialogButtonBox::RejectRole);
    btnBox->setFixedWidth(350);
    QVBoxLayout* newProjectFormLayout = new QVBoxLayout(newProjectForm);
    newProjectFormLayout->setAlignment(Qt::AlignHCenter);
    newProjectFormLayout->addWidget(leName);
    newProjectFormLayout->addWidget(qeDescription);
    newProjectFormLayout->addWidget(lblAuthor);
    newProjectFormLayout->addWidget(btnBox);
    QVBoxLayout* newProjectMenuLayout = new QVBoxLayout(newProjectMenu);
    newProjectMenuLayout->setContentsMargins(0,0,0,10);
    newProjectMenuLayout->setSpacing(0);
    newProjectMenuLayout->addWidget(newProjectMenuHeader);
    newProjectMenuLayout->addWidget(newProjectForm);
    newProjectMenuLayout->addStretch();

    WAF::Animation::sideSlideIn(newProjectMenu, WAF::TopSide);

    connect(btnBox, &QDialogButtonBox::accepted, [=] {
        QString name = leName->text();
        QString description = qeDescription->toPlainText();

        QMessageBox msgError;
        msgError.setIcon(QMessageBox::Critical);
        msgError.setWindowTitle("Erro!");
        if(name.length() == 0 || description.length() == 0) {
            msgError.setText("Preencha todos os campos, por favor.");
            msgError.exec();
            return;
        }

        Project project(name, description, m_authUser->getId());
        auto* projectRow = m_projectsRepository->create(project);

        if(projectRow) {
            m_openedProject = projectRow;
            WAF::Animation::sideSlideOut(newProjectMenu, WAF::TopSide);
            WAF::Animation::sideSlideOut(m_menu, WAF::LeftSide);
            this->openProject();
        } else {
            msgError.setText("Ocorreu algum erro inesperado. Tente novamente mais tarde.");
            msgError.exec();
        }
    });

    connect(btnBox, &QDialogButtonBox::rejected, [=] {
        WAF::Animation::sideSlideOut(newProjectMenu, WAF::TopSide);
    });
}

void CMainWindow::chooseProject() {
    if (!m_openProject) m_openProject = new OpenProject(m_authUser, this);
    if (!m_openProject->isVisible()) m_openProject->show();

    connect(m_openProject, &OpenProject::accept, [this](Project* project) {
        WAF::Animation::sideSlideOut(m_menu, WAF::LeftSide);
        m_openedProject = project;
        this->openProject();
    });
}

void CMainWindow::openProject() {
    m_mainToolbarTitle->setText("<b>" + m_openedProject->getName() + "</b>");
    m_TableDockWidgetArea->setDisabled(false);
    m_PropertiesDockWidgetArea->setDisabled(false);
    this->setWindowTitle("[" + m_openedProject->getName() + "]" + " - Rexpress");
    m_menuButtonInviteUser->setDisabled(false);
    m_menuButtonAddRequirement->setDisabled(false);
    m_inviteUserAction->setDisabled(false);
    m_addRequirementAction->setDisabled(false);

    m_propertiesWidget->hide();
    m_treeWidget->clear();
    this->getRequirements();
}

int CMainWindow::treeCount(QTreeWidgetItem *parent = 0)
{
    int count = 0;
    if (parent == 0) {
        int topCount = m_treeWidget->topLevelItemCount();
        for (int i = 0; i < topCount; i++) {
            QTreeWidgetItem *item = m_treeWidget->topLevelItem(i);
            if (item->isExpanded()) {
                count += treeCount(item);
            }
        }
        count += topCount;
    } else {
        int childCount = parent->childCount();
        for (int i = 0; i < childCount; i++) {
            QTreeWidgetItem *item = parent->child(i);
            if (item->isExpanded()) {
                count += treeCount(item);
            }
        }
        count += childCount;
    }
    return count;
}

void CMainWindow::createRequirement(QModelIndex parentModelIndex) {
    int parentIndex = -1;
    if(parentModelIndex.isValid()) {
        parentIndex = parentModelIndex.row();
    }

    QFrame* newRequirementMenu = new QFrame(this);
    newRequirementMenu->setProperty("menu", true);
    QFrame* newRequirementMenuHeader = new QFrame(newRequirementMenu);
    newRequirementMenuHeader->setStyleSheet("background-color: rgb(68,68,68);");
    QLabel* menuHeaderTitle = new QLabel("Criar novo requisito", newRequirementMenuHeader);
    menuHeaderTitle->setAlignment(Qt::AlignHCenter);
    menuHeaderTitle->setStyleSheet(tr("font-size: 28px;"));
    QHBoxLayout* menuHeaderLayout = new QHBoxLayout(newRequirementMenuHeader);
    menuHeaderLayout->setContentsMargins(2,14,2,14);
    menuHeaderLayout->setSpacing(5);
    menuHeaderLayout->addWidget(menuHeaderTitle);
    QFrame* newRequirementForm = new QFrame(newRequirementMenu);
    QLineEdit* leDefinition = new QLineEdit(newRequirementForm);
    leDefinition->setPlaceholderText(tr("Definição do requisito"));
    leDefinition->setFixedWidth(350);
    QTextEdit* qeEspecification = new QTextEdit(newRequirementForm);
    qeEspecification->setPlaceholderText(tr("Especificação do requisito"));
    qeEspecification->setFixedWidth(350);
    qeEspecification->setFixedHeight(100);
    QLabel* lblType = new QLabel(newRequirementForm);
    lblType->setText(tr("Tipo"));
    QComboBox* cbType = new QComboBox(newRequirementForm);
    cbType->addItem(tr("Funcional"));
    cbType->addItem(tr("Não Funcional"));
    cbType->addItem(tr("Negócio"));
    cbType->addItem(tr("Dominío"));
    QLabel* lblPriority = new QLabel(newRequirementForm);
    lblPriority->setText(tr("Prioridade"));
    QComboBox* cbPriority = new QComboBox(newRequirementForm);
    cbPriority->addItem(tr("5 - Muito Alta"));
    cbPriority->addItem(tr("4 - Alta"));
    cbPriority->addItem(tr("3 - Média"));
    cbPriority->addItem(tr("2 - Baixa"));
    cbPriority->addItem(tr("1 - Muito baixa"));
    QLabel* lblStatus = new QLabel(newRequirementForm);
    lblStatus->setText(tr("<b>Status: </b>") + tr("Não iniciado"));
    QLabel* lblAuthor = new QLabel(newRequirementForm);
    lblAuthor->setText(tr("<b>Criado por: </b>") + m_authUser->getFullName());
    QLabel* lblParentRequirement = new QLabel(newRequirementForm);
    if(parentIndex != -1) {
        auto parentRequirementRow =  m_requirementsRepository->
                getByIdAndProjectId(QString::number(parentIndex + 1), m_openedProject->getId());
        lblParentRequirement->setText(tr("<b>Super-requisito: </b>") + parentRequirementRow->getDefinition());
    }
    QDialogButtonBox* btnBox = new QDialogButtonBox(newRequirementForm);
    btnBox->addButton("Confirmar", QDialogButtonBox::AcceptRole);
    btnBox->addButton("Cancelar", QDialogButtonBox::RejectRole);
    btnBox->setFixedWidth(350);
    QVBoxLayout* newRequirementFormLayout = new QVBoxLayout(newRequirementForm);
    newRequirementFormLayout->setAlignment(Qt::AlignHCenter);
    newRequirementFormLayout->addWidget(leDefinition);
    newRequirementFormLayout->addWidget(qeEspecification);
    newRequirementFormLayout->addWidget(lblType);
    newRequirementFormLayout->addWidget(cbType);
    newRequirementFormLayout->addWidget(lblPriority);
    newRequirementFormLayout->addWidget(cbPriority);
    newRequirementFormLayout->addWidget(lblStatus);
    newRequirementFormLayout->addWidget(lblAuthor);
    if(parentIndex != -1) {
        newRequirementFormLayout->addWidget(lblParentRequirement);
    }
    newRequirementFormLayout->addWidget(btnBox);
    QVBoxLayout* newRequirementMenuLayout = new QVBoxLayout(newRequirementMenu);
    newRequirementMenuLayout->setContentsMargins(0,0,0,10);
    newRequirementMenuLayout->setSpacing(0);
    newRequirementMenuLayout->addWidget(newRequirementMenuHeader);
    newRequirementMenuLayout->addWidget(newRequirementForm);
    newRequirementMenuLayout->addStretch();

    WAF::Animation::sideSlideIn(newRequirementMenu, WAF::TopSide);

    connect(btnBox, &QDialogButtonBox::accepted, [=] {
        auto requirements = m_requirementsRepository->getByProjectId(m_openedProject->getId());

        QString id = QString::number(requirements.size() + 1);
        QString definition = leDefinition->text();
        QString especification = qeEspecification->toPlainText();
        QString type = cbType->currentText();
        QString priority = cbPriority->currentText();

        if(parentIndex != -1) {
            QString parentRequirementId = QString::number(parentIndex + 1);
        }

        QMessageBox msgError;
        msgError.setIcon(QMessageBox::Critical);
        msgError.setWindowTitle("Erro!");
        if(definition.length() == 0 || especification.length() == 0) {
            msgError.setText("Preencha todos os campos, por favor.");
            msgError.exec();
            return;
        }

        Requirement requirement;
        if(parentIndex != -1) {
            requirement = Requirement(id, definition, especification, type, priority,
                                      m_openedProject->getId(), m_authUser->getId(), QString::number(parentIndex + 1));
        } else {
            requirement = Requirement(id, definition, especification, type, priority,
                                      m_openedProject->getId(), m_authUser->getId());
        }

        auto* requirementRow = m_requirementsRepository->create(requirement);

        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, requirementRow->getId());
        item->setText(1, requirementRow->getDefinition());
        item->setText(2, requirementRow->getType());
        item->setText(3, requirementRow->getPriority());
        item->setText(4, requirementRow->getStatus());

        if(parentIndex != -1) {
            auto parent = m_treeWidget->itemFromIndex(parentModelIndex);
            parent->addChild(item);
            parent->setExpanded(true);
        } else {
            m_treeWidget->addTopLevelItem(item);
        }

        if(requirementRow) {
            WAF::Animation::sideSlideOut(newRequirementMenu, WAF::TopSide);
            WAF::Animation::sideSlideOut(m_menu, WAF::LeftSide);
        } else {
            msgError.setText("Ocorreu algum erro inesperado. Tente novamente mais tarde.");
            msgError.exec();
        }
    });

    connect(btnBox, &QDialogButtonBox::rejected, [=] {
        WAF::Animation::sideSlideOut(newRequirementMenu, WAF::TopSide);
    });
}

void CMainWindow::getRequirements() {
    auto requirements = m_requirementsRepository->getParentRequirements(m_openedProject->getId());

    requirements.reverse();
    for(auto requirement : requirements) {
        QTreeWidgetItem *item = new QTreeWidgetItem(m_treeWidget);
        item->setText(0, requirement.getId());
        item->setText(1, requirement.getDefinition());
        item->setText(2, requirement.getType());
        item->setText(3, requirement.getPriority());
        item->setText(4, requirement.getStatus());

        m_treeWidget->addTopLevelItem(item);
        auto subrequirements = m_requirementsRepository->getSubRequirements(requirement.getId(), m_openedProject->getId());

        subrequirements.reverse();
        for(auto subrequirement : subrequirements) {
            QTreeWidgetItem *subitem = new QTreeWidgetItem();
            subitem->setText(0, subrequirement.getId());
            subitem->setText(1, subrequirement.getDefinition());
            subitem->setText(2, subrequirement.getType());
            subitem->setText(3, subrequirement.getPriority());
            subitem->setText(4, subrequirement.getStatus());

            item->addChild(subitem);
            item->setExpanded(true);
        }
    }
}

void CMainWindow::logout() {
    Login* login = new Login();
    login->show();
    this->close();
}

void CMainWindow::quit() {
    QApplication::closeAllWindows();
    this->close();
}


//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    DockManager->deleteLater();
    QMainWindow::closeEvent(event);
}

