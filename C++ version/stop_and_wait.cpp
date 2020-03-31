#include <iostream.h>
#include <stdlib.h>
#include<fstream.h>  

//下面是两个函数原型 
void receiver(int,fstream  &,fstream &,ofstream &);//接收方 
void sender(fstream  &datafile1,fstream  &datafile2,ofstream&datafile3);//发送方  

void main(){
	fstream  datafile1,datafile2; ofstream datafile3;
	cout<<"下面开始数据的传输，注意：传输数据以“!”结束"<<endl;
	sender(datafile1,datafile2,datafile3); 
	cout<<"数据传输结束"<<endl; 
}   
//接收端 

void receiver(int i,fstream &datafile1, fstream &datafile2, ofstream&datafile3){
	char r,re;  
	datafile1.open("file1",ios::out|ios::in);   
	if(!datafile1){
		cout<<"文件打开失败！"<<endl; 
		exit(0);
	}  
	datafile1.seekg(i-1,ios::beg);   
	datafile1.get(r);//打开file1,并从指定位置读取一个字符 
	if(r!=' ')
	{ 
		if(r>='A'&&r<='Z')//若读取的字符有效，即正确接受字符    
		{
			datafile3.open("file3",ios::app); 
			if(!datafile3)
			{
				cout<<"文件打开失败！"<<endl;  exit(0);
			}
			datafile3<<r;//将收到的字符写入文件file3    
			cout<<"字符已正确接收"<<endl;  
			cout<<"准备发送确认信息ACK"<<endl;
			cout<<"请输入A,并以回车结束"<<endl;//'A'代表"ACK"    
			cin>>re;
    		datafile2.open("file2",ios::out); 
			if(!datafile2)
			{
 				cout<<"文件打开失败！"<<endl;
				exit(0);     
			}		
			datafile2<<re;//将确认信息写入file2
		}
    	if(r<'A'||r>'Z')//读取的字符无效，即接受字符出错    
		{
    		cout<<"接收字符错误"<<endl;    
			cout<<"准备发送信息NAK"<<endl;
    		cout<<"请输入字符‘N’，并以回车结束";//'N'代表"NAK"    
			cin>>re;
    		datafile3.open("file3");   
			if(!datafile3)
			{
				cout<<"文件打开失败！"<<endl;
 				exit(0);     
			}
			datafile3<<re;//返回出错信息，将'N'写入file3   
		}    
	}
   datafile1.close(); 
   datafile2.close();   
   datafile3.close();}   
//发送端 
void sender(fstream  &datafile1,fstream  &datafile2,ofstream&datafile3)
{
	char s,st; long i = 0;  
	cout<<"整个信息输入以“！”结束";
 	cout<<"请输入一个待发送的字符,并按回车"; 
	cin>>s; 
 	datafile1.open("file1",ios::out|ios::in); if(!datafile1) {
  	cout<<"文件打开失败！"<<endl;
	exit(0); }  
 	datafile1<<s;//发送信息，即将待发送的字符写入文件
	file1i++;
 	cout<<"字符已被发送"<<endl; 
	datafile1.close(); 
 	receiver(i,datafile1,datafile2,datafile3);//调用接收端进行相应操作  
 	while(1) 
	{
 		if(s=='!') break;
	  	for(intt=1;t<=4;t++)//起定时器的作用  
		{
		 	datafile2.open("file2",ios::in); 
			if(!datafile2) 
			{
				cout<<"文件打开失败！"<<endl;
				exit(0); 
			}             
		 	datafile2.get(st);
		   	datafile2.close(); 
		  	if(st=='A')//发送方收到接收方的确认信息ACK   
			{
		    	cout<<"上一个字符已被接收！"<<endl;
		    	cout<<"请输入一个待发送的字符,并按回车"; 
				cin>>s; 
		 		datafile1.open("file1",ios::out|ios::in); 
				if(!datafile1)     
				{
		  			cout<<"文件打开失败！"<<endl;  exit(0);     
				}  
			 	datafile1<<s;//将新的待发送字符写入
				file1i++;
			 	cout<<"字符已被发送"<<endl;
			    datafile1.close();       
			    receiver(i,datafile1,datafile2,datafile3);//调用接收端进行相应操作  
			 	break; 
		   	}
			if(st=='N')//发送方收到接收方的出错信息NAK   
			{
		    	cout<<"上一个字符出错！"<<endl;
				cout<<"现在需重新发送原字符"<<endl;    
				datafile1.open("file1",ios::out|ios::in);   
				if(!datafile1)     
				{
		  		cout<<"文件打开失败！"<<endl;
				exit(0);     
				}
		     	datafile1<<s;i++;
		 		cout<<"字符已被发送"<<endl;    
				datafile1.close();  
		    	receiver(i,datafile1,datafile2,datafile3);//调用接收端进行相应操作  
				break;
			}
		}
		cout<<"定时器超时，现重新发送原字符。"<<endl;datafile1.open("file1",ios::out|ios::in); 
		if(!datafile1)
		{
			cout<<"文件打开失败！"<<endl;
			exit(0);     
		}
	 	datafile1<<s;
		i++;
		cout<<"字符已被发送"<<endl;
		datafile1.close(); 
	    receiver(i,datafile1,datafile2,datafile3);
	}
}
