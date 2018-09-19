
#include <cstdint>
#include <string>

namespace mocores
{
    class Message
    {
    public:
        std::int32_t id;
        Message(std::int32_t packet_id)
            :id(packet_id)
        {
        }

        virtual std::string serialize() = 0;
        virtual void deserialize() = 0;
    };
}