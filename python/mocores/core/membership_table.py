

class MembershipEntry(object):
    def __init__(self, ip, port, start_time):
        self.ip = ip
        self.port = port
        self.start_time = start_time
        self.is_dead = False

    def to_string(self):
        return '{0}:{1}:{2}'.format(
            str(self.ip), 
            str(self.port), 
            str(self.start_time))


class MembershipTable(object):
    def __init__(self):
        self.table = {}

    def add_entry(self, entry):
        self.table[entry.to_string()] = entry

    def remove_entry(self, entry):
        del self.table[entry.to_string()]
