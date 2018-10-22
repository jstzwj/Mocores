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
        if(inspect.isbuiltin(each_item[1]) or inspect.iscoroutinefunction(each_item[1])):
            orig_members_dict[each_item[0]] = each_item[1]
    
    # create new ref type
    new_class = type(original_class.__name__ + 'Ref', (object,), orig_members_dict)
    # orig_init = new_class.__init__
    # Make copy of original __init__, so we can call it without recursion
    def init_decorator(self, actor_class=None, actor_key=None, *args, **kws):
        self.actor_class = actor_class
        self.actor_key = actor_key

    new_class.__init__ = init_decorator # Set the class' __init__ to the new one

    for each_method in inspect.getmembers(new_class, predicate=inspect.iscoroutinefunction):
        if(each_method[0].startswith('__')):
            continue
        orig_method = getattr(new_class, each_method[0])
        async def function_decorator(self, *args, **kws):
            # construct work_item
            invoke_work_item = work_item.InvokeWorkItem(self.actor_class, self.actor_key,
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
    # Make copy of original __init__, so we can call it without recursion
    def init_decorator(self, *args, **kws):
        orig_init(self, *args, **kws)

    original_class.__init__ = init_decorator # Set the class' __init__ to the new one

    for each_method in inspect.getmembers(original_class, predicate=inspect.iscoroutinefunction):
        if(inspect.isbuiltin(each_method[1])):
            continue
        orig_method = getattr(original_class, each_method[0])
        async def function_decorator(self, *args, **kws):
            orig_method(self, *args, **kws)
        setattr(original_class, each_method[0], function_decorator)

    return original_class
