/*
    © 2016-2017 mocores
    This file is distributed under the MIT liscense.
    See LICENSE for details.
*/
#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include<string>
#include<memory>

#include"sqlconnection.h"

namespace mocores
{
    class SqlManager
    {
    public:
        SqlManager();
        static std::shared_ptr<SqlConnection> getConnection(const std::string & url,const std::string & user,const std::string & password);
    };
}


#endif // SQLMANAGER_H
