import mocores.net.protocol
import asyncio

# control dispatch
class WorkFlow(object):
    async def dispatch_packet(self, worker, packet, writer):
        print("receive packet id:{0}".format(packet.id))
        if(packet.id == 1):
            await self.send_pong(worker, packet, writer)
        elif(packet.id == 4):
            await self.send_memberships(worker, packet, writer)
        else:
            print("unknown packet:{0}".format(packet.id))


    async def send_pong(self, worker, packet, writer):
        header = mocores.net.protocol.PacketHeader(version=1, status=200)
        pong_packet = mocores.net.protocol.Pong()
        raw_packet = header.wrap_packet(pong_packet)
        print("send packet_id:{0}".format(pong_packet.id))
        writer.write(raw_packet)
        await writer.drain()

    async def send_memberships(self, worker, packet, writer):
        header = mocores.net.protocol.PacketHeader(version=1, status=200)
        packet = mocores.net.protocol.ReturnMemberShip()
        packet.membership_table = worker.membership_table.table
        raw_packet = header.wrap_packet(packet)
        print("send packet_id:{0}".format(packet.id))
        writer.write(raw_packet)
        await writer.drain()


# control flow
class PacketRouter(object):
    def __init__(self):
        self.work_flow = WorkFlow()

    async def dispatch_packet(self, worker, packet, writer):
        await self.work_flow.dispatch_packet(worker, packet, writer)

async def data_received(router, worker, reader, writer):
    while(True):
        raw_header = await reader.read(mocores.net.protocol.HEADER_SIZE)
        if(raw_header == b''):
            continue
        header = await mocores.net.protocol.parse_header(raw_header)
        if(header.len!=0):
            packet_data = await reader.read(header.len)
        else:
            packet_data = b''

        print("receive packet_id:{0}\tpacket_len:{1}".format(header.id, header.len))
        packet = mocores.net.protocol.get_packet_by_id(header.id)
        packet.deserialize(packet_data)
        await router.dispatch_packet(worker, packet, writer)

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
        server = await asyncio.start_server(
            lambda reader, writer:data_received(self.router, self.worker, reader, writer),
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
