#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QWidgetAction>
#include <QPlainTextEdit>

#include "DockManager.h"
#include "DockAreaWidget.h"
#include "DockWidget.h"

#include "models/user.h"
#include "database/dbmanager.h"

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
    QAction* SavePerspectiveAction = nullptr;
    QWidgetAction* PerspectiveListAction = nullptr;
    QPlainTextEdit* PerspectiveComboBox = nullptr;

    Ui::CMainWindow *ui;

    DBManager* DBManager = nullptr;

    ads::CDockManager* DockManager;
    ads::CDockAreaWidget* StatusDockArea;
    ads::CDockWidget* TimelineDockWidget;

    void createPerspectiveUi();

    User* m_authUser;

private slots:
	void savePerspective();
};
#endif // MAINWINDOW_H
