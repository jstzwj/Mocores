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

class Message(object):
    def serialize(self):
        pass

    def deserialize(self, buf):
        pass

@protocol(id=1)
class HeartBeat(Message):
    def __init__(self):
        pass

    def serialize(self):
        buf = bytearray(b'')
        buf.append(self.id.to_bytes(4, byteorder='big'))
        return buf

    def deserialize(self, data):
        self.id = int.from_bytes(data, byteorder='big')

@protocol(id=2)
class MemberShip(Message):
    def __init__(self):
        pass

    def serialize(self):
        buf = bytearray(b'')
        buf.append(self.id.to_bytes(4, byteorder='big'))
        return buf

    def deserialize(self, data):
        self.id = int.from_bytes(data, byteorder='big')
