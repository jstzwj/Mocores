import mocores
import asyncio

import my_actors

def main():
    client = mocores.ClientBuilder().build()
    client.connect()

    my_actor = client.get_actor(my_actors.MyActor, 1)
    # num = my_actor.hello_world(message="hello world")
    # print(num)

if __name__ == "__main__":
    main()