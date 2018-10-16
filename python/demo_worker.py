import mocores
import asyncio

import my_actors


worker = mocores.Worker("localhost", 60007)
worker.run()