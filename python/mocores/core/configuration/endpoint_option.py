

class EndpointOption(object):
    def __init__(self):
        self.ip = None
        self.DEAFULT_CLUSTER_PORT = 13579
        self.DEAFULT_CLIENT_PORT = 30000
        self.cluster_port = self.DEAFULT_CLUSTER_PORT
        self.client_port = self.DEAFULT_CLIENT_PORT
