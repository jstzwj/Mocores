#include "sqlmanager.h"

namespace mocores
{
    SqlManager::SqlManager()
    {

    }

    SqlDatabase SqlManager::getConnection(const std::string &url, const std::string &user, const std::string &password)
    {
        uint32_t seperater=url.find_first_of(':');
        if(url.substr(0,seperater)=="sqlite3")
        {
            SqlDatabase con(new sql_internal::ConnectionSqlite3);
            con.getConnection()->open(url.substr(seperater+1,url.length()),user,password);
            return con;
        }
        else
        {
			throw "Unknown database type";
        }
    }
}
