#ifndef SQLQUERY_H
#define SQLQUERY_H
#include<string>
#include"sqlconnection.h"
#include"sqlresultset.h"
#include"errcode.h"
namespace mocores
{
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

    class SqlQuery
    {
    public:
        SqlQuery(const std::string & sql, SqlConnection &con);
        SqlQuery(SqlConnection &con);
        ~SqlQuery();

        SqlResultSet exec(const std::string &query);
        SqlResultSet exec();

        SqlError lastError() const;
    protected:
        SqlConnection * connection;
        const std::string query;
        SqlError last_error;
    };

}

#endif // SQLQUERY_H
