import hashlib


class ConsistentHash:
    def __init__(self, replicas_num):
        self.replicas_num = replicas_num
        self.ring = {}
        self.sorted_keys=[]

    def add_node(self, node):
        """Adds a `node` to the hash ring (including a number of replicas).
        """
        for i in range(self.replicas_num):
            key = self.gen_key('%s:%s' % (node, i))
            self.ring[key] = node
            self.sorted_keys.append(key)

        self.sorted_keys.sort()

    def remove_node(self, node):
        """Removes `node` from the hash ring and its replicas.
        """
        for i in range(self.replicas_num):
            key = self.gen_key('%s:%s' % (node, i))
            del self.ring[key]
            self.sorted_keys.remove(key)

    def get_node(self, string_key):
        """Given a string key a corresponding node in the hash ring is returned.

        If the hash ring is empty, `None` is returned.
        """
        return self.get_node_pos(string_key)[0]

    def get_node_pos(self, string_key):
        """Given a string key a corresponding node in the hash ring is returned
        along with it's position in the ring.

        If the hash ring is empty, (`None`, `None`) is returned.
        """
        if not self.ring:
            return None, None

        key = self.gen_key(string_key)

        nodes = self.sorted_keys
        for i in range(len(nodes)):
            node = nodes[i]
            if key <= node:
                return self.ring[node], i

        return self.ring[nodes[0]], 0

    def get_nodes(self, string_key):
        """Given a string key it returns the nodes as a generator that can hold the key.

        The generator is never ending and iterates through the ring
        starting at the correct position.
        """
        if not self.ring:
            yield None, None

        node, pos = self.get_node_pos(string_key)
        for key in self.sorted_keys[pos:]:
            yield self.ring[key]

        while True:
            for key in self.sorted_keys:
                yield self.ring[key]

    def gen_key(self, key):
        """Given a string key it returns a long value,
        this long value represents a place on the hash ring.

        md5 is currently used because it mixes well.
        """
        m = hashlib.md5()
        m.update(key)
        return int(m.hexdigest(), base=16)