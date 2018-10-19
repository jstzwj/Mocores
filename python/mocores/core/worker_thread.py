import mocores.core.util
import threading

class WorkerThread(threading.Thread):
    def __init__(self):
        super(WorkerThread, self).__init__()
        self._messages = mocores.core.util.MessageQueue()
        self._condition = threading.Condition()
        self.actors = mocores.core.actor_pool.ActorPool()

    def run(self):
        self._condition.acquire()
        while (self._messages.size()!=0):
            self._condition.wait()
        if(self._messages.size()!=0):
            task = self._messages.pop_front()

        self._condition.release()

    def put(self, item):
        self._condition.acquire()
        self._messages.push_back(item)
        self._condition.notify()
        self._condition.release()
        