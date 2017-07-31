/*
    © 2016-2017 mocores
    This file is distributed under the MIT liscense.
    See LICENSE for details.
*/
#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include<string>
#include<memory>


#include"sqldatabase.h"
#include"sqlconnection.h"

namespace mocores
{
    class SqlManager
    {
    public:
        SqlManager();
        static SqlDatabase getConnection(const std::string & url,const std::string & user="root",const std::string & password="");
    };
}


#endif // SQLMANAGER_H
