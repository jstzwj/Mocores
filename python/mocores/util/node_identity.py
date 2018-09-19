

class NodeID(object):
    def __init__(self, ip, port, start_time):
        self.ip = ip
        self.port = port
        self.start_time = start_time

    def to_string(self):
        return '{0}:{1}:{2}'.format(
            str(self.ip), 
            str(self.port), 
            str(self.start_time))

    def hash(self):
        id = self.to_string()
        hash = 0
        for c in id:
            hash = hash + ord(c)
            hash = hash % (2^32)
        return hash


def parse_node_id(id):
    info = id.split(':')
    return NodeID(info[0], info[1], info[2])