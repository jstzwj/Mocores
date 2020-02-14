from multiprocessing import Pool, Process, Queue
import time
import importlib
import sys

import pickle
import asyncio

from mocores.silo.nethub import NetHub
from mocores.silo.scheduler import ThreadTaskScheduler, ActivationTaskScheduler

'''
这里设计和orleans不一样，orleans使用线程，可以共享grain，但这里进程不行
'''

class Worker(object):
    def __init__(self, worker_id):
        self.worker_id = worker_id
        self.scheduler = ActivationTaskScheduler()

    async def run(self):
        print(f'worker {self.worker_id} started')

def worker_main(worker_id):
    worker = Worker(worker_id)
    asyncio.run(worker.run())

class Silo(object):
    def __init__(self):
        self.num_worker = 4
        self.worker_procs = []
        self.task_queue = Queue()
        self.nethub= NetHub()

    async def run(self):
        for i in range(self.num_worker):
            p = Process(target=worker_main, args=(i,))
            p.start()
        await self.nethub.run()
