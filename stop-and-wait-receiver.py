#!/usr/bin/python
# -*- coding: UTF-8 -*-

import threading
import time


class Receiver(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)  # 父类的init
        self.r = 0
        self.content = ""       # 解码后的结果，模拟数据链路层之上
        self.last_frame = ""    # 最新接受的帧

    def run(self):
        # self.receive_frame()
        parity, seq_match = self.check_frame(self.last_frame)
        if not parity:      # 未通过偶校验，数据出错
            time.sleep(0.5)     # 休眠0.5秒
        elif seq_match:
            self.content += self.deliver_data()     # 将二进制表示帧转换为字符
            # deliver_data 中的chr()函数起到了伪代码中ExtractData()的作用
            self.r += 1
        self.send_frame()

    def check_frame(self, frame):
        # parity_from_sender = frame[0]   # 发送方偶校验
        seq_number = frame[-1]          # 序列号

        sum_frame = 0   # 对数据位和发送方冗余位求和
        for ch in frame[0:-1]:
            sum_frame += int(ch)

        parity = (sum_frame // 2 == 0)    # 偶校验结果
        seq_match = (self.r == seq_number)  # 判断是重发帧还是新的帧

        return parity, seq_match

    def send_frame(self):
        return self.r

    def receive_frame(self, frame):
        self.last_frame = frame

    def deliver_data(self):
        content = self.last_frame[1:-1]   # 发送的数据

        unicode = 0
        for ch in content:
            unicode += int(ch)
            unicode *= 10

        print("接受字符{}".format(chr(unicode)))
        return chr(unicode)
