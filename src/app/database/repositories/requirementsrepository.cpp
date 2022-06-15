#include "requirementsrepository.h"

RequirementsRepository::RequirementsRepository(DBManager* dbmanager, QObject* parent) : QObject(parent), IRepository<Requirement, QString>(dbmanager) {
    m_dbmanager->open();
};

std::list<Requirement> RequirementsRepository::getAll() {
    QSqlQuery query("SELECT id, definition, especification, status, type, "
                    "priority, project_id, created_at, updated_at, created_by_id, "
                    "updated_by_id, parent_requirement_id FROM requirements");

    std::list<Requirement> list;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString definition = query.value(1).toString();
        QString especification = query.value(2).toString();
        RequirementStatus status = Requirement::convertStatus (query.value(3).toString());
        QString type = query.value(4).toString();
        QString priority = query.value(5).toString();
        QString project_id = query.value(6).toString();
        QString created_at = query.value(7).toString();
        QString updated_at = query.value(8).toString();
        QString created_by_id = query.value(9).toString();
        QString updated_by_id = query.value(10).toString();
        QString parent_requirement_id = query.value(11).toString();

        Requirement requirement(id, definition, especification, type, status, priority, project_id,
                                created_at, updated_at, created_by_id, updated_by_id, parent_requirement_id);
        list.push_front(requirement);
    }
    return list;
}

std::list<Requirement> RequirementsRepository::getByProjectId(QString projectId) {
    QSqlQuery query;

    query.prepare("SELECT id, definition, especification, status, type, "
                  "priority, project_id, created_at, updated_at, created_by_id, "
                  "updated_by_id, parent_requirement_id FROM requirements WHERE project_id = :projectId");
    query.bindValue(":projectId", projectId.toInt());
    query.exec();

    std::list<Requirement> list;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString definition = query.value(1).toString();
        QString especification = query.value(2).toString();
        RequirementStatus status = Requirement::convertStatus(query.value(3).toString());
        QString type = query.value(4).toString();
        QString priority = query.value(5).toString();
        QString project_id = query.value(6).toString();
        QString created_at = query.value(7).toString();
        QString updated_at = query.value(8).toString();
        QString created_by_id = query.value(9).toString();
        QString updated_by_id = query.value(10).toString();
        QString parent_requirement_id = query.value(11).toString();

        Requirement requirement(id, definition, especification, type, status, priority, project_id,
                                created_at, updated_at, created_by_id, updated_by_id, parent_requirement_id);
        list.push_front(requirement);
    }
    return list;
}

Requirement* RequirementsRepository::getById(QString id) {
    QSqlQuery query;

    query.prepare("SELECT id, definition, especification, status, type, "
                  "priority, project_id, created_at, updated_at, created_by_id, "
                  "updated_by_id, parent_requirement_id FROM requirements WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if(query.next()) {
        QString id = query.value(0).toString();
        QString definition = query.value(1).toString();
        QString especification = query.value(2).toString();
        RequirementStatus status = Requirement::convertStatus(query.value(3).toString());
        QString type = query.value(4).toString();
        QString priority = query.value(5).toString();
        QString project_id = query.value(6).toString();
        QString created_at = query.value(7).toString();
        QString updated_at = query.value(8).toString();
        QString created_by_id = query.value(9).toString();
        QString updated_by_id = query.value(10).toString();
        QString parent_requirement_id = query.value(11).toString();

        Requirement* requirement = new Requirement(id, definition, especification, type, status, priority, project_id,
                                                   created_at, updated_at, created_by_id, updated_by_id, parent_requirement_id);
        return requirement;
    } else {
        return nullptr;
    }
}

Requirement* RequirementsRepository::getByIdAndProjectId(QString id, QString projectId) {
    QSqlQuery query;

    query.prepare("SELECT id, definition, especification, status, type, "
                  "priority, project_id, created_at, updated_at, created_by_id, "
                  "updated_by_id, parent_requirement_id FROM requirements WHERE id = :id"
                  " AND project_id = :projectId");
    query.bindValue(":id", id);
    query.bindValue(":projectId", projectId);
    query.exec();

    if(query.next()) {
        QString id = query.value(0).toString();
        QString definition = query.value(1).toString();
        QString especification = query.value(2).toString();
        RequirementStatus status = Requirement::convertStatus(query.value(3).toString());
        QString type = query.value(4).toString();
        QString priority = query.value(5).toString();
        QString project_id = query.value(6).toString();
        QString created_at = query.value(7).toString();
        QString updated_at = query.value(8).toString();
        QString created_by_id = query.value(9).toString();
        QString updated_by_id = query.value(10).toString();
        QString parent_requirement_id = query.value(11).toString();

        Requirement* requirement = new Requirement(id, definition, especification, type, status, priority, project_id,
                                                   created_at, updated_at, created_by_id, updated_by_id, parent_requirement_id);
        return requirement;
    } else {
        return nullptr;
    }
}


