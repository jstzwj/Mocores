#ifndef STATEMENT_H
#define STATEMENT_H

#include<string>

#include"resultset.h"

namespace mocores
{
    class Statement
    {
    public:
        Statement(const std::string & query)=default;
        virtual ~Statement();

        ResultSet executeQuery(const std::string &sql)=0;
        boolean execute(const std::string &sql)=0;
        int executeUpdate(const std::string & sql)=0;

        void close()=0;
    };
    namespace sql_internal
    {

    }
}


#endif // STATEMENT_H
