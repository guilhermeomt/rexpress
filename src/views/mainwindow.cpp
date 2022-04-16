#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "ui_form.h"

#include <QWidgetAction>
#include <QLabel>
#include <QCalendarWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QTableWidget>
#include <QTabWidget>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QInputDialog>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QToolBar>
#include <QToolButton>
#include <QHeaderView>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "properties.h"

#include "../animations/src/Animation/Animation.h"
#include <../animations/src/StackedWidgetAnimation/StackedWidgetAnimation.h>


using namespace ads;

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
}

CMainWindow::CMainWindow(User* authUser, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow), m_authUser(authUser)
{
    ui->setupUi(this);
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    DockManager = new CDockManager(this);

    QWidget w;

    QSettings settings(":/settings/settings.ini", QSettings::IniFormat);
    DBManager = new class DBManager("QMYSQL", settings);

    DBManager->open();

//    QSqlQuery query("SELECT * FROM users");
//    int idName = query.record().indexOf("first_name");
//    QString name = tr("");
//    while (query.next())
//    {
//        name  = query.value(idName).toString();
//        qDebug() << name;
//    }

    DBManager->close();

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
    DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TableDockWidget);
    ui->menuView->addAction(TableDockWidget->toggleViewAction());

    Form* propertiesTable = new Form();
    CDockWidget* PropertiesDockWidget = new CDockWidget("Propriedades");
    PropertiesDockWidget->setIcon(QIcon(":/icons/svg/services.svg"));
    PropertiesDockWidget->setWidget(propertiesTable);
    DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget);
    ui->menuView->addAction(PropertiesDockWidget->toggleViewAction());

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

    QFrame* menu = new QFrame(&w);
    menu->setProperty("menu", true);
    menu->setFixedWidth(300);
    QFrame* menuToolbar = new QFrame(menu);
    menuToolbar->setFrameShape(QFrame::StyledPanel);
    QToolButton* menuToolbarBackButton = new QToolButton(menuToolbar);
    menuToolbarBackButton->setIcon(QIcon(":/icons/svg/bookmark.svg"));
    QLabel* menuToolbarTitle = new QLabel("<b>Logado como " + m_authUser->getFirstName(), menuToolbar);
    menuToolbarTitle->setStyleSheet(tr("color: #a1a1a1"));
    QHBoxLayout* menuToolbarLayout = new QHBoxLayout(menuToolbar);
    menuToolbarLayout->setContentsMargins(QMargins());
    menuToolbarLayout->setSpacing(10);
    menuToolbarLayout->addWidget(menuToolbarBackButton);
    menuToolbarLayout->addWidget(menuToolbarTitle);
    QPushButton* menuButtonLogout = new QPushButton("Logout", menu);
    menuButtonLogout->setIcon(QIcon(":/icons/svg/up_left.svg"));
    menuButtonLogout->setProperty("menu", true);
    QPushButton* menuButtonProject = new QPushButton("Abrir projeto", menu);
    menuButtonProject->setProperty("menu", true);
    QPushButton* menuButtonExit = new QPushButton("Sair", menu);
    menuButtonExit->setProperty("menu", true);
    QVBoxLayout* menuLayout = new QVBoxLayout(menu);
    menuLayout->setContentsMargins(QMargins());
    menuLayout->setSpacing(0);
    menuLayout->addWidget(menuToolbar);
    menuLayout->addWidget(menuButtonLogout);
    menuLayout->addWidget(menuButtonProject);
    menuLayout->addWidget(menuButtonExit);
    menuLayout->addStretch();
    CDockWidget* MenuDockWidget = new CDockWidget("Menu");
    MenuDockWidget->setWidget(menu);
    auto* MenuDockWidgetArea = DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea , MenuDockWidget);
    MenuDockWidgetArea->setMaximumWidth(0);
    MenuDockWidgetArea->setFixedHeight(900);
    menu->hide();

    QObject::connect(mainToolbarMenuButton, &QToolButton::clicked, [=] {
        WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
    });
}

CMainWindow::~CMainWindow()
{
    delete ui;
}


//void CMainWindow::createPerspectiveUi()
//{
//	SavePerspectiveAction = new QAction("Create Perspective", this);
//    connect(SavePerspectiveAction, SIGNAL(triggered()), SLOT(savePerspective()));
//    PerspectiveListAction = new QWidgetAction(this);
//    PerspectiveComboBox = new QPlainTextEdit(this);


//    PerspectiveComboBox->setSizeAdjustPolicy(QPlainTextEdit::AdjustToContentsOnFirstShow);
//    PerspectiveComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    PerspectiveComboBox->setPlaceholderText(tr("Filtrar..."));

//    connect(PerspectiveComboBox, SIGNAL(activated(const QString&)),
//        DockManager, SLOT(openPerspective(const QString&)));
//    PerspectiveListAction->setDefaultWidget(PerspectiveComboBox);
//	ui->toolBar->addSeparator();
//	ui->toolBar->addAction(PerspectiveListAction);
//	ui->toolBar->addAction(SavePerspectiveAction);
//}


void CMainWindow::savePerspective()
{
    QString PerspectiveName = QInputDialog::getText(this, "Save Perspective", "Enter unique name:");
    if (PerspectiveName.isEmpty())
    {
        return;
    }

    DockManager->addPerspective(PerspectiveName);
    QSignalBlocker Blocker(PerspectiveComboBox);
    PerspectiveComboBox->clear();
    //	PerspectiveComboBox->addItems(DockManager->perspectiveNames());
    //	PerspectiveComboBox->setCurrentText(PerspectiveName);
}


//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    DockManager->deleteLater();
    QMainWindow::closeEvent(event);
}


