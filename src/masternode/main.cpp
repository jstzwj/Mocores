#include <iostream>
#include"settings.h"
#include"logerror.h"
#include"mocoresinstance.h"


#include"database/mocores_sql.h"
#include"database/sqlwrapper.h"

using namespace std;

int main(int argc, char *argv[])
{

    mocores::SqlDatabase db=mocores::SqlManager::getConnection("sqlite3:data_frame.db");
    mocores::SqlQuery query(db);
    query.exec(mocores::SqlWrapper().select("*").from("node_info").where(mocores::SqlWrapper::equal("create_time","null")).get());
    for(auto each:query.resultset())
    {
        for(auto eachval:each)
        {
            std::cout<<eachval<<std::ends;
        }
        std::cout<<std::endl;
    }


    //读取数据库配置文件进入内存
    mocores::Settings settings;
    if(settings.readSettings()!=mocores::MOCORES_GOOD)
    {
        //读取配置失败退出
        return 1;
    }
    //开启错误日志
    if(mocores::errlog.openLogErrorFile(settings.log_error)!=false)
    {
        //错误日志打开失败退出
        return 1;
    }
    //构建数据库实例
    mocores::errlog.log(3,"Server started.");
    mocores::MocoresInstance instance(settings);
    instance.run();


    //析构实例
    mocores::errlog.log(3,"Server ended.");
    return 0;
}

