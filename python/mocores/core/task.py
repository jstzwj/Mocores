

class Task(object):
    def __init__(self, from_worker, to_worker, time, work_item):
        self.from_worker = from_worker
        self.to_worker = to_worker
        self.time = time
        self.work_item = work_item
