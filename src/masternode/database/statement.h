#ifndef STATEMENT_H
#define STATEMENT_H

#include<string>

#include"resultset.h"


/**************
 * 本类已废弃
 *
 * ************/
namespace mocores
{
    class Statement
    {
    public:
        Statement(const std::string &){}
        virtual ~Statement();

        virtual ResultSet executeQuery(const std::string &sql)=0;
        virtual bool execute(const std::string &sql)=0;
        virtual int executeUpdate(const std::string & sql)=0;

        virtual void close()=0;
    };
    namespace sql_internal
    {

    }
}


#endif // STATEMENT_H
