package com.springboot.service;

import org.springframework.stereotype.Service;

@Service
public class ReceiverService {
    int r=0;
    String content="";
    boolean flag=true;
    public String handle(String frame) {
        if(frame.equals("011001011")&&flag) {System.out.println("模拟出错");frame="010001011";flag=false;}
        String seq_number = frame.substring(frame.length()-1);//序列号
        int sum_frame = 0;  //对数据位和发送方冗余位求和
        for(int i=0;i<frame.length()-1;++i)
            sum_frame += Integer.parseInt(String.valueOf(frame.charAt(i)));
        int parity = (sum_frame % 2 == 0?1:0);//偶校验结果
        int seq_match = (this.r ==Integer.parseInt(seq_number)?1:0);  //判断是重发帧还是新的帧
        if (parity!=1){
            //未通过偶校验，数据出错
            System.out.println("未通过偶校验，数据出错");
        }
        else if(seq_match==1){
            String content_b=frame.substring(1,frame.length()-1);
            content=content+toString(content_b);
            System.out.println("接收到数据:"+content);
            this.r = (this.r+1)%2;
            return this.r+"";
        }
        return "Timeout";
    }

    public static String toString(String binary) {
        String[] tempStr=binary.split(" ");
        char[] tempChar=new char[tempStr.length];
        for(int i=0;i<tempStr.length;i++) {
            tempChar[i]=BinstrToChar(tempStr[i]);
        }
        return String.valueOf(tempChar);
    }


    //将二进制字符串转换成int数组
    public static int[] BinstrToIntArray(String binStr) {
        char[] temp=binStr.toCharArray();
        int[] result=new int[temp.length];
        for(int i=0;i<temp.length;i++) {
            result[i]=temp[i]-48;
        }
        return result;
    }


    //将二进制转换成字符
    public static char BinstrToChar(String binStr){
        int[] temp=BinstrToIntArray(binStr);
        int sum=0;
        for(int i=0; i<temp.length;i++){
            sum +=temp[temp.length-1-i]<<i;
        }
        return (char)sum;
    }
}
