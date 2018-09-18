import socket

class NodeClient(object):
    def __init__(self, ip, port):
        self._ip = ip
        self._port = port

    def connect(self):
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._sock.connect((self._ip, self._port))

    def disconnect(self, sock):
        self._sock.close()

    def send(self, data):
        self._sock.send(data)