#ifndef RESULTSET_H
#define RESULTSET_H
#include<vector>
#include<string>
#include"sqlrecord.h"
#include"../errcode.h"
namespace mocores
{
    /*!
     * \brief The SqlError class
     * \brief Record the error of sql.
     */
    class SqlError
    {
    public:
        SqlError(ErrorCode errcode=MOCORES_GOOD,const std::string & str="")
            :error_info(str),code(errcode){}
        void setInfo(const std::string & str){error_info=str;}
        void setCode(ErrorCode errcode){code=errcode;}
        std::string getError(){return error_info;}
        ErrorCode getCode(){return code;}
    protected:
        std::string error_info;
        ErrorCode code;
    };
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
