/*
    © 2016-2017 mocores
    This file is distributed under the MIT liscense.
    See LICENSE for details.
*/
#ifndef STATEMENT_H
#define STATEMENT_H

#include<string>

#include"sqlresultset.h"

namespace mocores
{
    /*!
     * \brief The Statement class
     * \deprecated Instead of SqlQuery.
     */
    class Statement
    {
    public:
        Statement(const std::string &){}
        virtual ~Statement();

        virtual SqlResultSet executeQuery(const std::string &sql)=0;
        virtual bool execute(const std::string &sql)=0;
        virtual int executeUpdate(const std::string & sql)=0;

        virtual void close()=0;
    };
    namespace sql_internal
    {

    }
}


#endif // STATEMENT_H
