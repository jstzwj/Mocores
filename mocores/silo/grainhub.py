
class GrainHub(object):
    def __init__(self):
        self._grains = {}

    def find(self, grain_type, grain_identify, grain_component):
        com_id = (grain_type, grain_identify, grain_component)
        return self._grains.get(com_id, None)

    def add(self, grain_type, grain_identify, grain_component, grain_value):
        com_id = (grain_type, grain_identify, grain_component)
        self._grains[com_id] = grain_value