import threading

# actor_id = actor_class + actor_key
class ActorPool(object):
    def __init__(self):
        self.pool = {}
        self.mutex = threading.Lock()

    def has_actor(self, actor_id):
        rst = False
        if self.mutex.acquire():
            rst = actor_id in self.pool
            self.mutex.release()
        return rst

    def put(self, actor_id, actor):
        if self.mutex.acquire():
            self.pool[actor_id] = actor
            self.mutex.release()

    def get(self, actor_id):
        actor = None
        if self.mutex.acquire():
            actor = self.pool[actor_id]
            self.mutex.release()
        return actor