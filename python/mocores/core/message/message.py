import enum

class Categories(enum.Enum):
    Ping = 0
    System = 1
    Application = 2

class Directions(enum.Enum):
    Request = 0
    Response = 1
    OneWay = 2

class ResponseTypes(enum.Enum):
    Success = 0
    Error = 1
    Rejection = 2


class RejectionTypes(enum.Enum):
    Transient = 0
    Overloaded = 1
    DuplicateRequest = 2
    Unrecoverable = 3
    GatewayTooBusy = 4


class Header(object):
    def __init__(self):
        pass

class Message(object):
    def __init__(self):
        self.LENGTH_HEADER_SIZE = 8

        self.queued_time = None
        self.retry_count = 0
        self.max_retries = 3
        self.target_address = None
        self.sending_address = None
        self.category = None
        self.direction = None