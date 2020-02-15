

class SiloIdentity(object):
    ip = None
    port = None
    epoch = None # Epoch is just time in ticks when this silo started
    def __init__(self, ip, port, epoch):
        pass

    def get_str(self):
        return f'{str(self.ip)}:{str(self.port)}:{str(self.epoch)}'

    def get_endpoint(self):
        return f'{str(self.ip)}:{str(self.port)}'