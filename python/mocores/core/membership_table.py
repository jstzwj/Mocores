

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
        self.table = []

    def add_entry(self, worker_id):
        self.table.append(MembershipEntry(worker_id.ip, worker_id.port, worker_id.start_time))

    def remove_entry(self, worker_id):
        for i in range(len(self.table)):
            if(self.table[i].ip == worker_id.ip and
                self.table[i].port == worker_id.port and
                self.table[i].start_time == worker_id.start_time):
                del self.table[i]
                break
