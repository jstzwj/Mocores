#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include<string>

#include"sqlconnection.h"

namespace mocores
{
    class SqlManager
    {
    public:
        SqlManager();
        static SqlConnection getConnection(const std::string & url,const std::string & user,const std::string & password);
    };
}


#endif // SQLMANAGER_H
