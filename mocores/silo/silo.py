from multiprocessing import Pool, Process, Queue, Pipe
import time
import importlib
import sys
import random

import pickle
import asyncio
from enum import Enum
import socket

from mocores.silo.grainhub import GrainHub
from mocores.silo.nethub import NetHub
from mocores.silo.nettrans import NetTrans
from mocores.silo.scheduler import ThreadTaskScheduler, ActivationTaskScheduler, Task
from mocores.silo.silo_identity import SiloIdentity

'''
这里设计和orleans不一样，orleans使用线程，可以共享grain，但这里进程不行
'''
MAX_HASHING = 2**32 - 1

class WorkerMessageType(Enum):
    REQUEST = 1
    RESPONSE = 2
    CLOSE = 3

class Worker(object):
    def __init__(self, worker_id, task_pipe):
        self.worker_id = worker_id
        self.task_pipe = task_pipe
        self.scheduler = ActivationTaskScheduler()
        self.grains = GrainHub()

    async def run(self):
        print(f'worker {self.worker_id} started')
        while True:
            msg_type, msg = self.task_pipe.recv()
            if msg_type == WorkerMessageType.CLOSE:
                break
            elif msg_type == WorkerMessageType.REQUEST:
                if type(msg) != Task:
                    raise RuntimeError('Wrong message body type.')
                cur_grain = self.grains.find(msg.grain_type, msg.grain_identify)
                retval = await getattr(cur_grain, msg.grain_method)()

            else:
                raise RuntimeError('Unsupported message type.')

        print(f'worker {self.worker_id} stopped')


def worker_main(worker_id, task_pipe):
    worker = Worker(worker_id, task_pipe)
    asyncio.run(worker.run())

class Silo(object):
    def __init__(self):
        self.num_worker = 4
        self.worker_procs = []
        self.task_pipelines = []
        self.nethub= NetHub(self.task_pipelines)
        self.nettrans = NetTrans()
        ip = socket.gethostbyname(socket.gethostname())
        port = 9797
        epoch = time.time()
        self.identity = SiloIdentity(ip, port, epoch)

    async def run(self):
        # start all workers
        for i in range(self.num_worker):
            pipe_source, pipe_to = Pipe()
            p = Process(target=worker_main, args=(i, pipe_to))
            self.worker_procs.append(p)
            self.task_pipelines.append(pipe_source)
            p.start()
        # start network
        await self.nethub.run()
        # join all workers
        for i in range(self.num_worker):
            self.worker_procs[i].join()
