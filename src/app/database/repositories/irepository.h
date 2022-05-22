#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <iostream>
#include <list>
#include "database/dbmanager.h"
#include "../../../dependency_injection/instantiationservice.h"

template<class T, class U>
class IRepository {
public:
    IRepository(DBManager* dbmanager) : m_dbmanager(dbmanager) { };
    virtual ~IRepository() { }

    virtual std::list<T> getAll() = 0;
    virtual T* getById(U id) = 0;
    virtual T* create(T entity) = 0;
    virtual T* update(T entity) = 0;
    virtual T* remove(U id) = 0;
protected:
    DBManager* m_dbmanager{nullptr};
};

#endif // IREPOSITORY_H
