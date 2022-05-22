    #ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlQuery>
#include <QSettings>

class QSqlDatabase;

class DBManager : public QObject
{
    Q_OBJECT
public:
    DBManager();
    DBManager(const QString& driver, QSettings* config, QObject* parent = nullptr);
    ~DBManager();

    QSqlDatabase* m_db;

    QSettings* config() const;

    bool isOpen() const;

    bool open();

    void close();


private:
    QSettings* m_config;
};

#endif // DBMANAGER_H
