#include "sqldatabase.h"

namespace mocores
{
    SqlDatabase::SqlDatabase()
        :connection(nullptr),refcount(nullptr){}

    SqlDatabase::SqlDatabase(SqlConnection *con)
        :connection(con),refcount(new int(1)){}

    SqlDatabase::SqlDatabase(const SqlDatabase &other)
        :connection(other.connection),refcount(other.refcount)
    {
        ++*refcount;
    }

    SqlDatabase &SqlDatabase::operator=(const SqlDatabase &other)
    {
        if(&other!=this)
        {
            removeConnection();
            refcount=other.refcount;
            connection=other.connection;
            (*refcount)++;
        }
        return *this;
    }

    void SqlDatabase::setConnection(SqlConnection *con)
    {
        if(connection!=nullptr)
        {
            delete connection;
            connection=nullptr;
        }
        if(refcount!=nullptr)
        {
            (*refcount)--;
            if(*refcount==0)
            {
                delete refcount;
                refcount=nullptr;
            }
        }
        connection=con;
    }

    void SqlDatabase::removeConnection()
    {
        if(refcount!=nullptr)
        {
            (*refcount)--;
            if(*refcount==0)
            {
                delete refcount;
                refcount=nullptr;
                if(connection!=nullptr)
                {
                    delete connection;
                    connection=nullptr;
                }
            }
        }
    }

    bool SqlDatabase::open(const std::string &url, const std::string &user, const std::string &password)
    {
        return connection->open(url,user,password);
    }

    void SqlDatabase::close()
    {
        connection->close();
    }

    SqlDatabase::~SqlDatabase()
    {
        removeConnection();
    }
}
