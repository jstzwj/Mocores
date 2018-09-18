
import mocores.actor

class Client(object):
    def __init__(self):
        print("new client")

    def connect(self):
        print("connecting to the cluster")

    def get_actor(self, class_name, key):
        print("return actor ref \n name:{0}\n key:{1}", class_name, key)
        

def build():
    print("building")
    return Client()


def connect():
    print("connecting")