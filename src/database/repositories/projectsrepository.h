#ifndef PROJECTSREPOSITORY_H
#define PROJECTSREPOSITORY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "repository.h"
#include "models/project.h"

class ProjectsRepository final :  public Repository<Project, int>
{
public:
    ProjectsRepository(QSettings &config);
    ~ProjectsRepository() { delete m_dbmanager; };

    std::list<Project> getAll() override;
    Project* getById(int id) override;
    QVector<Project*>* getByOwnerId(QString ownerId);
    Project* getByName(QString name);
    Project* create(Project entity) override;
    Project* update(Project entity) override;
    Project* remove(int id) override;
};

#endif // PROJECTSREPOSITORY_H
