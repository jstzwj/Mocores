import sys

sys.path.append("src/")

import mocores.client

client = mocores.client_build()

#connect the client to the cluster, in this case, which only contains one silo
client.connect()

#example of calling grains from the initialized client
friend = client.get_actor("HelloActor", 0)
response = friend.sayHello("Good morning, my friend!")
print(mocores.get(response))