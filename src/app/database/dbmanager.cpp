#include "database/dbmanager.h"
#include <QtSql/QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <iostream>

DBManager::DBManager() {
    m_config = new QSettings(":/settings/settings.ini", QSettings::IniFormat);
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
}

DBManager::DBManager(const QString& driver, QSettings* config, QObject* parent)
    : QObject(parent), m_db(nullptr), m_config(config)
{
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase(driver));
}

DBManager::~DBManager()
{
    close();
    QSqlDatabase::removeDatabase(m_db->connectionName());
    delete m_db;
    m_db = nullptr;
}

bool DBManager::isOpen() const
{
    bool b = m_db->isOpen();
    if(!b) {
        qDebug() << "database is not open.";
    }

    return b;
}

bool DBManager::open()
{
    if(m_db->isOpen()){
        return true;
    }

    m_config->beginGroup(QSettings::tr("DBConnection"));
    QString hostname = m_config->value("hostname").toString();
    QString database = m_config->value("database").toString();
    QString username = m_config->value("username").toString();
    QString password = m_config->value("password").toString();
    m_config->endGroup();

    m_db->setHostName(hostname);
    m_db->setDatabaseName(database);
    m_db->setUserName(username);
    m_db->setPassword(password);

    bool b = m_db->open();
    if(!b) {
        qDebug() << "DBManager::open " << m_db->lastError();
    }
    return b;
}

void DBManager::close()
{
    if (m_db->isOpen())
    {
        m_db->close();
    }
}

QSettings* DBManager::config() const
{
    return m_config;
}
