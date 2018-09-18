


class ActorRef(object):
    def __init__(self, class_id, key):
        self._class_id = class_id
        self._key = key

class Actor(object):
    def __init__(self, class_id, checkpoint_interval):
        self._class_id = class_id
        self._class_name = Actor.__name__
        self._checkpoint_interval = checkpoint_interval

