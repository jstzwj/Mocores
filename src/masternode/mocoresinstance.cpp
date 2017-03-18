#include "mocoresinstance.h"

namespace mocores
{

    MocoresInstance::MocoresInstance(Settings &set)
        :setting(set)
    {

    }

    int MocoresInstance::run()
    {
        //根据配置读取数据库内项目信息

        //开启computing node网络监听

        //判断配置中是否有服务端程序，若有，打开网络监听

        //等待控制台输入(除了exit可以退出)
        //消息队列维护
        while(true)
        {

        }
        //退出操作，清理资源

        return 0;
    }

}

