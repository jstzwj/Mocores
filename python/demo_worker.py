import mocores
import asyncio

import my_actors

def main():
    worker = mocores.WorkerBuilder().build()
    worker.run()

if __name__ == "__main__":
    main()
