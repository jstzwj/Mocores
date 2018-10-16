import inspect
import copy
import pyarrow


# generate actor ref
def actor_ref(original_class):
    # copy members to dict
    orig_members_list = inspect.getmembers(original_class)
    orig_members_dict = {}
    for each_item in orig_members_list:
        orig_members_dict[each_item[0]] = each_item[1]
    
    # create new ref type
    new_class = type(original_class.__name__ + '_ref', (object,), orig_members_dict)
    orig_init = new_class.__init__
    orig_del = new_class.__del__
    # Make copy of original __init__, so we can call it without recursion
    def init_decorator(self, actor_class=None, actor_id=None, *args, **kws):
        print("actor_class:" + actor_class)
        print("actor_id:" + str(actor_id))

    def del_decorator(self):
        print("decorator del")

    new_class.__init__ = init_decorator # Set the class' __init__ to the new one
    new_class.__del__ = del_decorator

    for each_method in inspect.getmembers(new_class, predicate=inspect.isfunction):
        if(each_method[0].startswith('__')):
            continue
        orig_method = getattr(new_class, each_method[0])
        def function_decorator(self, *args, **kws):
            # serialize args
            args_buf = pyarrow.serialize(args).to_buffer()
            aws_buf = pyarrow.serialize(kws).to_buffer()
            print(pyarrow.deserialize(args_buf))
            print(pyarrow.deserialize(aws_buf))
            print("decorator each:" + orig_method.__name__)

        setattr(new_class, each_method[0], function_decorator)
        

    return new_class


# decorate actor
def actor(original_class):
    orig_init = original_class.__init__
    orig_del = original_class.__del__
    # Make copy of original __init__, so we can call it without recursion
    def init_decorator(self, *args, **kws):
        orig_init(self, *args, **kws)

    def del_decorator(self):
        orig_del(self)

    original_class.__init__ = init_decorator # Set the class' __init__ to the new one
    original_class.__del__ = del_decorator

    for each_method in inspect.getmembers(original_class, predicate=inspect.isfunction):
        if(each_method[0].startswith('__')):
            continue
        orig_method = getattr(original_class, each_method[0])
        def function_decorator(self, *args, **kws):
            orig_method(self, *args, **kws)
        setattr(original_class, each_method[0], function_decorator)

    return original_class



def get_actor(actor_type, actor_id):
    actor_ref_type = actor_ref(actor_type)
    actor_class = actor_type.__module__ + "." + actor_type.__name__
    return actor_ref_type(actor_class, actor_id)