#!/usr/bin/python
# -*- coding: UTF-8 -*-

import threading
import time


class Sender(threading.Thread):
    def __init__(self, content:str):
        threading.Thread.__init__(self) # 父类的init
        self.s = 0  # 发送方控制变量
        self.can_send: bool = True
        self.store_frame = ""
        self.frames = []
        self.frame_init(content)
        self.ACK = -1    # 用于接收ACK信号

    def frame_init(self, content:str):
        # 模拟数据链路层之上的层次
        self.frames = [bin(ord(ch)).replace('0b', '') for ch in content]

    def make_frame(self):
        # frame: 偶校验，数据，序列号
        parity = 0
        for ch in self.frames.pop(0):   # 将第一个帧取出（不放回）
            parity += int(ch)
        parity = parity // 2
        frame = "{}{}{}".format(parity, self.frames[0], self.s)
        return frame

    def send_frame(self, frame):
        print("Send frame: Parity{}\tFrame{}\tsequence_number{}".format(frame[0], frame[1:-1], frame[-1]))
        return frame

    def resend_frame(self):
        print("Resend Frame{}".format(self.store_frame))
        return self.store_frame

    def receive(self, frame_ack):
        self.ACK = int(frame_ack)

    def run(self):
        send_time = 0   # 初始化
        while True:
            if self.frames is None:
                # 如果没有需要发送的帧，就退出了
                # 注：这不是现实中的，只是便于程序的运行
                break
            if self.can_send:
                frame = self.make_frame()
                self.store_frame = frame    # 保留副本
                send_time = time.time()     # 计时器开始计时
                self.s = (self.s + 1)//2    # s  变量取反
                self.send_frame(frame)      # 发送副本
                self.can_send = False
            if self.ACK == self.s:      # 成功接收
                send_time = 0
                self.can_send = True
                self.store_frame = ""   # 清除副本
            if time.time() - send_time > 1:     # Timeout
                send_time = time.time()         # 重新计时
                self.resend_frame()

if __name__ == "__main__":
    sender = Sender("hello")
    sender.start()
    print(sender.frames)