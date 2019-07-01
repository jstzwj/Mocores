import time
import logging
import asyncio

import mocores.core.runtime.actor_base
import mocores.core.util
import mocores.core.actor_pool
import mocores.core.worker_thread
from mocores.core.util.message_queue import MessageQueue
from mocores.core.runtime.membership_table import MembershipTable, MembershipTableEntry


class RuntimeWorker(object):
    def __init__(self, cluster_id, service_id, ip, port, single_node_mode=False):
        print("new worker")
        self.cluster_id = cluster_id
        self.service_id = service_id
        self.single_node_mode = single_node_mode
        self.ip = ip
        self.port = port
        self.start_time = time.strftime('%Y-%m-%d-%H-%M-%S', time.gmtime(time.time()))
        self.messages = MessageQueue()
        self.worker_threads = []
        self.membership_table = MembershipTable()

    async def handle_packet(self, reader, writer):
        data = await reader.read(100)
        message = data.decode()
        addr = writer.get_extra_info('peername')
        print("Received %r from %r" % (message, addr))

        print("Send: %r" % message)
        writer.write(data)
        await writer.drain()

        print("Close the client socket")
        writer.close()

    def run(self):
        logging.info("start server")

        # add self to membership table
        if self.single_node_mode:
            self.membership_table.add_entry(
                MembershipTableEntry(
                    self.cluster_id,
                    self.ip,
                    self.port,
                    self.start_time,
                    True))
        else:
            pass

        logging.info("start worker threads")
        for i in range(4):
            self.worker_threads.append(mocores.core.worker_thread.WorkerThread())
            self.worker_threads[i].start()

        logging.debug("wait for connections")
        loop = asyncio.get_event_loop()
        coro = asyncio.start_server(lambda reader, writer: self.handle_packet(reader, writer), self.ip, self.port, loop=loop)
        server = loop.run_until_complete(coro)
        # Serve requests until Ctrl+C is pressed
        print('Serving on {}'.format(server.sockets[0].getsockname()))
        try:
            loop.run_forever()
        except KeyboardInterrupt:
            pass

        # Close the server
        server.close()
        loop.run_until_complete(server.wait_closed())
        loop.close()

    def get_actor(self, actor_type, actor_id):
        actor_ref_type = mocores.core.runtime.actor_base.actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__
        return actor_ref_type(actor_class, actor_id)