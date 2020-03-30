from stop_and_wait_receiver import *
from stop_and_wait_sender import *
from multiprocessing import Queue

if __name__ == "__main__":
    data_to_send = "Hello, World"
    queue = Queue()  # 此队列用于进程通信
    sender = Sender(data_to_send, queue)
    receiver = Receiver(queue)
    sender.start()
    receiver.start()
    # sender.join()
    # receiver.join()