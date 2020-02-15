import queue

class Task(object):
    grain_type = None
    grain_identity = None
    grain_method = None
    grain_params = None
    def __init__(self):
        pass


class ThreadTaskScheduler(object):
    def __init__(self):
        self.task_queue = queue.Queue()

    def add_task(self, t):
        self.task_queue.put(t)

    def execute(self):
        if not self.task_queue.empty():
            t = self.task_queue.get()
            t.execute()

class ActivationTaskScheduler(object):
    def __init__(self):
        self.task_queue = queue.Queue()

    def add_task(self, t):
        self.task_queue.put(t)

    def execute(self):
        if not self.task_queue.empty():
            t = self.task_queue.get()
            t.execute()
