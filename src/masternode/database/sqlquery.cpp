#include "sqlquery.h"
namespace mocores
{
    SqlQuery::SqlQuery(const std::string &sql, SqlConnection &con)
        :connection(&con),query(sql)
    {

    }

    SqlQuery::SqlQuery(SqlConnection &con)
        :connection(&con),query(nullptr)
    {

    }

    SqlQuery::~SqlQuery()
    {

    }

    SqlResultSet SqlQuery::exec(const std::string &query)
    {
        if(connection!=nullptr)
        {
            return connection->executeQuery(query);
        }
        else
        {
            throw SqlError(MOCORES_SQL_ERROR_CONNECTION_NOT_INIT);
        }
    }

    SqlResultSet SqlQuery::exec()
    {
        if(connection!=nullptr)
        {
            return connection->executeQuery(this->query);
        }
        else
        {
            throw SqlError(MOCORES_SQL_ERROR_CONNECTION_NOT_INIT);
        }
    }

    SqlError SqlQuery::lastError() const
    {
        return this->lastError();
    }
}