Requirement* RequirementsRepository::create(Requirement entity) {
    QSqlQuery query;

    query.prepare("INSERT INTO requirements(id, definition, especification, status, type, priority, project_id, created_by_id, parent_requirement_id)"
                  " VALUES (:id, :definition, :especification, :status, :type, :priority, :project_id, :created_by_id, :parent_requirement_id)");
    query.bindValue(":id", entity.getId().toInt());
    query.bindValue(":definition", entity.getDefinition());
    query.bindValue(":especification", entity.getEspecification());
    query.bindValue(":status", entity.getStatus());
    query.bindValue(":type", entity.getType());
    query.bindValue(":priority", entity.getPriority());
    query.bindValue(":project_id", entity.getProjectId().toInt());
    query.bindValue(":created_by_id", entity.getCreatedBy().toInt());
    query.bindValue(":parent_requirement_id", entity.getParentRequirementId().toInt());
    auto ok = query.exec();

    if(!ok) {
        return nullptr;
    }

    QString id = entity.getId();
    QString projectId = entity.getProjectId();

    Requirement* newRequirement = this->getByIdAndProjectId(id, projectId);

    return newRequirement;
}

std::list<Requirement> RequirementsRepository::getParentRequirements(QString projectId) {
    QSqlQuery query;

    query.prepare("SELECT id, definition, especification, status, type, "
                  "priority, project_id, created_at, updated_at, created_by_id, "
                  "updated_by_id, parent_requirement_id FROM requirements WHERE project_id = :projectId "
                  "AND parent_requirement_id = 0");
    query.bindValue(":projectId", projectId.toInt());
    query.exec();

    std::list<Requirement> list;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString definition = query.value(1).toString();
        QString especification = query.value(2).toString();
        RequirementStatus status = Requirement::convertStatus(query.value(3).toString());
        QString type = query.value(4).toString();
        QString priority = query.value(5).toString();
        QString project_id = query.value(6).toString();
        QString created_at = query.value(7).toString();
        QString updated_at = query.value(8).toString();
        QString created_by_id = query.value(9).toString();
        QString updated_by_id = query.value(10).toString();
        QString parent_requirement_id = query.value(11).toString();

        Requirement requirement(id, definition, especification, type, status, priority, project_id,
                                created_at, updated_at, created_by_id, updated_by_id, parent_requirement_id);
        list.push_front(requirement);
    }
    return list;
}


std::list<Requirement> RequirementsRepository::getSubRequirements(QString id, QString projectId) {
    QSqlQuery query;

    query.prepare("SELECT id, definition, especification, status, type, "
                  "priority, project_id, created_at, updated_at, created_by_id, "
                  "updated_by_id, parent_requirement_id FROM requirements WHERE parent_requirement_id = :parent_requirement_id"
                  " AND project_id = :projectId");
    query.bindValue(":parent_requirement_id", id);
    query.bindValue(":projectId", projectId);
    query.exec();

    std::list<Requirement> list;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString definition = query.value(1).toString();
        QString especification = query.value(2).toString();
        RequirementStatus status = Requirement::convertStatus(query.value(3).toString());
        QString type = query.value(4).toString();
        QString priority = query.value(5).toString();
        QString project_id = query.value(6).toString();
        QString created_at = query.value(7).toString();
        QString updated_at = query.value(8).toString();
        QString created_by_id = query.value(9).toString();
        QString updated_by_id = query.value(10).toString();
        QString parent_requirement_id = query.value(11).toString();

        Requirement requirement(id, definition, especification, type, status, priority, project_id,
                                created_at, updated_at, created_by_id, updated_by_id, parent_requirement_id);
        list.push_front(requirement);
    }
    return list;
}


Requirement* RequirementsRepository::update(Requirement entity) {
    return nullptr;
}

Requirement* RequirementsRepository::remove(QString id) {
    QSqlQuery query;

    query.prepare("DELETE FROM requirements WHERE id project_id = :projectId");
    query.bindValue(":projectId", id);
    query.exec();

    auto ok = query.exec();

    if(!ok) {
        return nullptr;
    }

    return new Requirement();
}

Requirement* RequirementsRepository::removeWithIdAndProjectId(QString id, QString projectId) {
    QSqlQuery query;

    query.prepare("DELETE FROM requirements WHERE id = :id AND project_id = :projectId");
    query.bindValue(":id", id);
    query.bindValue(":projectId", projectId);
    query.exec();

    auto ok = query.exec();

    if(!ok) {
        return nullptr;
    }

    return new Requirement();
}

