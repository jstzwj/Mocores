import mocores.core.actor
import mocores.net.protocol
import mocores.net.tcp_server

class Worker(object):
    def __init__(self, ip, port):
        print("new worker")
        self.ip = ip
        self.port = port


    def run(self):
        print("start server and wait for connection")
        tcp_server = mocores.net.tcp_server.TcpServer()
        tcp_server.listen(self.port)

    def get_actor(self, actor_type, actor_id):
        actor_ref_type = mocores.core.actor.actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__
        return actor_ref_type(actor_class, actor_id)
        