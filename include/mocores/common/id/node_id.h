#include <cstdint>
#include <ctime>
#include <string>


namespace mocores
{
    class NodeID
    {
    public:
        std::string host;
        std::uint16_t port;
        std::uint64_t epoch;

		NodeID(std::string host, std::uint16_t port, std::uint64_t epoch)
		{

		}

        std::string to_string()
        {

        }


        void parse_string(const std::string &node_id)
        {

        }

        std::uint32_t hash()
        {
            
        }
    };
}