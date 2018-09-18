

def get_node_id(ip, port, start_time):
    return '{0}:{1}:{2}'.format(
            str(ip), 
            str(port), 
            str(start_time))

def get_node_info_by_id(id):
    info = id.split(':')
    return info[0], info[1], info[2]

def get_node_id_hash(id):
    hash = 0
    for(c in id):
        hash += ord(c)
        hash %= 65536
    return hash