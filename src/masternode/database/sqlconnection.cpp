#include "sqlconnection.h"

namespace mocores
{
    namespace sql_internal
    {
        ConnectionSqlite3::~ConnectionSqlite3()
        {
            if(db!=nullptr)
            {
                sqlite3_close(db);
                db=nullptr;
            }
        }

        SqlResultSet ConnectionSqlite3::executeQuery(const std::string &sql)
        {
            int ret=0;
            char * errmsg=nullptr;
            char ** dbresult=nullptr;
            int nrow=0;
            int ncolumn=0;
            SqlResultSet result;
            //判断sql操作类型
            ret = sqlite3_get_table(db,sql.c_str(),&dbresult,&nrow,&ncolumn,&errmsg);
            if(ret == SQLITE_OK)
            {
                int index=0;
                for(int i=0;i<nrow;i++)
                {
                    SqlRecord row;
                    for(int j=0;j<ncolumn;j++)
                    {
                        row.push_back(dbresult[index]);
                        index++;
                    }
                    result.push_back(row);
                }
                sqlite3_free_table(dbresult);
            }
            else
            {
                std::string errstr(errmsg);
                sqlite3_free(errmsg);
                throw errstr;
            }
            return result;
        }



        bool ConnectionSqlite3::open(const std::string &url, const std::string &user, const std::string &password)
        {
            int ret = 0;
            ret = sqlite3_open(url.c_str(),&db);
            if(ret != SQLITE_OK)
            {
                throw sqlite3_errmsg(db);
            }
        }

        void ConnectionSqlite3::close()
        {
            if(db!=nullptr)
            {
                sqlite3_close(db);
                db=nullptr;
            }
        }


    }
}

