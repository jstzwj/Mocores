import mocores.core.actor
import mocores.net.protocol
import mocores.net.tcp_client

class Client(object):
    def __init__(self, ip, port):
        print("new client {0}:{1}".format(ip, port))
        self.ip = ip
        self.port = port

    async def connect(self, ip, port):
        print("connecting to the cluster: {0}:{1}".format(ip, port))
        # connect and get membership table
        master_session = mocores.net.tcp_client.ClientSession(ip, port)
        await master_session.ping()
        # ping and get actor table

    def get_actor(self, actor_type, actor_id):
        actor_ref_type = mocores.core.actor.actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__
        return actor_ref_type(actor_class, actor_id)
        