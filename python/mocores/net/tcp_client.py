import asyncore

class TcpClient(asyncore.dispatcher):
    def __init__(self, host, port, path):
        asyncore.dispatcher.__init__(self)
        self.create_socket()
        self.connect( (host, port) )
        self.buffer = bytes('', 'ascii')

    def handle_connect(self):
        pass

    def handle_close(self):
        self.close()

    def handle_read(self):
        print(self.recv(8192))

    def writable(self):
        return (len(self.buffer) > 0)

    def handle_write(self):
        sent = self.send(self.buffer)
        self.buffer = self.buffer[sent:]


client = TcpClient('www.python.org', 25566, '/')
asyncore.loop()