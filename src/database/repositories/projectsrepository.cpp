#include "projectsrepository.h"


ProjectsRepository::ProjectsRepository(QSettings &config) : Repository<Project,int>(config) {
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

Project* ProjectsRepository::getById(int id) {
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

QVector<Project*>* ProjectsRepository::getByOwnerId(QString ownerId) {

    QSqlQuery query;
    query.prepare("SELECT DISTINCT pr.id, pr.name, pr.description, pr.owner_id, pr.created_at, pr.updated_at FROM projects pr"
                  " INNER JOIN users ON pr.owner_id = :userId");
    query.bindValue(":userId", ownerId);
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
     if(vector) {
         return vector;
     } else {
         return nullptr;
     }
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
    } else {
        return nullptr;
    }
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
    int id = lastId.toInt();

    Project* newProject = this->getById(id);

    return newProject;
}

Project* ProjectsRepository::update(Project entity) {
   return nullptr;
}

Project* ProjectsRepository::remove(int id) {
   return nullptr;
}
