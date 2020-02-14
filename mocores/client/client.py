

class Client(object):
    def __init__(self, ip='127.0.0.1', port=9797):
        self.ip = ip
        self.port = port

    async def connect(self):
        pass