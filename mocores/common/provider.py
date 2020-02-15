

class PersistentState(object):
    async def ClearStateAsync(self):
        pass
    async def WriteStateAsync(self):
        pass
    async def ReadStateAsync(self):
        pass

class StorageProvider(object):
    def __init__(self):
        pass

    def Init(self, name):
        raise NotImplementedError("Init in IStorageProvider not implemented")

    def Close(self, name):
        raise NotImplementedError("Close in IStorageProvider not implemented")

    async def ReadStateAsync(self, grainType:str, grainRef, grainState):
        raise NotImplementedError("ReadStateAsync in IStorageProvider not implemented")

    async def WriteStateAsync(self, grainType:str, grainRef, grainState):
        raise NotImplementedError("WriteStateAsync in IStorageProvider not implemented")

    async def ClearStateAsync(self, grainType:str, grainRef, grainState):
        raise NotImplementedError("ClearStateAsync in IStorageProvider not implemented")
    