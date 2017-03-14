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
        Statement createStatement()=0;

        ResultSet executeQuery(const std::string &sql)=0;
        //boolean execute(const std::string &sql)=0;
        //int executeUpdate(const std::string & sql)=0;

        void open(const std::string & url,const std::string & user,const std::string & password)=0;
        void close()=0;
    };
    namespace sql_internal
    {
#include"sqlite/sqlite3.h"
        class ConnectionSqlite3:public SqlConnection
        {
        protected:
            sqlite3 *db = nullptr;
        public:
            SqlConnection()=default;
            virtual ~SqlConnection();
            Statement createStatement();

            ResultSet executeQuery(const std::string &sql);

            void open(const std::string & url, const std::string & user, const std::string & password);
            void close();
        };
    }
}


#endif // SQLCONNECTION_H
