import mocores.core.actor

class Client(object):
    def __init__(self, ip, port):
        print("new client")

    def connect(self, ip, port):
        print("connecting to the cluster")

    def get_actor(self, actor_type, actor_id):
        actor_ref_type = mocores.core.actor.actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__
        return actor_ref_type(actor_class, actor_id)
        