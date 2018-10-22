from mocores.core.runtime.runtime_client import RuntimeClient

class ClientBuilder(object):
    def __init__(self):
        pass

    def build(self):
        client = RuntimeClient()

        return client
    
    def configure(self):
        pass