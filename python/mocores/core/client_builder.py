from mocores.core.runtime.runtime_client import RuntimeClient

class ClientBuilder(object):
    def __init__(self):
        self.ip = "127.0.0.1"
        self.port = 60007
        pass

    def build(self):
        client = RuntimeClient(self.ip, self.port)

        return client
    
    def configure(self, ip, port):
        self.ip = ip
        self.port = port
        pass