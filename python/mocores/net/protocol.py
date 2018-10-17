import json

protocol_dist = {}

def protocol(id=0):
    def class_decorator(orig_class):
        orig_class.id = id
        protocol_dist[id] = orig_class
        return orig_class
    return class_decorator

def get_packet_by_id(id):
    return protocol_dist[id]()

def readByte(data):
    return (data[:1], data[1:])

def readInt(data):
    return (int.from_bytes(data[:4], byteorder="big"), data[4:])

def readStr(data):
    len, data = readInt(data)
    return (data[:len].decode(), data[len:])

class PacketHeader(object):
    def __init__(self, version=0, status=0, len=0, id=0):
        self.len = len
        self.id = id
        self.version = version
        self.status = status
    
    @staticmethod
    def wrap_packet(self, packet, version, status):
        buf = bytearray(b'')
        packet_raw_data = packet.serialize()
        self.len = len(packet_raw_data)
        self.id = packet.id
        buf.append(self.len.to_bytes(4, byteorder='big'))
        buf.append(self.id.to_bytes(4, byteorder='big'))
        buf.append(self.version.to_bytes(2, byteorder='big'))
        buf.append(self.status.to_bytes(2, byteorder='big'))

class Message(object):
    def serialize(self):
        pass

    def deserialize(self, buf):
        pass

@protocol(id=1)
class Ping(Message):
    def serialize(self):
        buf = bytearray(b'')
        buf.append(self.id.to_bytes(4, byteorder='big'))
        return buf

    def deserialize(self, data):
        self.id = int.from_bytes(data, byteorder='big')

@protocol(id=2)
class Pong(Message):
    def serialize(self):
        buf = bytearray(b'')
        buf.append(self.id.to_bytes(4, byteorder='big'))
        return buf

    def deserialize(self, data):
        self.id = int.from_bytes(data, byteorder='big')

@protocol(id=3)
class MemberShip(Message):
    def serialize(self):
        buf = bytearray(b'')
        buf.append(self.id.to_bytes(4, byteorder='big'))
        return buf

    def deserialize(self, data):
        self.id = int.from_bytes(data, byteorder='big')
