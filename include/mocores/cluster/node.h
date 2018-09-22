/*
 * @Author: JasonWang
 * @Date: 2018-09-20 16:31:00
 * @LastEditors: JasonWang
 * @LastEditTime: 2018-09-20 17:31:11
 * @Description:
 */
#ifndef MOCORES_CLUSTER_NODE_H
#define MOCORES_CLUSTER_NODE_H

#include <memory>

#include <mocores/cluster/worker_pool.h>
#include <mocores/common/config/config_node.h>

namespace mocores
{
    class Node
    {
    private:
        bool is_running;
        ConfigNode config;
        std::unique_ptr<WorkerPool> worker_pool;

    public:
        Node();
        ~Node();

        int run(int argc, char* argv[]);

        int exit();

    private:
        void getPlatformInfo();
        void readConfig();
        void startNetworkService();
    };
}

#endif