#!coding:utf8
 
import collections
 
class LRU(object):
    def __init__(self, size=5):
        self.size = size
        self.cache = collections.OrderedDict()
     
    def get(self,key):
        if key in self.cache:
            value = self.cache.pop(key)
            self.cache[key] = value
            return value
        else:
            value = None
            return value
    def set(self,key, value):
        if key in self.cache:
            self.cache.pop(key)
            self.cache[key] = value
        elif self.size == len(self.cache):
            self.cache.popitem(last = False)
            self.cache[key] = value
        else:
            self.cache[key] = value