import mocores
import asyncio

import my_actors

async def main():
    worker = mocores.Worker("localhost", 60007)
    await worker.run()

loop = asyncio.get_event_loop()
loop.run_until_complete(main())
loop.close()