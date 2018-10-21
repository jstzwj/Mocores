import mocores.core.util
import socket

class SocketManager:
    def __init_(self):
        self.cache = mocores.core.util.LRU(15)
    
    def create_accepting_socket(self, address, port):
        pass

    def create_sending_socket(self, address, port):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            s.connect((address, port))
        except:
            print("connection error")
