#ifndef SQLRECORD_H
#define SQLRECORD_H
#include<vector>
#include<string>
#include"../utility/mvariant.h"
namespace mocores
{
    /*!
     * \brief Sql basic value.
     */
    using SqlType=MVariant<int,double,std::string>;
    /*!
     * \brief Represents a record in sql result sets.
     */
    class SqlRecord:public std::vector<std::string>
    {
    public:
        std::vector<bool> isNull;
    };
    /*
    class SqlRecord
    {
    public:
        SqlRecord();
    protected:
        std::vector<SqlType> record_data;

    };
    */
}


#endif // SQLRECORD_H
