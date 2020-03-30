#!/usr/bin/python
# -*- coding: UTF-8 -*-

import threading
import time
from multiprocessing import Queue


class Receiver(threading.Thread):
    def __init__(self, queue):
        threading.Thread.__init__(self)  # 父类的init
        self.queue1 = queue  # 创建一个队列，用于进程通信
        self.lock = threading.Lock()
        self.e = threading.Event()
        self.r = 0
        self.content = ""  # 解码后的结果，模拟数据链路层之上
        self.last_frame = ""  # 最新接受的帧
        print("receiver init")

    def run(self):
        # time.sleep(5)
        while True:
            # self.e.wait()
            self.lock.acquire()  # 进入关键区
            print("receiver running")
            self.receive_frame()  # 接收帧
            self.lock.release()  # 离开关键区

            parity, seq_match = self.check_frame(self.last_frame)
            if not parity:  # 未通过偶校验，数据出错
                print("receiver 未通过偶校验，数据出错")
                pass
                # time.sleep(0.5)     # 休眠0.5秒
            elif seq_match:
                self.content += self.deliver_data()  # 将二进制表示帧转换为字符
                # deliver_data 中的chr()函数起到了伪代码中ExtractData()的作用
                self.r += 1

            self.lock.acquire()  # 进入关键区
            self.send_frame()
            self.lock.release()  # 离开关键区

    def check_frame(self, frame):
        # parity_from_sender = frame[0]   # 发送方偶校验
        print("check_frame frame", frame)
        seq_number = frame[-1]  # 序列号

        sum_frame = 0  # 对数据位和发送方冗余位求和
        for ch in frame[0:-1]:
            sum_frame += int(ch)

        parity = (sum_frame % 2 == 0)  # 偶校验结果
        seq_match = (self.r == int(seq_number))  # 判断是重发帧还是新的帧

        return parity, seq_match

    def send_frame(self):  # 发送ACK
        self.queue1.put(self.r)
        return self.r

    def receive_frame(self):
        get = self.queue1.get()
        if get is None:
            self.last_frame = "0000000000"
        else:
            self.last_frame = get

    def deliver_data(self):
        content = self.last_frame[1:-1]  # 发送的数据

        unicode = int(content, 2)
        print(unicode)
        print("接受字符:{}".format(chr(unicode)))
        return chr(unicode)