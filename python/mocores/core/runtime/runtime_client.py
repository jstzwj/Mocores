import logging
import asyncio
import datetime

from mocores.core.runtime.actor_base import actor, actor_ref
from mocores.core.runtime.membership_table import MembershipTable, MembershipTableEntry

class RuntimeClient(object):
    def __init__(self, ip, port):
        print("new client {0}:{1}".format(ip, port))
        self.ip = ip
        self.port = port
        self.membership_table = MembershipTable()
        self.membership_table.add_entry(MembershipTableEntry("dev", "127.0.0.1", 60007, datetime.datetime.now(), True))

    def connect(self):
        for each in self.membership_table.table:
            logging.debug("try to connect to:{}".format(each.to_string()))
            async def tcp_echo_client(message, loop):
                reader, writer = await asyncio.open_connection('127.0.0.1', 60007,loop=loop)

                print('Send: %r' % message)
                writer.write(message.encode())

                data = await reader.read(100)
                print('Received: %r' % data.decode())

                print('Close the socket')
                writer.close()
            message = 'Hello World!'
            loop = asyncio.get_event_loop()
            loop.run_until_complete(tcp_echo_client(message, loop))
            loop.close()

    def get_actor(self, actor_type, actor_id):
        # generate ref
        actor_ref_type = actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__

        # get worker id by hash

        return actor_ref_type(actor_class, actor_id)