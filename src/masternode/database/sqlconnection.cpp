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

        bool ConnectionSqlite3::executeQuery(const std::string &sql, SqlResultSet &record)
        {
            int type=getQueryType(sql);
            if(type==0)
            {

            }
            else if(type==1)
            {

            }
            else if(type==2)
            {

            }
            else if(type==3)
            {

            }
            else if(type==4)//select
            {
                char *errmsg;
                int   ret;
                ret = sqlite3_exec(db, sql.c_str(), SelectCallback, static_cast<void*> (&record), &errmsg);
                if (ret != SQLITE_OK)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            else if(type==5)
            {

            }
            /*
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
            */
        }



        bool ConnectionSqlite3::open(const std::string &url, const std::string &user, const std::string &password)
        {
            int ret = 0;
            ret = sqlite3_open(url.c_str(),&db);
            if(ret != SQLITE_OK)
            {
                throw sqlite3_errmsg(db);
            }
            return true;
        }

        void ConnectionSqlite3::close()
        {
            if(db!=nullptr)
            {
                sqlite3_close(db);
                db=nullptr;
            }
        }
        int ConnectionSqlite3::getQueryType(const std::string &str)
        {
            int pos=0;
            StrUtil::consumeSpace(str,pos);
            if(StrUtil::isStr(str,pos,"create",mocores::MOCORES_STRUTIL_NON_CASE_SENSITIVE))
            {
                return 1;
            }
            else if(StrUtil::isStr(str,pos,"insert",mocores::MOCORES_STRUTIL_NON_CASE_SENSITIVE))
            {
                return 2;
            }
            else if(StrUtil::isStr(str,pos,"update",mocores::MOCORES_STRUTIL_NON_CASE_SENSITIVE))
            {
                return 3;
            }
            else if(StrUtil::isStr(str,pos,"select",mocores::MOCORES_STRUTIL_NON_CASE_SENSITIVE))
            {
                return 4;
            }
            else if(StrUtil::isStr(str,pos,"delete",mocores::MOCORES_STRUTIL_NON_CASE_SENSITIVE))
            {
                return 5;
            }
            else
            {
                return -1;
            }
        }

        int ConnectionSqlite3::SelectCallback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
        {
            SqlResultSet* res = reinterpret_cast<SqlResultSet*>(p_data);
            SqlRecord record;

            #ifdef SQLITE_WRAPPER_REPORT_COLUMN_NAMES
            // Hubert Castelain: column names in the first row of res if res is empty

            if(res->size()==0)
            {
                std::vector<std::string> col_name;
                for(int i=0; i < num_fields; i++)
                {
                    if(p_fields[i])
                        col_name.push_back (std::string(p_col_names[i]));
                    else
                        col_name.push_back(std::string("(null)")); // or what else ?
                }
                res->colnames.push_back(col_name);
            }
            #endif

            for(int i=0; i < num_fields; i++)
            {
                if (p_fields[i])
                {

                    record.push_back(std::string(p_fields[i]));
                }
                else
                {
                    record.push_back(std::string("<null>"));
                }
            }
            res->push_back(record);

            return 0;
       }


    }
}

