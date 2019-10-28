from concurrent import futures
import time
import importlib

import pickle
import grpc

from mocores.contrib.protocol_pb2 import CallRequest, CallReply
from mocores.contrib.protocol_pb2_grpc import CallServicer, add_CallServicer_to_server

_ONE_DAY_IN_SECONDS = 60 * 60 * 24


class Caller(CallServicer):
	# 工作函数
    def Call(self, request, context):
        module = importlib.import_module(request.module_name)
        actor_class = getattr(module, request.class_name)()
        method = getattr(actor_class, request.method_name)

        params = pickle.loads(request.params)
        ret = method(*params)

        return CallReply(state=0,ret=pickle.dumps(ret))


class Silo(object):
    def __init__(self):
        pass

    def run(self):
        # gRPC 服务器
        server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        add_CallServicer_to_server(Caller(), server)
        server.add_insecure_port('[::]:50051')
        server.start()  # start() 不会阻塞，如果运行时你的代码没有其它的事情可做，你可能需要循环等待。
        try:
            while True:
                time.sleep(_ONE_DAY_IN_SECONDS)
        except KeyboardInterrupt:
            server.stop(0)