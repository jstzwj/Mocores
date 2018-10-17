import socket
import asyncio

class TcpClient(object):
    def __init__(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        self.is_open = False

    async def connect(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        self.reader, self.writer = await asyncio.open_connection(self.ip, self.port)
        self.is_open = True

    def get_writer(self):
        if (self.is_open):
            return self.writer
        else:
            return None

    def get_reader(self):
        if (self.is_open):
            return self.reader
        else:
            return None
            
    async def close(self):
        self.writer.close()
        await self.writer.wait_closed()
        self.is_open = False


