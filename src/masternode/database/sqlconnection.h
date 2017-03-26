#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include"statement.h"

namespace mocores
{
    class SqlConnection
    {
    public:
        SqlConnection()=default;
        virtual ~SqlConnection()=default;
        //virtual Statement createStatement()=0;

        virtual SqlResultSet executeQuery(const std::string &sql)=0;
        //boolean execute(const std::string &sql)=0;
        //int executeUpdate(const std::string & sql)=0;

        virtual bool open(const std::string & url,const std::string & user,const std::string & password)=0;
        virtual void close()=0;
    };
    namespace sql_internal
    {
#include"sqlite/sqlite3.h"
        class ConnectionSqlite3:public SqlConnection
        {
        protected:
            sqlite3 *db;
        public:
            ConnectionSqlite3()=default;
            virtual ~ConnectionSqlite3();
            //Statement createStatement();

            SqlResultSet executeQuery(const std::string &sql);

            bool open(const std::string & url, const std::string & user, const std::string & password);
            void close();
        };
    }
}


#endif // SQLCONNECTION_H
