import asyncio
import struct
import msgpack
from enum import Enum
from mocores.silo.silo_identity import SiloIdentity

'''
packet format
|         header       |  body   |
| version | type | len | payload |
|    2    |   2  |  4  |   ...   |

type
1 -> ping
2 -> pong
3 -> close
4 -> handshake
5 -> call
6 -> ret

'''
CURRENT_PROTOCOL_VERION = 1
MAX_PACKET_LEN = 409600

class ProtocolType(Enum):
    PING = 1
    PONG = 2
    CLOSE = 3
    HANDSHAKE = 4
    CALL = 5
    RET = 6

class StateType(Enum):
    OPEN = 1
    HANDSHAKE = 2
    WORK = 3
    CLOSE = 4

class ClientSession(object):
    def __init__(self, nethub, reader, writer):
        self.nethub = nethub
        self.reader = reader
        self.writer = writer
        self.state = StateType.OPEN

    async def start(self):
        while True:
            asyncio.create_task(self.dispatch_packet())
            if self.state == StateType.CLOSE:
                break

    async def dispatch_packet(self):
        header_data = await self.reader.readexactly(8)
        version_data = struct.unpack('!H', header_data[:2])
        type_data = struct.unpack('!H', header_data[2:4])
        len_data = struct.unpack('!I', header_data[4:])
        # check some conds
        if version_data != CURRENT_PROTOCOL_VERION:
            raise RuntimeError('Some clients sent data in different version format.')
        if len_data > MAX_PACKET_LEN:
            raise RuntimeError('Some clients sent data too long!')
        
        # read body
        body_data = None
        if len_data > 0:
            body_data = await self.reader.readexactly(len_data)

        # log
        addr = self.writer.get_extra_info('peername')
        print(f"Received {len_data!r} length from {addr!r}")
        # enum all type
        if type_data == ProtocolType.CLOSE:
            print(f"Client {addr!r} closed")
            self.state = StateType.CLOSE
            self.writer.close()
            await self.writer.wait_closed()
        elif type_data == ProtocolType.PING:
            ping_num = b''
            if body_data is not None:
                ping_num = msgpack.unpackb(body_data, raw=False)
            packed_header = bytearray(struct.pack('!HHI', CURRENT_PROTOCOL_VERION, ProtocolType.PONG, len(ping_num)))
            packed_body = bytearray(ping_num)
            packed_data = packed_header + packed_body
            self.writer.write(packed_data)
            await self.writer.drain()
        elif type_data == ProtocolType.PONG:
            print('pong ok')
        elif type_data == ProtocolType.HANDSHAKE:
            if body_data is None:
                raise RuntimeError('Handshaking body no found')
            if self.state != StateType.OPEN:
                raise RuntimeError('State is not correct')
            self.state = StateType.HANDSHAKE
            client_endpoint = msgpack.unpackb(body_data, raw=False)
            self.nethub.sessions[client_endpoint] = self
        elif type_data == ProtocolType.CALL:
            if body_data is None:
                raise RuntimeError('Call body no found')
            if self.state != StateType.HANDSHAKE or self.state != StateType.WORK:
                raise RuntimeError('State is not correct')
            if self.state == StateType.HANDSHAKE:
                self.state = StateType.WORK

        elif type_data == ProtocolType.RET:
            if body_data is None:
                raise RuntimeError('Call body no found')
            if self.state != StateType.HANDSHAKE or self.state != StateType.WORK:
                raise RuntimeError('State is not correct')
            if self.state == StateType.HANDSHAKE:
                self.state = StateType.WORK
            
        else:
            raise RuntimeError('Unknown packet type.')

    async def handshake_state(self, body):
        pass

    async def work_state(self, body):
        pass
                

class NetHub(object):
    def __init__(self, task_queue, ip='0.0.0.0', port=9797):
        self.ip = ip
        self.port = port
        self.task_queue = task_queue
        self.sessions = {}

    async def handle_echo(self, reader, writer):
        sess = ClientSession(self, reader, writer)
        await sess.start()

    async def run(self):
        server = await asyncio.start_server(
            self.handle_echo, self.ip, self.port)

        addr = server.sockets[0].getsockname()
        print(f'Serving on {addr}')

        async with server:
            await server.serve_forever()
