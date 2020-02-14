import asyncio

from mocores import Client

async def main():
    client = Client('127.0.0.1', 9797)
    await client.connect()
    

if __name__ == "__main__":
    asyncio.run(main())
