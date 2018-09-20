
#include <boost/log/trivial.hpp>

#include <mocores/cluster/node.h>
namespace mocores
{
    Node::Node() : is_running(false) {}

    Node::~Node()
    {
        if (is_running) exit();
    }

    int Node::run(int argc, char* argv[])
    {
        BOOST_LOG_TRIVIAL(info) << "Mocores node is starting.";
        is_running = true;
        return 0;
    }

    int Node::exit()
    {
        BOOST_LOG_TRIVIAL(info) << "Mocores node is existing.";
        is_running = false;
        return 0;
    }
}
