#ifndef REQUIREMENTSREPOSITORY_H
#define REQUIREMENTSREPOSITORY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "irepository.h"
#include "models/requirement.h"

class RequirementsRepository final : public QObject, public IRepository<Requirement, QString>
{
    Q_OBJECT
public:
    explicit RequirementsRepository(DBManager* dbmanager, QObject* parent = nullptr);
    ~RequirementsRepository() override { delete m_dbmanager; }

    std::list<Requirement> getAll() override;
    std::list<Requirement> getByProjectId(QString projectId);
    Requirement* getByIdAndProjectId(QString id, QString projectId);
    std::list<Requirement> getParentRequirements(QString projectId);
    std::list<Requirement> getSubRequirements(QString id, QString projectId);
    Requirement* getById(QString id) override;
    Requirement* create(Requirement entity) override;
    Requirement* update(Requirement entity) override;
    Requirement* remove(QString id) override;
    Requirement* removeWithIdAndProjectId(QString id, QString projectId);
};

#endif // REQUIREMENTSREPOSITORY_H
