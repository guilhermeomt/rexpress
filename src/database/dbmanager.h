#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlQuery>
#include <QSettings>

class QSqlDatabase;

class DBManager : public QObject
{
public:
    DBManager(const QString& driver, QSettings &config, QObject *parent = 0);
    ~DBManager();

    QSqlDatabase* m_db;

    QSettings& config() const;

    bool queryExec(QSqlQuery &query,const QString& sql);

    bool isOpen() const;

    bool open();

    void close();


private:
    QSettings& m_config;
};

#endif // DBMANAGER_H
