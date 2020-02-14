
from mocores import Silo, IGrain
import asyncio


class PongGrain(IGrain):
    def __init__(self):
        super().__init__()
        self.add_method(self.pong)

    async def pong(self):
        return "hello world"

async def main():
    silo = Silo()
    await silo.run()

if __name__ == "__main__":
    asyncio.run(main())
    