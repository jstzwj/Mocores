#ifndef MOCORES_COMMON_MESSAGE_H
#define MOCORES_COMMON_MESSAGE_H

#include <cstdint>
#include <list>
#include <string>
#include <vector>

namespace mocores
{
    enum WorkItemType
    {
        None = 0x0000,
        Request = 0x0001,       // New request received
        Response = 0x0002,      // Response to a request received
        Invoke = 0x0004,        // Invoke a method on an activation
    };

    class IWorkItem
    {
    public:
        std::string name;
        WorkItemType itemType;

        std::int64_t timeQueued;
        void execute();
    };
}

#endif // !MOCORES_COMMON_MESSAGE_H
