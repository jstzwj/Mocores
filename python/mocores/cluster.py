import inspect


def register_actor(actor):
    if inspect.isclass(actor):
        return worker.make_actor(actor, checkpoint_interval)

def actor(*args, **kwargs):
    return register_actor(args[0])


class ActorRef(object):
    def __init__(self, class_name, key):
        self._class_name = class_name
        self._key = key

class Actor(object):
    def __init__(self, class_name, checkpoint_interval):
        self._class_name = Actor.__name__
        self._checkpoint_interval = checkpoint_interval

    def on_active(self):
        pass

    def on_inactive(self):
        pass

