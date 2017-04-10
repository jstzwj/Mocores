#include <iostream>
#include"settings.h"
#include"log/logger.h"
#include"thread/singleton.h"
#include"mocoresinstance.h"


#include"database/mocores_sql.h"
#include"database/sqlwrapper.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    mocores::SqlDatabase db=mocores::SqlManager::getConnection("sqlite3:data_frame.db");
    mocores::SqlQuery query(db);
    query.exec(mocores::SqlWrapper().select("*").from("node_info").where(mocores::SqlWrapper::is("create_time","null")).get());
    for(auto each:query.resultset())
    {
        for(auto eachval:each)
        {
            std::cout<<eachval<<std::ends;
        }
        std::cout<<std::endl;
    }
    */

    //读取数据库配置文件进入内存
    mocores::Settings settings;
    if(settings.readSettings()!=mocores::MOCORES_GOOD)
    {
        //读取配置失败退出
        return 1;
    }
    //开启错误日志
    mocores::Logger * errlog=&mocores::Singleton<mocores::Logger>::getInstance();
    errlog->configure();
    errlog->setName("errlog");
    errlog->setAppender(new mocores::FileAppender(settings.log_error));
    errlog->setLayout(mocores::LogLayout("%t\t[%p]\t%m%n"));
    errlog->start();

    //日志输出测试
    long long i=1e7;
    clock_t start=clock();
    while(i-->0)
    {
        errlog->info("LogQuickTest:id="+std::to_string(i)+"time:"+std::to_string(clock()-start)+
			"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    }
    std::cout<<"Time used:"<<clock()-start<<std::endl;
    //构建数据库实例
    errlog->info("Server started.");
    mocores::MocoresInstance instance(settings);
    instance.run();


    //析构实例
    errlog->info("Server ended.");
    return 0;
}

