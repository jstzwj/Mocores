#include "sqlmanager.h"

namespace mocores
{
    SqlManager::SqlManager()
    {

    }

    SqlConnection SqlManager::getConnection(const std::string &url, const std::string &user, const std::string &password)
    {
        int seperater=url.find_first_of(':');
        if(url.substr(0,seperater)=="sqlite3")
        {
            return
        }
        else
        {

        }
    }
}
