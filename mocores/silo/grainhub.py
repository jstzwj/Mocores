
class GrainHub(object):
    def __init__(self):
        self._grains = {}

    def find(self, grain_type, grain_identify):
        com_id = (grain_type, grain_identify)
        return self._grains.get(com_id, None)

    def add(self, grain_type, grain_identify, grain_value):
        com_id = (grain_type, grain_identify)
        self._grains[com_id] = grain_value