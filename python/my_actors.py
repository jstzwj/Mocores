import mocores

@mocores.actor
class MyActor(object):
    def __init__(self):
        print("init")

    async def hello_world(self, message=None):
        print(message)
        return 1

    def plain_hello(self, message = None):
        print(message)
        return 0