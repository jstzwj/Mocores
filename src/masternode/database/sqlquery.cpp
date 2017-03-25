#include "sqlquery.h"
namespace mocores
{
    SqlQuery::SqlQuery(const std::string &sql, const SqlConnection &con)
        :connection(nullptr),query(nullptr)
    {

    }

    SqlQuery::SqlQuery(const SqlConnection &con)
        :connection(nullptr),query(nullptr)
    {

    }
}

