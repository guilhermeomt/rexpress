
#include "views/login.h"
#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "ui_form.h"

#include <QWidgetAction>
#include <QTreeView>
#include <QTimer>
#include <QTabWidget>
#include <QTreeWidget>
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

#include "src/Animation/Animation.h"
#include "src/StackedWidgetAnimation/StackedWidgetAnimation.h"

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
    QStringList labels;
    labels << "ID" << "Especificação " << "Tipo "<< "Prioridade" << "Status";
    treeWidget->setHeaderLabels(labels);
    treeWidget->header()->resizeSection(1, 250);
    CDockWidget* TableDockWidget = new CDockWidget("Requisitos");
    TableDockWidget->setIcon(QIcon(":/icons/svg/file.svg"));
    TableDockWidget->setWidget(treeWidget);
    auto* TableDockWidgetArea = DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TableDockWidget);
    m_TableDockWidgetArea = TableDockWidgetArea;
    ui->menuView->addAction(TableDockWidget->toggleViewAction());
    TableDockWidgetArea->setDisabled(true);

    Form* propertiesWidget = new Form();
    CDockWidget* PropertiesDockWidget = new CDockWidget("Propriedades");
    PropertiesDockWidget->setIcon(QIcon(":/icons/svg/view_details.svg"));
    PropertiesDockWidget->setWidget(propertiesWidget);
    auto* PropertiesDockWidgetArea = DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget);
    m_PropertiesDockWidgetArea = PropertiesDockWidgetArea;
    ui->menuView->addAction(PropertiesDockWidget->toggleViewAction());
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
    QPushButton* menuButtonNewProject = new QPushButton(QIcon(":/icons/svg/add_folder.svg"), "Novo projeto", menu);
    QPushButton* menuButtonOpenProject = new QPushButton(QIcon(":/icons/svg/opened_folder.svg"), "Abrir projeto", menu);
    menuButtonOpenProject->setProperty("menu", true);
    QPushButton* menuButtonInviteUser = new QPushButton(QIcon(":/icons/svg/user_folder.svg"), "Convidar usuário ao projeto", menu);
    m_menuButtonInviteUser = menuButtonInviteUser;
    menuButtonInviteUser->setProperty("menu", true);
    menuButtonInviteUser->setDisabled(true);
    QPushButton* menuButtonInvites = new QPushButton(QIcon(":/icons/svg/invite.svg"), "Convites", menu);
    m_menuButtonInvites = menuButtonInvites;
    menuButtonInvites->setProperty("menu", true);
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
    menuLayout->addWidget(menuButtonInviteUser);
    menuLayout->addWidget(menuButtonInvites);
    menuLayout->addWidget(menuButtonLogout);
    menuLayout->addWidget(menuButtonExit);
    menuLayout->addStretch();

    connect(menuButtonLogout, &QPushButton::clicked, [=] {
        Login* login = new Login();
        login->show();
        this->close();
    });

    connect(mainToolbarMenuButton, &QToolButton::clicked, [=] {
        WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
    });

    connect(menuButtonNewProject, &QPushButton::clicked, [this] {
        createProject();
    });

    connect(menuButtonInviteUser, &QPushButton::clicked, [this] {
        InviteUser* inviteUser = new InviteUser(m_authUser, m_openedProject, this);
        inviteUser->show();
    });


    connect(menuButtonInvites, &QPushButton::clicked, [this] {
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
    });

    connect(mainToolbarMenuButton, &QToolButton::clicked, [=] {
        WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
    });

    connect(menuButtonOpenProject, &QPushButton::clicked, [this] { chooseProject(); } );
}

void CMainWindow::getPendingInvites() {
    QSettings settings(":/settings/settings.ini", QSettings::IniFormat);
    m_invitationsRepository = new InvitationsRepository(settings);

    m_pendingInvitations = m_invitationsRepository->getByInviteeId(m_authUser->getId());

    if(!m_pendingInvitations) {
        m_pendingInvitations = new QVector<Invitation*>();
    }
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

        QSettings settings(":/settings/settings.ini", QSettings::IniFormat);
        m_projectsRepository = new ProjectsRepository(settings);

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
}

//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    DockManager->deleteLater();
    QMainWindow::closeEvent(event);
}


