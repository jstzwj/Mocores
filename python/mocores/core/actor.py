import inspect
import time
import datetime
import asyncio
import pyarrow
import mocores.core.work_item as work_item
import mocores.core.task as task


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
        self.actor_class = actor_class
        self.actor_id = actor_id

    def del_decorator(self):
        print("decorator del")

    new_class.__init__ = init_decorator # Set the class' __init__ to the new one
    new_class.__del__ = del_decorator

    for each_method in inspect.getmembers(new_class, predicate=inspect.isfunction):
        if(each_method[0].startswith('__')):
            continue
        orig_method = getattr(new_class, each_method[0])
        async def function_decorator(self, *args, **kws):
            # construct work_item
            invoke_work_item = work_item.InvokeWorkItem(self.actor_class, self.actor_id,
                each_method[0], args, kws)

            
            # search actor table

            # construct task

            # send task
            cur_time = datetime.datetime.now()

            # wait value

            # return value

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
