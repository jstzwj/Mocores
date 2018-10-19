import json
from mocores.core.membership_table import(MembershipTable, MembershipTableEntry)

protocol_dist = {}
HEADER_SIZE = 12

def protocol(id=0):
    def class_decorator(orig_class):
        orig_class.id = id
        protocol_dist[id] = orig_class
        return orig_class
    return class_decorator

def get_packet_by_id(id):
    return protocol_dist[id]()

def writeByte(data, val):
    data.append(val)

def writeInt16(data, val):
    data += val.to_bytes(2,byteorder='big')

def writeInt32(data, val):
    data += val.to_bytes(4,byteorder='big')

def writeInt64(data, val):
    data += val.to_bytes(8,byteorder='big')

def writeInt(data, val):
    data += val.to_bytes(4,byteorder='big')

def writeStr(data, val):
    raw_str = val.encode()
    writeInt(data, len(raw_str))
    data += raw_str

def readByte(data):
    return (data[:1], data[1:])

def readInt(data):
    return (int.from_bytes(data[:4], byteorder="big"), data[4:])

def readInt16(data):
    return (int.from_bytes(data[:2], byteorder="big"), data[2:])

def readInt32(data):
    return (int.from_bytes(data[:4], byteorder="big"), data[4:])

def readInt64(data):
    return (int.from_bytes(data[:8], byteorder="big"), data[8:])

def readStr(data):
    len, data = readInt(data)
    return (data[:len].decode(), data[len:])

class PacketHeader(object):
    def __init__(self, version=0, status=0, len=0, id=0):
        self.len = len
        self.id = id
        self.version = version
        self.status = status
    
    def wrap_packet(self, packet):
        buf = bytearray(b'')
        packet_raw_data = packet.serialize()
        self.len = len(packet_raw_data)
        self.id = packet.id
        
        # add packet header
        buf += self.len.to_bytes(4, byteorder='big')
        buf += self.id.to_bytes(4, byteorder='big')
        buf += self.version.to_bytes(2, byteorder='big')
        buf += self.status.to_bytes(2, byteorder='big')

        # add packet body
        buf += packet_raw_data
        return buf

def parse_header(data):
    header = PacketHeader()
    header.len = int.from_bytes(data[0:4], byteorder = 'big')
    header.id = int.from_bytes(data[4:8], byteorder = 'big')
    header.version = int.from_bytes(data[8:10], byteorder = 'big')
    header.status = int.from_bytes(data[8:12], byteorder = 'big')

    return header

async def parse_packet(reader):
    raw_header = await reader.read(HEADER_SIZE)
    header = parse_header(raw_header)
    print("income packet len:{0}, id{1}".format(header.len, header.id))
    if(header.len!=0):
        packet_data = await reader.read(header.len)
    else:
        packet_data = b''

    packet = get_packet_by_id(header.id)
    packet.deserialize(packet_data)
    return packet

class Message(object):
    def serialize(self):
        pass

    def deserialize(self, buf):
        pass

@protocol(id=1)
class Ping(Message):
    def serialize(self):
        buf = bytearray(b'')
        return buf

    def deserialize(self, data):
        pass

@protocol(id=2)
class Pong(Message):
    def serialize(self):
        buf = bytearray(b'')
        return buf

    def deserialize(self, data):
        pass

@protocol(id=3)
class Ack(Message):
    def serialize(self):
        buf = bytearray(b'')
        return buf

    def deserialize(self, data):
        pass

@protocol(id=4)
class RequestMemberShip(Message):
    def serialize(self):
        buf = bytearray(b'')
        return buf

    def deserialize(self, data):
        pass


@protocol(id=5)
class ReturnMemberShip(Message):
    def __init__(self):
        self.membership_table = []
    def serialize(self):
        buf = bytearray(b'')
        writeInt32(buf, len(self.membership_table))
        for entry in self.membership_table:
            writeStr(buf, entry.ip)
            writeInt16(buf, entry.port)
            writeStr(buf, entry.start_time)
        return buf

    def deserialize(self, data):
        table_len, data = readInt32(data)
        i = 0
        while i < table_len:
            ip, data = readStr(data)
            port, data = readInt16(data)
            start_time, data = readStr(data)
            self.membership_table.append(MembershipTableEntry(ip, port, start_time))
            i = i + 1

@protocol(id=6)
class AddMember(Message):
    def serialize(self):
        buf = bytearray(b'')
        return buf

    def deserialize(self, data):
        pass

@protocol(id=7)
class RemoveMember(Message):
    def serialize(self):
        buf = bytearray(b'')
        return buf

    def deserialize(self, data):
        pass

@protocol(id=8)
class RefreshMemberShip(Message):
    def serialize(self):
        buf = bytearray(b'')
        return buf

    def deserialize(self, data):
        pass