import socket
import asyncio
import mocores.net.protocol

class TcpClient(object):
    def __init__(self, ip=None, port=None):
        self.ip = ip
        self.port = port
        self.is_open = False
        self._waiter = None

    async def connect(self, ip=None, port=None):
        if(ip!=None):
            self.ip = ip
        if(port!=None):
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
        self._wakeup_waiter()
        self.writer.close()
        await self.writer.wait_closed()
        self.is_open = False

    async def wait_for_data(self):
        loop = asyncio.get_event_loop()
        self._waiter = loop.create_future()
        await self._waiter
        self._waiter = None

    def _wakeup_waiter(self):
        waiter = self._waiter
        if waiter:
            self._waiter = None
            waiter.set_result(None)

class ClientSession(object):
    def __init__(self, ip=None, port=None):
        self.client = TcpClient(ip=ip, port=port)

    async def active(self):
        if(not self.client.is_open):
            await self.client.connect()

    async def ping(self):
        await self.active()
        writer = self.client.get_writer()
        header = mocores.net.protocol.PacketHeader(version=1, status=200)
        ping_packet = mocores.net.protocol.Ping()
        raw_packet = header.wrap_packet(ping_packet)
        writer.write(raw_packet)
        await writer.drain()


