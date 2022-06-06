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
                QString priority, QString projectId, QString createdAt, QString createdBy,
                QString updatedAt, QString updatedBy, QString parentRequirementId)
        : m_id(id),
          m_definition(definition),
          m_especification(especification),
          m_type(type),
          m_status(RequirementStatus::NOT_STARTED),
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
    RequirementStatus getStatus() const { return m_status; }
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
