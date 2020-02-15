import asyncio

from mocores import Client

async def main():
    client = Client(localhost_cluster=True)
    await client.connect()


if __name__ == "__main__":
    asyncio.run(main())
