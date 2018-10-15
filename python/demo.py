import mocores

@mocores.actor
class MyActor(object):
    def __init__(self):
        print("init")

    def hello_word(self):
        print('hello world')

    def __del__(self):
        print("del")

my_actor = MyActor()
my_actor.hello_word()