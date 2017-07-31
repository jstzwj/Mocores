#include "mocoresinstance.h"

namespace mocores
{

    MocoresInstance::MocoresInstance(Settings &set)
        :setting(set)
    {

    }

    int MocoresInstance::run()
    {
        //守护进程

        //根据配置读取数据库内项目信息


        //读取项目信息列表

        /**
         * 开启computing node网络监听
         * 在线子节点登陆
         */


        /**
         * 判断上次是否因为崩溃关机
         * 如果因为崩溃关机，清理损坏数据（子节点定时清理）
        */


        /**
         *  开启项目调度器（根据最大并行项目数）
         *
         */


        //消息队列维护
        std::shared_ptr<MessageQueue> msgqueue{new MessageQueue};
        Message msg;

        //等待控制台输入(除了exit可以退出)
        while(msgqueue->getMessage(msg)!= true)
        {
            switch(msg.tagMsg)
            {

            }
            //降低cpu占用率
            mocores::this_thread::yield();
            mocores::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        //退出操作，清理资源

        return 0;
    }

}

