

class WorkItem(object):
    def __init__(self):
        pass


class InvokeWorkItem(WorkItem):
    def __init__(self, actor_class, actor_id, actor_method,
                 parameters, keyword_parameters, invoke_time):
        self.actor_class = actor_class
        self.actor_id = actor_id
        self.actor_method = actor_method
        self.parameters = parameters
        self.keyword_parameters = keyword_parameters
        self.invoke_time = invoke_time
