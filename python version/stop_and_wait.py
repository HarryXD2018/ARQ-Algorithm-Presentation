from stop_and_wait_sender import *

if __name__ == "__main__":
    data_to_send = "Hello, World"
    sender = Sender(data_to_send)
    sender.run()
