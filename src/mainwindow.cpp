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
#include <QHeaderView>

#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "form.h"

using namespace ads;


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    DockManager = new CDockManager(this);

    // Set central widget
//    QPlainTextEdit* w = new QPlainTextEdit();
//	w->setPlaceholderText("This is the central editor. Enter your text here.");
//    CDockWidget* CentralDockWidget = new CDockWidget("CentralWidget");
//    CentralDockWidget->setWidget(w);
//    auto* CentralDockArea = DockManager->setCentralWidget(CentralDockWidget);
//    CentralDockArea->setAllowedAreas(DockWidgetArea::OuterDockAreas);

    // create other dock widgets
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
    TableDockWidget->setWidget(treeWidget);
    TableDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->resize(250, 150);
    TableDockWidget->setMinimumSize(200,150);
    DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TableDockWidget);
    ui->menuView->addAction(TableDockWidget->toggleViewAction());

    Form* propertiesTable = new Form();
    CDockWidget* PropertiesDockWidget = new CDockWidget("Propriedades");
    PropertiesDockWidget->setWidget(propertiesTable);
    PropertiesDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    PropertiesDockWidget->resize(300, 150);
    PropertiesDockWidget->setMinimumSize(200,150);
    DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget);
    ui->menuView->addAction(PropertiesDockWidget->toggleViewAction());

  //  createPerspectiveUi();
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


