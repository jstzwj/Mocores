import mocores.net.protocol

from twisted.internet.protocol import Protocol, Factory
from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

class WorkerProtocol(Protocol):
    def connectionMade(self):
        print("New connection comes in: {0}:{1}".format(self.transport.client[0], self.transport.client[1]))
 
    def connectionLost(self, reason):
        print("Connection lost:")

    def dataReceived(self, data):
        packet_id = int.from_bytes(data[:4], byteorder = 'big')
        packet = mocores.net.protocol.get_packet_by_id(packet_id)
        print(packet)

class TcpServer(object):
    def __init__(self):
        pass

    def listen(self, port):
        f = Factory()
        f.protocol = WorkerProtocol
        reactor.listenTCP(port, f)
        reactor.run()
