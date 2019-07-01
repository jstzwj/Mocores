import mocores.core.runtime.runtime_worker

class WorkerBuilder(object):
    def __init__(self):
        pass

    def build(self):
        worker = mocores.core.runtime.runtime_worker.RuntimeWorker("dev", "HelloApp", "localhost", 60007, True)
        return worker