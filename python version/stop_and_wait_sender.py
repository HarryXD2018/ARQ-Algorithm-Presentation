#!/usr/bin/python
# -*- coding: UTF-8 -*-

import time
import requests

requests.packages.urllib3.disable_warnings()


class Sender:
    def __init__(self, content: str):
        self.s = 0  # 发送方控制变量
        self.store_frame = ""
        self.frames = []
        self.frame_init(content)
        self.ACK = 0  # 用于接收ACK信号
        print("sender init")

    def frame_init(self, content: str):
        # 模拟数据链路层之上的层次
        self.frames = [bin(ord(ch)).replace('0b', '') for ch in content]
        print(self.frames)

    def make_frame(self):
        # frame: 偶校验，数据，序列号
        parity = 0
        if self.frames.__len__() == 0:
            return ""
        for ch in self.frames[0]:
            parity += int(ch)
        parity = parity % 2
        frame = "{}{}{}".format(parity, self.frames.pop(0), self.s)  # 将第一个帧取出（不放回）
        return frame

    def send_frame(self, frame):
        print("Send frame: Parity:{}\t Frame:{}\t sequence_number:{}".format(frame[0], frame[1:-1], frame[-1]))
        url = "https://flxdu.cn/api/test?frame=" + frame
        r = requests.get(url)
        self.ACK = r.text
        return frame

    def resend_frame(self):
        print("Resend Frame {}".format(self.store_frame))
        url = "https://flxdu.cn/api/test?frame=" + self.store_frame
        r = requests.get(url)
        self.ACK = r.text
        return self.store_frame

    def run(self):
        while True:
            if self.frames is None:
                # 如果没有需要发送的帧，就退出了
                # 注：这不是现实中的，只是便于程序的运行
                break
            frame = self.make_frame()
            if frame == "":
                break
            self.store_frame = frame  # 保留副本
            self.s = (self.s + 1) % 2  # s  变量取反
            self.send_frame(frame)  # 发送副本
            print(frame)
            time.sleep(0.5)
            # 接收返回的ACK帧
            if self.ACK == "Timeout":
                self.resend_frame()
            elif self.ACK != self.s:  # 成功接收
                self.store_frame = ""  # 清除副本
            elif self.ACK == self.s:  # 未成功接收
                self.resend_frame()


if __name__ == "__main__":
    sender = Sender("hello")
    sender.start()
    print(sender.frames)
