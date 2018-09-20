/*
 * @Author: JasonWang
 * @Date: 2018-09-20 16:31:00
 * @LastEditors: OBKoro1
 * @LastEditTime: 2018-09-20 17:31:11
 * @Description:
 */
#ifndef MOCORES_CLUSTER_NODE_H
#define MOCORES_CLUSTER_NODE_H

namespace mocores
{
    class Node
    {
    private:
        bool is_running;

    public:
        Node();
        ~Node();

        int run(int argc, char* argv[]);

        int exit();
    };
}

#endif