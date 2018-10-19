from enum import Enum

class WorkerStatus(Enum):
    Null = 0
    # This silo was just created, but not started yet.
    Created = 1
    # This silo has just started, but not ready yet. It is attempting to join the cluster.
    Joining = 2    
    # This silo is alive and functional.
    Active = 3
    # This silo is shutting itself down.
    ShuttingDown = 4 
    # This silo is stopping itself down.
    Stopping = 5
    # This silo is deactivated/considered to be dead.
    Dead = 6