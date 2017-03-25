#ifndef SQLQUERY_H
#define SQLQUERY_H
#include<string>
#include"sqlconnection.h"
#include"resultset.h"
namespace mocores
{
    class SqlError
    {
    public:

    };

    class SqlQuery
    {
    public:
        SqlQuery(const std::string & sql,const SqlConnection & con);
        SqlQuery(const SqlConnection & con);
        SqlQuery(const SqlQuery &other);
        ~SqlQuery();

        bool exec(const std::string &query);
        bool exec();

        SqlError lastError() const;
    protected:
        SqlConnection * connection;
        const std::string * query;
        SqlError last_error;
    };

}

#endif // SQLQUERY_H
