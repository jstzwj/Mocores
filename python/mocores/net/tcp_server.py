import mocores.net.protocol
import asyncio

class WorkerProtocol(asyncio.Protocol):
    def connection_made(self, transport):
        peername = transport.get_extra_info('peername')
        print('Connection from {}'.format(peername))
        self.transport = transport

    def data_received(self, data):
        packet_id = int.from_bytes(data[:4], byteorder = 'big')
        packet = mocores.net.protocol.get_packet_by_id(packet_id)
        print(packet)

        message = data.decode()
        print('Data received: {!r}'.format(message))

        print('Send: {!r}'.format(message))
        self.transport.write(data)

        print('Close the client socket')
        self.transport.close()
        

class TcpServer(object):
    def __init__(self, ip=None, port=None):
        self.ip = ip
        self.port = port

    async def start_up(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        server = await asyncio.start_server(lambda: WorkerProtocol(), self.ip, self.port)

        addr = server.sockets[0].getsockname()
        print(f'Serving on {addr}')

        async with server:
            await server.serve_forever()
