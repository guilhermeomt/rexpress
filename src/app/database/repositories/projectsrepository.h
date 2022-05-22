#ifndef PROJECTSREPOSITORY_H
#define PROJECTSREPOSITORY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "irepository.h"
#include "models/project.h"

class ProjectsRepository final : public QObject, public IRepository<Project, QString>
{
    Q_OBJECT
public:
    ProjectsRepository(DBManager* dbmanager, QObject* parent = nullptr);
    ~ProjectsRepository() {};

    std::list<Project> getAll() override;
    Project* getById(QString id) override;
    QVector<Project*>* getByUserId(QString userId);
    Project* getByName(QString name);
    Project* create(Project entity) override;
    bool addUserToProject(QString projectId, QString userId);
    Project* update(Project entity) override;
    Project* remove(QString id) override;
};

#endif // PROJECTSREPOSITORY_H
