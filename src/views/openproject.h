#ifndef OPENPROJECT_H
#define OPENPROJECT_H

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidgetItem>

#include "database/repositories/projectsrepository.h"
#include "models/user.h"

namespace Ui {
class OpenProject;
}

class OpenProject : public QDialog
{
    Q_OBJECT

public:
    explicit OpenProject(User *authUser, QWidget *parent = nullptr);
    ~OpenProject();

signals:
    void accept(Project* project);

private slots:
    void on_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_btnBox_accepted();

private:
    Ui::OpenProject *ui;

    User* m_authUser = nullptr;

    ProjectsRepository* m_projectsRepository = nullptr;
};

#endif // OPENPROJECT_H
