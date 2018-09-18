import sys

sys.path.append("src/")

import mocores.actor

@mocores.actor
class HelloActor(object):
    def __init__(self):
        self.value = 0

    def increment(self):
        self.value += 1
        return self.value