

from mocores.client.nethub import NetHub

class Client(object):
    def __init__(self, storage_provider=None, localhost_cluster=True):
        self.storage_provider = storage_provider
        self.localhost_cluster = localhost_cluster
        self.nethub = NetHub()
    async def connect(self):
        if self.localhost_cluster:
            await self.nethub.connect('localhost', 9797)
        else:
            pass