#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <list>
#include "database/dbmanager.h"

template<class T, class U>
class Repository
{
public:
   Repository();
   Repository(QSettings &config) : m_dbmanager(new DBManager("QMYSQL", config)) {};
   ~Repository() { }

   virtual std::list<T> getAll() = 0;
   virtual T* getById(U id) = 0;
   virtual T* create(T entity) = 0;
   virtual T* update(T entity) = 0;
   virtual T* remove(U id) = 0;
protected:
    DBManager* m_dbmanager;
};

#endif // REPOSITORY_H
