#ifndef RESULTSET_H
#define RESULTSET_H
#include<vector>
#include<string>
#include"sqlrecord.h"
namespace mocores
{
    /*!
     * \brief The result of sql query.
     */
    class SqlResultSet:public std::vector<SqlRecord>
    {
    public:
        std::vector<std::string> colnames;
    };
}


#endif // RESULTSET_H
