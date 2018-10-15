import inspect


def actor(original_class):
    orig_init = original_class.__init__
    orig_del = original_class.__del__
    # Make copy of original __init__, so we can call it without recursion
    def init_decorator(self, *args, **kws):
        print("decorator init")
        orig_init(self, *args, **kws)

    def del_decorator(self):
        print("decorator del")
        orig_del(self)

    

    original_class.__init__ = init_decorator # Set the class' __init__ to the new one
    original_class.__del__ = del_decorator

    for each_method in inspect.getmembers(original_class, predicate=inspect.isfunction):
        if(each_method[0].startswith('__')):
            continue
        orig_method = getattr(original_class, each_method[0])
        def function_decorator(self, *args, **kws):
            print("decorator each:" + orig_method.__name__)
            orig_method(self, *args, **kws)
        setattr(original_class, each_method[0], function_decorator)
        

    return original_class

