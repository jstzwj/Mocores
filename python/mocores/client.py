import mocores.core.actor
import mocores.net.protocol

from twisted.internet import task
from twisted.internet.defer import Deferred
from twisted.internet.protocol import ClientFactory
from twisted.internet.protocol import Protocol, Factory
from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

class ClientProtocol(Protocol):
    def dataReceived(self, data):
        packet_id = int.from_bytes(data[:4], byteorder = 'big')
        packet = mocores.net.protocol.get_packet_by_id(packet_id)
        print(packet)

class Client(object):
    def __init__(self, ip, port):
        print("new client {0}:{1}".format(ip, port))
        self.ip = ip
        self.port = port

    def connect(self, ip, port):
        print("connecting to the cluster: {0}:{1}".format(ip, port))
        f = ClientFactory()
        f.protocol = ClientProtocol
        reactor.connectTCP(ip, port, f)

    def get_actor(self, actor_type, actor_id):
        actor_ref_type = mocores.core.actor.actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__
        return actor_ref_type(actor_class, actor_id)
        