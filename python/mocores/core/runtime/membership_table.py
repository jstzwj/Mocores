import mocores.core.runtime

class MembershipTableEntry(object):
    def __init__(self, cluster_id, ip, port, start_time, primary):
        self.cluster_id = cluster_id
        self.ip = ip
        self.port = port
        self.start_time = start_time
        self.primary = primary
        self.status = mocores.core.runtime.WorkerStatus.Null
        self.report_alive_time = ""
        self.suspecting_workers = []
        self.suspecting_time = []

    def to_string(self):
        return '{0}:{1}:{2}'.format(
            str(self.ip), 
            str(self.port), 
            str(self.start_time))


class MembershipTable(object):
    def __init__(self):
        self.table = []

    def add_entry(self, entry):
        self.table.append(entry)

    def remove_entry(self, worker_id):
        for i in range(len(self.table)):
            if(self.table[i].ip == worker_id.ip and
                self.table[i].port == worker_id.port and
                self.table[i].start_time == worker_id.start_time):
                del self.table[i]
                break
