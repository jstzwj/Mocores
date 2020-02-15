import pymysql

from mocores.common.provider import StorageProvider

class MysqlStorageProvider(StorageProvider):
    def __init__(self, host='localhost', user='root', password='', db='mocores'):
        self.host = host
        self.user = user
        self.password = password
        self.db = db

    def Init(self, name):
        self.connection = pymysql.connect(
                            host=self.host,
                            user=self.user,
                            password=self.password,
                            db=self.db)

    def Close(self, name):
        self.connection.close()

    def CheckTable(self, tablename):
        check_table = f'create table if not exists {tablename} (`grain_id` VARCHAR(128) primary key, `grain_value` TEXT)'
        with self.connection.cursor() as cursor:
            cursor.execute(check_table)
        self.connection.commit()

    async def ReadStateAsync(self, grainType:str, grainRef, grainState):
        self.CheckTable(grainType)
        read_sql = f'SELECT grain_value FROM {grainType} WHERE grain_id==%s'
        with self.connection.cursor() as cursor:
            cursor.execute(read_sql, grainRef.key)
            result = cursor.fetchone()
            print(result)

    async def WriteStateAsync(self, grainType:str, grainRef, grainState):
        self.CheckTable(grainType)

    async def ClearStateAsync(self, grainType:str, grainRef, grainState):
        self.CheckTable(grainType)