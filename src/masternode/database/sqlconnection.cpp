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

        ResultSet ConnectionSqlite3::executeQuery(const std::string &sql)
        {
            int ret=0;
            char * errmsg=nullptr;
            char ** dbresult=nullptr;
            int nrow=0;
            int ncolumn=0;
            ResultSet result;
            //判断sql操作类型
            ret = sqlite3_get_table(db,sql.c_str(),&dbresult,&nrow,&ncolumn,&errmsg);
            if(ret == SQLITE_OK)
            {
                int index=0;
                for(int i=0;i<nrow;i++)
                {
                    std::vector<std::string> row;
                    for(int j=0;j<ncolumn;j++)
                    {
                        row.push_back(dbresult[index]);
                        index++;
                    }
                    result.data.push_back(row);
                }
                sqlite3_free_table(dbresult);
            }
            else
            {
                throw errmsg;
            }
            return result;
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

