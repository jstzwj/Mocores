import mocores
import asyncio

import my_actors

async def main():
    client = mocores.Client("localhost", 60006)
    client.connect("localhost", 60007)

    my_actor = client.get_actor(my_actors.MyActor, 1)
    num = await my_actor.hello_world(message="hello world")
    print(num)

def readInt(data):
    return (int.from_bytes(data[:4], byteorder="big"),data[4:])

def readStr(data):
    len, data = readInt(data)
    return (data[:len].decode(), data[len:])


print((1).to_bytes(4, byteorder="big"))
bs = b"\x00\x00\x00\x011234"
string, bs= readStr(bs)
print(string, bs)

# async run main
loop = asyncio.get_event_loop()
loop.run_until_complete(main())
loop.close()