from stop_and_wait_receiver import *
from stop_and_wait_sender import *
from multiprocessing import Queue
if __name__ == "__main__":
    data_to_send = "Hello, World"
    sender = Sender(data_to_send)
    receiver = Receiver()

    sender.start()
    receiver.start()
    # sender.join()
    # receiver.join()



