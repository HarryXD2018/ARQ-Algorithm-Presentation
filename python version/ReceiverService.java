package com.springboot.service;

import org.springframework.stereotype.Service;

import java.io.*;
import java.util.Date;

@Service
public class ReceiverService {
    int r = 0;
    String content = "";
    private static final double error_probability = 0.2;//范围(0,1)
    Long startTs = System.currentTimeMillis();

    public String handle(String frame) throws IOException {
        if (Math.random() < error_probability) {
            String _frame = "";
            for (int i = 0; i < frame.length() - 1; ++i)
                _frame += String.valueOf(frame.charAt(i)).equals("1") ? "0" : "1";
            log("模拟出错，将数据"+frame+"更改为"+_frame+"出错概率:"+toString(error_probability*100+"")+"%");
            frame = _frame;
        }
        String seq_number = frame.substring(frame.length() - 1);//序列号
        int sum_frame = 0;  //对数据位和发送方冗余位求和
        for (int i = 0; i < frame.length() - 1; ++i)
            sum_frame += Integer.parseInt(String.valueOf(frame.charAt(i)));
        int parity = (sum_frame % 2 == 0 ? 1 : 0);//偶校验结果
        int seq_match = (this.r == Integer.parseInt(seq_number) ? 1 : 0);  //判断是重发帧还是新的帧
        if (parity != 1) {
            //未通过偶校验，数据出错
            log("未通过偶校验，数据出错");
        } else if (seq_match == 1) {
            String content_b = frame.substring(1, frame.length() - 1);
            if (System.currentTimeMillis() - startTs > 10000) content = "";
            content = content + toString(content_b);
            log("接收到数据:" + content);
            startTs = System.currentTimeMillis();
            this.r = (this.r + 1) % 2;
            return this.r + "";
        }
        return "Timeout";
    }

    public void log(String str) throws IOException {
        Date date = new Date();
        FileWriter fileWriter;
        fileWriter = new FileWriter("/root/计网实验.txt", true);//需要将###更换为文件路径
        fileWriter.write(date.toString() + " " + str + "\r\n");
        fileWriter.flush();
        fileWriter.close();
    }

    public static String toString(String binary) {
        String[] tempStr = binary.split(" ");
        char[] tempChar = new char[tempStr.length];
        for (int i = 0; i < tempStr.length; i++) {
            tempChar[i] = BinstrToChar(tempStr[i]);
        }
        return String.valueOf(tempChar);
    }


    //将二进制字符串转换成int数组
    public static int[] BinstrToIntArray(String binStr) {
        char[] temp = binStr.toCharArray();
        int[] result = new int[temp.length];
        for (int i = 0; i < temp.length; i++) {
            result[i] = temp[i] - 48;
        }
        return result;
    }


    //将二进制转换成字符
    public static char BinstrToChar(String binStr) {
        int[] temp = BinstrToIntArray(binStr);
        int sum = 0;
        for (int i = 0; i < temp.length; i++) {
            sum += temp[temp.length - 1 - i] << i;
        }
        return (char) sum;
    }

    public String testLog() {
        File file = new File("/root/计网实验.txt");
        StringBuilder result = new StringBuilder();
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));//构造一个BufferedReader类来读取文件
            String s;
            while ((s = br.readLine()) != null) {//使用readLine方法，一次读一行
                result.append("<p>" + System.lineSeparator() + s + "</p>");
            }
            br.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return result.toString();
    }
}
