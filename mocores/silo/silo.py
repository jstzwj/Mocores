from multiprocessing import Pool, Process, Queue
import time
import importlib
import sys
import random

import pickle
import asyncio

from mocores.silo.nethub import NetHub
from mocores.silo.scheduler import ThreadTaskScheduler, ActivationTaskScheduler

'''
这里设计和orleans不一样，orleans使用线程，可以共享grain，但这里进程不行
'''
MAX_HASHING = 2**32 - 1

class Worker(object):
    def __init__(self, worker_id, task_queue):
        self.worker_id = worker_id
        self.consistent_hash_value = random.randint(0, MAX_HASHING)
        self.task_queue = task_queue
        self.scheduler = ActivationTaskScheduler()

    async def run(self):
        print(f'worker {self.worker_id} started')

def worker_main(worker_id, task_queue):
    worker = Worker(worker_id, task_queue)
    asyncio.run(worker.run())

class Silo(object):
    def __init__(self):
        self.num_worker = 4
        self.worker_procs = []
        self.task_queue = Queue()
        self.nethub= NetHub(self.task_queue)

    async def run(self):
        for i in range(self.num_worker):
            p = Process(target=worker_main, args=(i, self.task_queue))
            p.start()
        await self.nethub.run()
