import mocores
import asyncio

@mocores.actor
class MyActor(object):
    def __init__(self):
        print("init")

    def hello_world(self, message=None):
        print(message)
        return 1


async def main():
    client = mocores.Client("192.168.1.1", 60006)
    client.connect("192.168.1.2", 60006)

    my_actor = client.get_actor(MyActor, 1)
    num = await my_actor.hello_world(message="hello world")
    print(num)


# async run main
loop = asyncio.get_event_loop()
loop.run_until_complete(main())
loop.close()