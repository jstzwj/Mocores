#include "sqlmanager.h"

namespace mocores
{
    SqlManager::SqlManager()
    {

    }

    std::shared_ptr<SqlConnection> SqlManager::getConnection(const std::string &url, const std::string &user, const std::string &password)
    {
        int seperater=url.find_first_of(':');
        if(url.substr(0,seperater)=="sqlite3")
        {
            std::shared_ptr<sql_internal::ConnectionSqlite3> con(new sql_internal::ConnectionSqlite3);
            con->open(url,user,password);
            return con;
        }
        else
        {

        }
    }
}
