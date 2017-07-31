#include <iostream>
#define WIN32_LEAN_AND_MEAN

#include"settings.h"
#include"log/logger.h"
#include"thread/singleton.h"
#include"mocoresinstance.h"


#include"database/mocores_sql.h"
#include"database/sqlwrapper.h"


//#include"event.h"

//#pragma warning(disable:4819)

using namespace std;
// 定时事件回调函数 
//void onTime(int sock, short event, void*arg)
//{
//	cout << "Game Over!" << endl;
//	struct timeval tv;
//	tv.tv_sec = 1;
//	tv.tv_usec = 0;
//	// 重新添加定时事件（定时事件触发后默认自动删除） 
//	event_add((struct event*)arg, &tv);
//}

int main(int argc, char *argv[])
{
//#ifdef WIN32
//	WSADATA wsa_data;
//	WSAStartup(0x0201, &wsa_data);
//#endif
//	// 初始化 
//	event_init();
//	struct event evTime;
//	// 设置定时事件 
//	evtimer_set(&evTime, onTime, &evTime);
//	struct timeval tv;
//	tv.tv_sec = 1;
//	tv.tv_usec = 0;
//	// 添加定时事件 
//	event_add(&evTime, &tv);
//	// 事件循环 
//	event_dispatch();
//	return 0;
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
    errlog->setAppender(mocores::FileAppender(settings.log_error));
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

