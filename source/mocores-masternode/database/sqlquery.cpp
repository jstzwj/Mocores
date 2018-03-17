#include "sqlquery.h"
namespace mocores
{
    SqlQuery::SqlQuery(const std::string &sql, SqlDatabase &con)
        :connection(con.getConnection()),query(sql)
    {

    }

    SqlQuery::SqlQuery(SqlDatabase &con)
        :connection(con.getConnection()),query()
    {

    }

    SqlQuery::~SqlQuery()
    {

    }

    bool SqlQuery::exec(const std::string &query)
    {
        if(connection!=nullptr)
        {
            return connection->executeQuery(query,last_record,last_error);
        }
        else
        {
            return MOCORES_SQL_ERROR_CONNECTION_NOT_INIT;
        }
    }

    bool SqlQuery::exec()
    {
        if(connection!=nullptr)
        {
            return connection->executeQuery(this->query,last_record,last_error);
        }
        else
        {
            return MOCORES_SQL_ERROR_CONNECTION_NOT_INIT;
        }
    }

    SqlResultSet SqlQuery::resultset()
    {
        return last_record;
    }

    SqlError SqlQuery::lastError() const
    {
        return this->lastError();
    }
}

