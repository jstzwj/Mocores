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
    class SqlResultSet
    {
    public:
        SqlResultSet();
        std::vector<SqlRecord> data;
    };
}


#endif // RESULTSET_H
