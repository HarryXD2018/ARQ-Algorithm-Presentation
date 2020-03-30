from stop_and_wait_receiver import *
from stop_and_wait_sender import *
from multiprocessing import Queue
import time

if __name__ == "__main__":
    queue = Queue()
    data_to_send = "Hello, World"
    sender = Sender(data_to_send)
    sender.run()

    # sender.join()
    # receiver.join()
