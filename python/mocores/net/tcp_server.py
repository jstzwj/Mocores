import mocores.net.protocol
import asyncio

# control dispatch
class WorkFlow(object):
    async def dispatch_packet(self, packet, writer):
        if(packet.id == 1):
            await self.send_pong(packet, writer)
        else:
            print("unknown packet")


    async def send_pong(self, packet, writer):
        header = mocores.net.protocol.PacketHeader(version=1, status=200)
        pong_packet = mocores.net.protocol.Pong()
        raw_packet = header.wrap_packet(pong_packet)
        writer.write(raw_packet)
        await writer.drain()


# control flow
class PacketRouter(object):
    def __init__(self):
        self.work_flow = WorkFlow()

    async def dispatch_packet(self, packet, writer):
        await self.work_flow.dispatch_packet(packet, writer)

async def data_received(router, reader, writer):
    header = await mocores.net.protocol.parse_header(reader)
    if(header.len!=0):
        packet_data = await reader.read(header.len)
    else:
        packet_data = b''

    packet = mocores.net.protocol.get_packet_by_id(header.id)
    packet.deserialize(packet_data)
    print("packet_id:{0}\tpacket_len:{1}".format(header.id, header.len))

    await router.dispatch_packet(packet, writer)
    

class TcpServer(object):
    def __init__(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        self.router = PacketRouter()

    async def start_up(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        loop = asyncio.get_event_loop()
        server = await asyncio.start_server(
            lambda reader, writer:data_received(self.router, reader, writer),
            self.ip,
            self.port)

        # Serve requests until Ctrl+C is pressed
        print('Serving on {}'.format(server.sockets[0].getsockname()))
        try:
            self._waiter = loop.create_future()
            await self._waiter
            self._waiter = None
        except KeyboardInterrupt:
            waiter = self._waiter
            if waiter:
                self._waiter = None
                waiter.set_result(None)

        # Close the server
        server.close()
