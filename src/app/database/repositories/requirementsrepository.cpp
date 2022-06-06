#include "requirementsrepository.h"

RequirementsRepository::RequirementsRepository(DBManager* dbmanager, QObject* parent) : QObject(parent), IRepository<Requirement, QString>(dbmanager) {
    m_dbmanager->open();
};


std::list<Requirement> RequirementsRepository::getAll() {
    QSqlQuery query("SELECT id, name, description, owner_id, created_at, updated_at FROM projects");

    std::list<Requirement> list;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString description = query.value(2).toString();
        QString ownerId = query.value(3).toString();
        QString createdAt = query.value(4).toString();
        QString updatedAt = query.value(5).toString();

        Requirement project(id, name, description, ownerId, createdAt, updatedAt);
        list.push_front(project);
    }
    return list;
}

Requirement* RequirementsRepository::getById(QString id) {
    QSqlQuery query;

    query.prepare("SELECT id, name, description, owner_id, created_at, updated_at FROM projects WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if(query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString description = query.value(2).toString();
        QString ownerId = query.value(3).toString();
        QString createdAt = query.value(4).toString();
        QString updatedAt = query.value(5).toString();

        Requirement* project = new Requirement(id, name, description, ownerId, createdAt, updatedAt);
        return project;
    } else {
        return nullptr;
    }
}

Requirement* RequirementsRepository::update(Requirement entity) {
    return nullptr;
}

Requirement* RequirementsRepository::remove(QString id) {
    return nullptr;
}

