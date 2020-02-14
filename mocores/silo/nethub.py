import asyncio
import struct
import msgpack
from enum import Enum

'''
packet format
|         header       |  body   |
| version | type | len | payload |
|    2    |   2  |  4  |   ...   |

type
1 -> ping
2 -> pong
3 -> close
4 -> call
5 -> ret

'''
CURRENT_PROTOCOL_VERION = 1
MAX_PACKET_LEN = 409600

class ProtocolType(Enum):
    PING = 1
    PONG = 2
    CLOSE = 3
    CALL = 4
    RET = 5

class ClientSession(object):
    def __init__(self, task_queue, reader, writer):
        self.task_queue = task_queue
        self.reader = reader
        self.writer = writer

    async def start(self):
        while True:
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
            # if close
            if type_data == ProtocolType.CLOSE:
                print(f"Client {addr!r} closed")
                self.writer.close()
                await self.writer.wait_closed()
                break
            
            # enum all type
            if type_data == ProtocolType.PING:
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
            elif type_data == ProtocolType.CALL:
                pass
            elif type_data == ProtocolType.RET:
                pass
            else:
                raise RuntimeError('Unknown packet type.')
                

class NetHub(object):
    def __init__(self, task_queue, ip='0.0.0.0', port=9797):
        self.ip = ip
        self.port = port
        self.task_queue = task_queue

    async def handle_echo(self, reader, writer):
        sess = ClientSession(self.task_queue, reader, writer)
        await sess.start()

    async def run(self):
        server = await asyncio.start_server(
            self.handle_echo, self.ip, self.port)

        addr = server.sockets[0].getsockname()
        print(f'Serving on {addr}')

        async with server:
            await server.serve_forever()
