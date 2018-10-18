import mocores.net.protocol
import asyncio

# control dispatch
class WorkFlow(object):
    def dispatch_packet(self, worker, packet, writer):
        print("receive packet id:{0}".format(packet.id))
        if(packet.id == 1):
            self.send_pong(worker, packet, writer)
        elif(packet.id == 4):
            self.send_memberships(worker, packet, writer)
        else:
            print("unknown packet:{0}".format(packet.id))


    def send_pong(self, worker, packet, writer):
        header = mocores.net.protocol.PacketHeader(version=1, status=200)
        pong_packet = mocores.net.protocol.Pong()
        raw_packet = header.wrap_packet(pong_packet)
        print("send packet_id:{0}".format(pong_packet.id))
        writer.write(raw_packet)

    def send_memberships(self, worker, packet, writer):
        header = mocores.net.protocol.PacketHeader(version=1, status=200)
        packet = mocores.net.protocol.ReturnMemberShip()
        packet.membership_table = worker.membership_table.table
        raw_packet = header.wrap_packet(packet)
        print("send packet_id:{0}".format(packet.id))
        writer.write(raw_packet)


# control flow
class PacketRouter(object):
    def __init__(self):
        self.work_flow = WorkFlow()

    def dispatch_packet(self, worker, packet, writer):
        self.work_flow.dispatch_packet(worker, packet, writer)

class WorkerProtocol(asyncio.Protocol):
    def __init__(self, router, worker):
        self.router = router
        self.worker = worker

    def connection_made(self, transport):
        self.peername = transport.get_extra_info('peername')
        print('Connection from {}'.format(self.peername))
        self.transport = transport

    def data_received(self, data):
        raw_header = data[:mocores.net.protocol.HEADER_SIZE]
        if(raw_header == b''):
            return
        header = mocores.net.protocol.parse_header(raw_header)
        packet_data = data[mocores.net.protocol.HEADER_SIZE:header.len]

        print("receive packet_id:{0}\tpacket_len:{1}".format(header.id, header.len))
        packet = mocores.net.protocol.get_packet_by_id(header.id)
        packet.deserialize(packet_data)
        self.router.dispatch_packet(self.worker, packet, self.transport)

    def connection_lost(self, exc):
        print('The client{0} exits the connection'.format(self.peername))

class TcpServer(object):
    def __init__(self, ip=None, port=None, worker=None):
        self.ip = ip
        self.port = port
        self.worker = worker
        self.router = PacketRouter()

    async def start_up(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        loop = asyncio.get_event_loop()
        server = await loop.create_server(
            lambda:WorkerProtocol(self.router, self.worker),
            self.ip,
            self.port)

        # Serve requests until Ctrl+C is pressed
        print('Serving on {}'.format(server.sockets[0].getsockname()))
        try:
            waiter = loop.create_future()
            await waiter
            waiter = None
        except KeyboardInterrupt:
            if waiter:
                waiter = None
                waiter.set_result(None)
        # Close the server
        server.close()
