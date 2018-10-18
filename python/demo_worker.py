import mocores
import asyncio

import my_actors

async def main():
    worker = mocores.Worker("dev", "HelloApp", "localhost", 60007, True)
    await worker.run()

loop = asyncio.get_event_loop()
loop.run_until_complete(main())
loop.close()