import mocores

@mocores.actor
class MyActor(object):
    def __init__(self):
        print("init")

    def hello_world(self, message=None):
        print(message)
        return 1