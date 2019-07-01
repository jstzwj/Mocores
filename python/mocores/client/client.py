import mocores.core.runtime.actor_base
# import mocores.core.net.protocol
from mocores.core.runtime.membership_table import(MembershipTable, MembershipTableEntry)
import logging


class Client(object):
    def __init__(self, ip, port):
        print("new client {0}:{1}".format(ip, port))
        self.ip = ip
        self.port = port
        self.master_session = None
        self.membership_table = MembershipTable()

    async def connect(self, ip, port):
        print("connecting to the cluster: {0}:{1}".format(ip, port))
        # connect and get membership table
        self.master_session = mocores.net.client_client.ClientSession(ip, port)
        await self.master_session.ping()
        self.membership_table.table = await self.master_session.get_memberships()
        for each in self.membership_table.table:
            logging.debug('ip:{0},port:{1},start_time:{2}'.format(each.ip, each.port, each.start_time))
        # ping and get actor table

    def get_actor(self, actor_type, actor_id):
        # generate ref
        actor_ref_type = mocores.core.actor.actor_ref(actor_type)
        actor_class = actor_type.__module__ + "." + actor_type.__name__

        # get worker id by hash

        return actor_ref_type(actor_class, actor_id)
        