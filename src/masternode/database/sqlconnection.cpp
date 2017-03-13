#include "sqlconnection.h"

namespace mocores
{
    namespace sql_internal
    {
        ConnectionSqlite3::SqlConnection(const std::string & _url, const std::string &_user, const std::string &_password)
            :url(_url),user(_user),password(_password)
        {
            const char *sql_create_table="create table t(id int primary key,msg varchar(128))";


                printf("Open database\n");

                ret = sqlite3_exec(db,sql_create_table,NULL,NULL,&errmsg);
                if(ret != SQLITE_OK){
                    fprintf(stderr,"create table fail: %s\n",errmsg);
                }
                sqlite3_free(errmsg);

        }

        ConnectionSqlite3::~SqlConnection()
        {
            if(db!=nullptr)
            {
                sqlite3_close(db);
                db=nullptr;
            }
        }

        Statement ConnectionSqlite3::createStatement()
        {

        }

        void ConnectionSqlite3::open(const std::string &url, const std::string &user, const std::string &password)
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

