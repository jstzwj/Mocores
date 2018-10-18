import mocores
import asyncio

import my_actors

async def main():
    client = mocores.Client("localhost", 60006)
    await client.connect("localhost", 60007)

    my_actor = client.get_actor(my_actors.MyActor, 1)
    num = await my_actor.hello_world(message="hello world")
    print(num)

# async run main
loop = asyncio.get_event_loop()
loop.run_until_complete(main())
loop.close()