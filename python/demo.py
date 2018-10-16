import mocores

@mocores.actor
class MyActor(object):
    def __init__(self):
        print("init")

    def hello_world(self, message=None):
        print(message)

    def __del__(self):
        print("del")

my_actor = mocores.get_actor(MyActor, 1)
new_actor = MyActor()
# my_actor.hello_world(message="hello world")