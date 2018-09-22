#ifndef MOCORES_SCHEDULER_TASK_SCHEDULER_H
#define MOCORES_SCHEDULER_TASK_SCHEDULER_H

#include <mocores/common/task.h>

namespace mocores
{
    class TaskScheduler
    {
        public:
        TaskScheduler();
        bool ExecuteTask(Task task);
        void QueueTask(Task task);
        bool DequeueTask(Task task);
    }
}

#endif