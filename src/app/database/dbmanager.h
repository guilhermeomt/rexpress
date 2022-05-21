#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlQuery>
#include <QSettings>

class QSqlDatabase;

class DBManager
{
public:
    DBManager(const QString& driver, QSettings &config);
    ~DBManager();

    QSqlDatabase* m_db;

    QSettings& config() const;

    bool isOpen() const;

    bool open();

    void close();


private:
    QSettings& m_config;
};

#endif // DBMANAGER_H
