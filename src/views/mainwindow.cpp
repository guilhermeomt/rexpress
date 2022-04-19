#include "views/login.h"
#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "ui_form.h"

#include <QWidgetAction>
#include <QLabel>
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

#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "properties.h"

#include "../animations/src/Animation/Animation.h"
#include "../animations/src/StackedWidgetAnimation/StackedWidgetAnimation.h"

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

void CMainWindow::main() {
    ui->setupUi(this);
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    DockManager = new CDockManager(this);
    setWindowTitle(tr("Rexpress"));
    this->showMaximized();

    QWidget w;

    QTreeWidget* treeWidget = new QTreeWidget();
    QStringList labels;
    labels << "ID" << "Especificação " << "Tipo "<< "Prioridade" << "Status";
    treeWidget->setHeaderLabels(labels);
    treeWidget->header()->resizeSection(1, 250);
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0, tr("REQ01"));
    item->setText(1, tr("O sistema deve ter login"));
    item->setText(2, tr("Funcional"));
    item->setText(3, tr("Alta"));
    item->setText(4, tr("Em progresso"));
    treeWidget->addTopLevelItem(item);
    CDockWidget* TableDockWidget = new CDockWidget("Requisitos");
    TableDockWidget->setIcon(QIcon(":/icons/svg/file.svg"));
    TableDockWidget->setWidget(treeWidget);
    auto* TableDockWidgetArea = DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TableDockWidget);
    ui->menuView->addAction(TableDockWidget->toggleViewAction());
    TableDockWidgetArea->setDisabled(true);

    Form* propertiesWidget = new Form();
    CDockWidget* PropertiesDockWidget = new CDockWidget("Propriedades");
    PropertiesDockWidget->setIcon(QIcon(":/icons/svg/services.svg"));
    PropertiesDockWidget->setWidget(propertiesWidget);
    auto* PropertiesDockWidgetArea = DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget);
    ui->menuView->addAction(PropertiesDockWidget->toggleViewAction());
    propertiesWidget->hide();
    PropertiesDockWidgetArea->setDisabled(true);

    QFrame* mainToolbar = new QFrame(&w);
    mainToolbar->setProperty("toolbar", true);
    mainToolbar->setFrameShape(QFrame::StyledPanel);
    QToolButton* mainToolbarMenuButton = new QToolButton(mainToolbar);
    mainToolbarMenuButton->setIcon(QIcon(":/icons/svg/menu.svg"));
    QLabel* mainToolbarTitle = new QLabel("<b>Projeto Gemini</b>", mainToolbar);
    QHBoxLayout* mainToolbarLayout = new QHBoxLayout(mainToolbar);
    mainToolbarLayout->setContentsMargins(QMargins());
    mainToolbarLayout->setSpacing(10);
    mainToolbarLayout->addWidget(mainToolbarMenuButton);
    mainToolbarLayout->addWidget(mainToolbarTitle);
    CDockWidget* CentralDockWidget = new CDockWidget("Cabeçalho");
    CentralDockWidget->setWidget(mainToolbar);
    auto* CentralDockArea = DockManager->addDockWidget(DockWidgetArea::OuterDockAreas, CentralDockWidget);
    CentralDockArea->setDockAreaFlag(CDockAreaWidget::eDockAreaFlag::HideSingleWidgetTitleBar, true);
    CentralDockArea->setMaximumHeight(50);

    QFrame* menu = new QFrame(this);
    menu->setProperty("menu", true);
    menu->setFixedWidth(300);
    QFrame* menuToolbar = new QFrame(menu);
    menuToolbar->setStyleSheet(tr("border: 1px solid transparent;"));
    menuToolbar->setFrameShape(QFrame::StyledPanel);
    QLabel* menuToolbarBackButton = new QLabel(menuToolbar);
    menuToolbarBackButton->setPixmap(QPixmap(":/icons/svg/next.svg"));

    QLabel* menuToolbarTitle = new QLabel("<b>Logado como " + m_authUser->getFirstName(), menuToolbar);
    menuToolbarTitle->setStyleSheet(tr("color: #a1a1a1;"));
    QHBoxLayout* menuToolbarLayout = new QHBoxLayout(menuToolbar);
    menuToolbarLayout->setContentsMargins(QMargins());
    menuToolbarLayout->setSpacing(10);
    menuToolbarLayout->addWidget(menuToolbarBackButton);
    menuToolbarLayout->addWidget(menuToolbarTitle);
    QPushButton* menuButtonLogout = new QPushButton("Logout", menu);
    menuButtonLogout->setIcon(QIcon(":/icons/svg/up_left.svg"));
    menuButtonLogout->setProperty("menu", true);
    QVariantMap options;
    options.insert("color", QColor(Qt::yellow));
    options.insert("color-off", QColor(Qt::yellow));
    QPushButton* menuButtonProject = new QPushButton("Abrir projeto", menu);
    menuButtonProject->setProperty("menu", true);
    QPushButton* menuButtonExit = new QPushButton("Sair", menu);
    menuButtonExit->setProperty("menu", true);
    QVBoxLayout* menuLayout = new QVBoxLayout(menu);
    menuLayout->setSpacing(3);
    menuLayout->addWidget(menuToolbar);
    menuLayout->addWidget(menuButtonLogout);
    menuLayout->addWidget(menuButtonProject);
    menuLayout->addWidget(menuButtonExit);
    menuLayout->addStretch();

    connect(mainToolbarMenuButton, &QToolButton::clicked, [=] {
        WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
    });

    connect(menuButtonLogout, &QPushButton::clicked, [=] {
        Login* login = new Login();
        login->show();
        this->close();
    });
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    DockManager->deleteLater();
    QMainWindow::closeEvent(event);
}


