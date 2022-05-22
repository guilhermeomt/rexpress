#include "projectsrepository.h"


ProjectsRepository::ProjectsRepository(DBManager* dbmanager, QObject* parent) : QObject(parent), IRepository<Project, QString>(dbmanager) {
    m_dbmanager->open();
};

std::list<Project> ProjectsRepository::getAll() {
    QSqlQuery query("SELECT id, name, description, owner_id, created_at, updated_at FROM projects");

    std::list<Project> list;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString description = query.value(2).toString();
        QString ownerId = query.value(3).toString();
        QString createdAt = query.value(4).toString();
        QString updatedAt = query.value(5).toString();

        Project project(id, name, description, ownerId, createdAt, updatedAt);
        list.push_front(project);
    }
    return list;
}

Project* ProjectsRepository::getById(QString id) {
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

        Project* project = new Project(id, name, description, ownerId, createdAt, updatedAt);
        return project;
    } else {
        return nullptr;
    }
}

QVector<Project*>* ProjectsRepository::getByUserId(QString userId) {

    QSqlQuery query;
    query.prepare("SELECT DISTINCT pr.id, pr.name, pr.description, pr.owner_id, pr.created_at, pr.updated_at FROM projects pr"
                  " INNER JOIN users_projects up ON up.project_id = pr.id WHERE up.user_id = :userId");
    query.bindValue(":userId", userId);
    query.exec();

    QVector<Project*>* vector = new QVector<Project*>();
    while(query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString description = query.value(2).toString();
        QString ownerId = query.value(3).toString();
        QString createdAt = query.value(4).toString();
        QString updatedAt = query.value(5).toString();

        Project* project = new Project(id, name, description, ownerId, createdAt, updatedAt);
        vector->push_front(project);
    }
    if(!vector->empty()) {
        return vector;
    }

    return nullptr;
}

Project* ProjectsRepository::getByName(QString name) {
    QSqlQuery query;

    query.prepare("SELECT id, name, description, owner_id, created_at, updated_at FROM projects WHERE name = :name");
    query.bindValue(":name", name);
    query.exec();

    if(query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString description = query.value(2).toString();
        QString ownerId = query.value(3).toString();
        QString createdAt = query.value(4).toString();
        QString updatedAt = query.value(5).toString();

        Project* project = new Project(id, name, description, ownerId, createdAt, updatedAt);
        return project;
    }

    return nullptr;
}

Project* ProjectsRepository::create(Project entity) {
    QSqlQuery query;

    query.prepare("INSERT INTO projects(name, description, owner_id)"
                  " VALUES (:name, :description, :ownerId)");
    query.bindValue(":name", entity.getName());
    query.bindValue(":description", entity.getDescription());
    query.bindValue(":ownerId", entity.getOwnerId());
    auto ok = query.exec();

    if(!ok) {
        return nullptr;
    }

    QVariant lastId = query.lastInsertId();
    QString id = lastId.toString();

    Project* newProject = this->getById(id);

    query.prepare("INSERT INTO users_projects(project_id, user_id)"
                  " VALUES (:projectId, :ownerId)");
    query.bindValue(":projectId", id);
    query.bindValue(":ownerId", entity.getOwnerId());
    ok = query.exec();

    if(!ok) {
        delete newProject;
        return nullptr;
    }

    return newProject;
}


bool ProjectsRepository::addUserToProject(QString projectId, QString userId) {
    QSqlQuery query;

    query.prepare("INSERT INTO users_projects(project_id, user_id)"
                  " VALUES (:projectId, :userId)");
    query.bindValue(":projectId", projectId);
    query.bindValue(":userId", userId);
    auto ok = query.exec();

    return ok;
}

Project* ProjectsRepository::update(Project entity) {
    return nullptr;
}

Project* ProjectsRepository::remove(QString id) {
    return nullptr;
}
