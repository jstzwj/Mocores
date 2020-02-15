import inspect

class IGrain(object):
    _funcs = {}
    _storage_provider = None
    def __init__(self):
        pass
    def add_method(self, func):
        if not inspect.iscoroutinefunction(func):
            raise RuntimeError('The object is not a coroutine function.')
        if func.__name__ not in self._funcs:
            self._funcs[func.__name__] = func

class Grain(object):
    def __init__(self):
        pass

    def __call__(self, obj):
        
        def wrapper(*args, **kwargs):
            print("__call__", self.name)
            func(*args, **kwargs)
            
        return wrapper
