#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include"sqlresultset.h"

#include"../utility/strutil.h"

namespace mocores
{   
    /*!
     * \brief The SqlConnection class
     * \note We will finish prepare sqlite statement later.
     */
    class SqlConnection
    {
    public:
        SqlConnection()=default;
        virtual ~SqlConnection()=default;

        virtual bool executeQuery(const std::string &sql,mocores::SqlResultSet &record, SqlError &error)=0;

        virtual bool open(const std::string & url,const std::string & user,const std::string & password)=0;
        virtual void close()=0;
    };
    namespace sql_internal
    {
#include"../sqlite/sqlite3.h"

        class ConnectionSqlite3:public SqlConnection
        {
        protected:
            sqlite3 *db;
        public:
            ConnectionSqlite3()=default;
            virtual ~ConnectionSqlite3();

            virtual bool executeQuery(const std::string &sql, mocores::SqlResultSet &record, SqlError &error);

            virtual bool open(const std::string & url, const std::string & user, const std::string & password);
            virtual void close();

        protected:
            /*!
             * \brief get type of query
             * \details -1 unknown type
             *          1 create
             *          2 insert
             *          3 update
             *          4 select
             *          5 delete
            */
            int getQueryType(const std::string &str);
            /**
             * @brief SQLite SelectCallback
             * @param p_data
             * @param num_fields
             * @param p_fields
             * @param p_col_names
             * @return
             */
            static int SelectCallback(void *p_data, int num_fields, char **p_fields, char** p_col_names);
        };
    }
}


#endif // SQLCONNECTION_H
