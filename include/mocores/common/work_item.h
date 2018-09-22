#ifndef MOCORES_COMMON_MESSAGE_H
#define MOCORES_COMMON_MESSAGE_H

#include <list>
#include <string>
#include <vector>
#include <cstdint>

namespace mocores
{
	enum WorkItemType
    {
        None = 0x0000,
        Request = 0x0001,         // New request received
        Response = 0x0002,        // Response to a request received
        Closure = 0x0004,         // Deferred closure
        Task = 0x0008,            // Execute a TPL task within an activation
        WorkItemGroup = 0x0010,   // Special -- activation worker as work item
        Invoke = 0x0020,          // Invoke a method on an activation
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
