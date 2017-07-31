#ifndef SQLQUERY_H
#define SQLQUERY_H
#include<string>
#include"sqldatabase.h"
#include"sqlconnection.h"
#include"sqlresultset.h"

namespace mocores
{

    class SqlQuery
    {
    public:
        SqlQuery(const std::string & sql, SqlDatabase &con);
        SqlQuery(SqlDatabase &con);
        ~SqlQuery();

        bool exec(const std::string &query);
        bool exec();

        SqlResultSet resultset();

        SqlError lastError() const;
    protected:
        SqlConnection * connection;
        std::string query;
        SqlResultSet last_record;
        SqlError last_error;
    };

}

#endif // SQLQUERY_H
