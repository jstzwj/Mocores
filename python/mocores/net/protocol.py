import json

class Message(object):
    def serialize(self):
        pass

    def deserialize(self, str):
        pass

class HeartBeat(Message):
    def __init__(self):
        self._id = 1
        self._check_num = 0

    def serialize(self):
        return {'id': self._id,
            'check_sum': self._check_num}

    def deserialize(self, dict):
        self._id = dict['id']
        self._check_num = dict['check_num']
