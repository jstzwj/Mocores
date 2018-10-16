import threading

class MessageQueue(object):
    def __init__(self):
        self.queue = []
        self.mutex = threading.Lock()

    def push_back(self, item):
        if self.mutex.acquire():
            self.queue.append(item)
            self.mutex.release()

    def pop_front(self):
        item = None
        if self.mutex.acquire():
            item = self.queue.pop(0)
            self.mutex.release()
        return item

    def pop_back(self):
        item = None
        if self.mutex.acquire():
            item = self.queue.pop(-1)
            self.mutex.release()
        return item

    def size(self):
        n = None
        if self.mutex.acquire():
            n = len(self.queue)
            self.mutex.release()
        return n