#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <QObject>

enum class RequirementStatus {
    NOT_STARTED,
    IN_PROGRESS,
    IMPLEMENTED,
    APPROVED,
    REJECTED,
    POSTPONED
};

class Requirement
{
public:
    explicit Requirement();
    Requirement(QString id, QString definition, QString especification, QString type,
                QString priority, QString projectId, QString createdBy)
        : m_id(id),
          m_definition(definition),
          m_especification(especification),
          m_type(type),
          m_status(RequirementStatus::NOT_STARTED),
          m_priority(priority),
          m_projectId(projectId),
          m_createdBy(createdBy)
    {};
    Requirement(QString id, QString definition, QString especification, QString type,
                QString priority, QString projectId, QString createdBy, QString parentRequirementId)
        : m_id(id),
          m_definition(definition),
          m_especification(especification),
          m_type(type),
          m_status(RequirementStatus::NOT_STARTED),
          m_priority(priority),
          m_projectId(projectId),
          m_createdBy(createdBy),
          m_parentRequirementId(parentRequirementId)
    {};
    Requirement(QString id, QString definition, QString especification,  QString type, RequirementStatus status,
                QString priority, QString projectId, QString createdAt, QString updatedAt,
                QString createdBy, QString updatedBy, QString parentRequirementId)
        : m_id(id),
          m_definition(definition),
          m_especification(especification),
          m_type(type),
          m_status(status),
          m_priority(priority),
          m_projectId(projectId),
          m_createdAt(createdAt),
          m_createdBy(createdBy),
          m_updatedAt(updatedAt),
          m_updatedBy(updatedBy),
          m_parentRequirementId(parentRequirementId)
    {};
    QString getId() const { return m_id; }
    void setId(QString id) { m_id = id; }
    QString getDefinition() const { return m_definition; }
    void setName(QString definition) { m_definition = definition; }
    QString getEspecification() const { return m_especification; }
    void setEspecification(QString especification) { m_especification = especification; }
    QString getType() const { return m_type; }
    void setType(QString type) { m_type = type; }
    QString getStatus() const {
        switch(m_status) {
        case RequirementStatus::NOT_STARTED:
            return "Não iniciado";
        case RequirementStatus::APPROVED:
            return "Aprovado";
        case RequirementStatus::IMPLEMENTED:
            return "Implementado";
        case RequirementStatus::IN_PROGRESS:
            return "Em progresso";
        case RequirementStatus::REJECTED:
            return "Rejeitado";
        case RequirementStatus::POSTPONED:
            return "Adiado";
        }
    }
    void setStatus(RequirementStatus status) { m_status = status; }
    QString getPriority() const { return m_priority; }
    void setPriority(QString priority) { m_priority = priority; }
    QString getProjectId() const { return m_projectId; }
    void setProjectId(QString projectId) { m_projectId = projectId; }
    QString getCreatedAt() const { return m_createdAt; }
    void setCreatedAt(QString createdAt) { m_createdAt = createdAt; }
    QString getCreatedBy() const { return m_createdBy; }
    void setCreatedBy(QString createdBy) { m_createdBy = createdBy; }
    QString getUpdatedAt() const { return m_updatedAt; }
    void setUpdatedAt(QString updatedAt) { m_updatedAt = updatedAt; }
    QString getUpdatedBy() const { return m_updatedBy; }
    void setUpdatedBy(QString updatedBy) { m_updatedBy = updatedBy; }
    QString getParentRequirementId() const { return m_parentRequirementId; }
    void setParentRequirementId(QString parentRequirementId) { m_parentRequirementId = parentRequirementId; }
    static RequirementStatus convertStatus(QString status) {
        if(status == "Não iniciado") {
            return RequirementStatus::NOT_STARTED;
        } else if (status == "Aprovado") {
            return RequirementStatus::APPROVED;
        } else if(status == "Implementado") {
            return RequirementStatus::IMPLEMENTED;
        } else if(status == "Em progresso") {
            return RequirementStatus::IN_PROGRESS;
        } else if(status == "Rejeitado") {
            return RequirementStatus::REJECTED;
        } else if(status == "Adiado") {
            return RequirementStatus::POSTPONED;
        }

        return RequirementStatus::NOT_STARTED;
    }
    QString getRequirementLabel(QString id) {
        auto value = id.toInt();
        if(value < 10) {
            return "REQ00" + id;
        } else if(value < 100) {
            return "REQ0" + id;
        }

        return "REQ" + id;
    }
private:
    QString m_id;
    QString m_definition;
    QString m_especification;
    QString m_type;
    RequirementStatus m_status;
    QString m_priority;
    QString m_projectId;
    QString m_createdAt;
    QString m_createdBy;
    QString m_updatedAt;
    QString m_updatedBy;
    QString m_parentRequirementId;
};

#endif // REQUIREMENT_H
