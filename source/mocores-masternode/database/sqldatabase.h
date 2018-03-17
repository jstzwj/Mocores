#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include"sqlconnection.h"
namespace mocores
{
    class SqlDatabase
    {
    public:
        SqlDatabase();
        SqlDatabase(SqlConnection * con);
        SqlDatabase(const SqlDatabase & other);
        SqlDatabase& operator=(const SqlDatabase & other);
        void setConnection(SqlConnection * con);
        void removeConnection();
        SqlConnection * getConnection(){return connection;}
        bool open(const std::string & url, const std::string & user, const std::string & password);
        void close();
        ~SqlDatabase();
    protected:
        SqlConnection * connection;
        int * refcount;
    };
}


#endif // SQLDATABASE_H
