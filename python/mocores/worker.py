import mocores.core.actor
import mocores.net.protocol

from twisted.internet.protocol import Protocol, Factory
from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

class WorkerProtocol(Protocol):
    def connectionMade(self):
        print("New connection comes in: {0}:{1}".format(self.transport.client[0], self.transport.client[1]))
        self.transport.write(b"hello")
 
    def connectionLost(self, reason):
        print("Connection lost:")

    def dataReceived(self, data):
        self.transport.write(data)

class Worker(object):
    def __init__(self, ip, port):
        print("new worker")
        self.ip = ip
        self.port = port


    def run(self):
        print("start server and wait for connection")
        f = Factory()
        f.protocol = WorkerProtocol
        reactor.listenTCP(self.port, f)
        reactor.run()

    def get_actor(self, actor_type, actor_id):
        actor_ref_type = mocores.core.actor.actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__
        return actor_ref_type(actor_class, actor_id)
        