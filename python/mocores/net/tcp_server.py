import mocores.net.protocol
import asyncio

async def parse_header(reader):
    header = mocores.net.protocol.PacketHeader()
    header.len = await reader.read(4)
    header.len = int.from_bytes(header.len, byteorder = 'big')

    header.id = await reader.read(4)
    header.id = int.from_bytes(header.id, byteorder = 'big')

    header.version = await reader.read(2)
    header.version = int.from_bytes(header.version, byteorder = 'big')

    header.status = await reader.read(2)
    header.status = int.from_bytes(header.status, byteorder = 'big')

    return header

async def data_received(reader, writer):
    header = await parse_header(reader)
    packet_data = await reader.read(header.len)

    packet = mocores.net.protocol.get_packet_by_id(header.id)
    packet.deserialize(packet_data)
    print("packet_id:{0}\npacket_len:{1}".format(header.id, header.len))
    

class TcpServer(object):
    def __init__(self, ip=None, port=None):
        self.ip = ip
        self.port = port

    async def start_up(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        loop = asyncio.get_event_loop()
        server = await asyncio.start_server(data_received, self.ip, self.port)

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
