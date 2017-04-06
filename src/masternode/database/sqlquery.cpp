#include "sqlquery.h"
namespace mocores
{
    SqlQuery::SqlQuery(const std::string &sql, SqlConnection &con)
        :connection(&con),query(sql)
    {

    }

    SqlQuery::SqlQuery(SqlConnection &con)
        :connection(&con),query()
    {

    }

    SqlQuery::~SqlQuery()
    {

    }

    bool SqlQuery::exec(const std::string &query)
    {
        if(connection!=nullptr)
        {
            return connection->executeQuery(query,last_record);
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
            return connection->executeQuery(this->query,last_record);
        }
        else
        {
            return MOCORES_SQL_ERROR_CONNECTION_NOT_INIT;
        }
    }

    SqlResultSet SqlQuery::record()
    {
        return last_record;
    }

    SqlError SqlQuery::lastError() const
    {
        return this->lastError();
    }
}

