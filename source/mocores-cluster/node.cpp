
#include <boost/log/trivial.hpp>
#include <boost/asio.hpp>

#include <mocores/common/util/platform_info.h>
#include <mocores/cluster/node.h>
#include <mocores/net/service_server.h>

using boost::asio::ip::tcp;

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

		// detect machine info
		getPlatformInfo();



		// start network service
		startNetworkService();

        return 0;
    }

    int Node::exit()
    {
        BOOST_LOG_TRIVIAL(info) << "Mocores node is existing.";
        is_running = false;
        return 0;
    }

	void Node::getPlatformInfo()
	{
		int cpu_num = hardware_concurrency();
		BOOST_LOG_TRIVIAL(info) << "Number of CPU cores is " << cpu_num << ".";
	}

	void Node::startNetworkService()
	{
		boost::asio::io_context io_context;
		tcp::endpoint endpoint(tcp::v4(), 25566);
		ServiceServer server(io_context, endpoint);
		io_context.run();
	}
}
