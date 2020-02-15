
import asyncio


class ClientSession(object):
    def __init__(self, nethub, reader, writer):
        self.nethub = nethub
        self.reader = reader
        self.writer = writer

    async def start(self):
        
        print('Close the connection')
        self.writer.close()

class NetHub(object):
    def __init__(self):
        self.sessions = {}

    async def connect(self, ip, port):
        reader, writer = await asyncio.open_connection(ip, port)
        session = ClientSession(self, reader, writer)
        endpoint = f'{str(ip)}:{str(port)}'
        self.sessions[endpoint] = session
        await session.start()
