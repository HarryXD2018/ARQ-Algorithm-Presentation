#include <iostream.h>
#include <stdlib.h>
#include<fstream.h>  

//��������������ԭ�� 
void receiver(int,fstream  &,fstream &,ofstream &);//���շ� 
void sender(fstream  &datafile1,fstream  &datafile2,ofstream&datafile3);//���ͷ�  

void main(){
	fstream  datafile1,datafile2; ofstream datafile3;
	cout<<"���濪ʼ���ݵĴ��䣬ע�⣺���������ԡ�!������"<<endl;
	sender(datafile1,datafile2,datafile3); 
	cout<<"���ݴ������"<<endl; 
}   
//���ն� 

void receiver(int i,fstream &datafile1, fstream &datafile2, ofstream&datafile3){
	char r,re;  
	datafile1.open("file1",ios::out|ios::in);   
	if(!datafile1){
		cout<<"�ļ���ʧ�ܣ�"<<endl; 
		exit(0);
	}  
	datafile1.seekg(i-1,ios::beg);   
	datafile1.get(r);//��file1,����ָ��λ�ö�ȡһ���ַ� 
	if(r!=' ')
	{ 
		if(r>='A'&&r<='Z')//����ȡ���ַ���Ч������ȷ�����ַ�    
		{
			datafile3.open("file3",ios::app); 
			if(!datafile3)
			{
				cout<<"�ļ���ʧ�ܣ�"<<endl;  exit(0);
			}
			datafile3<<r;//���յ����ַ�д���ļ�file3    
			cout<<"�ַ�����ȷ����"<<endl;  
			cout<<"׼������ȷ����ϢACK"<<endl;
			cout<<"������A,���Իس�����"<<endl;//'A'����"ACK"    
			cin>>re;
    		datafile2.open("file2",ios::out); 
			if(!datafile2)
			{
 				cout<<"�ļ���ʧ�ܣ�"<<endl;
				exit(0);     
			}		
			datafile2<<re;//��ȷ����Ϣд��file2
		}
    	if(r<'A'||r>'Z')//��ȡ���ַ���Ч���������ַ�����    
		{
    		cout<<"�����ַ�����"<<endl;    
			cout<<"׼��������ϢNAK"<<endl;
    		cout<<"�������ַ���N�������Իس�����";//'N'����"NAK"    
			cin>>re;
    		datafile3.open("file3");   
			if(!datafile3)
			{
				cout<<"�ļ���ʧ�ܣ�"<<endl;
 				exit(0);     
			}
			datafile3<<re;//���س�����Ϣ����'N'д��file3   
		}    
	}
   datafile1.close(); datafile2.close();   datafile3.close();}   
//���Ͷ� 
voidsender(fstream  &datafile1,fstream  &datafile2,ofstream&datafile3){
 chars,st; longi=0;  
cout<<"������Ϣ�����ԡ���������";
 cout<<"������һ�������͵��ַ�,�����س�"; cin>>s; 
 datafile1.open("file1",ios::out|ios::in); if(!datafile1) {
  cout<<"�ļ���ʧ�ܣ�"<<endl;  exit(0); }  
 datafile1<<s;//������Ϣ�����������͵��ַ�д���ļ�file1i++;
 cout<<"�ַ��ѱ�����"<<endl; datafile1.close(); 
 receiver(i,datafile1,datafile2,datafile3);//���ý��ն˽�����Ӧ����  
 while(1) {
 	if(s=='!') break;
  for(intt=1;t<=4;t++)//��ʱ��������  
{
 datafile2.open("file2",ios::in); if(!datafile2) {
cout<<"�ļ���ʧ�ܣ�"<<endl;exit(0); } 
               
 datafile2.get(st);
   datafile2.close(); 
  if(st=='A')//���ͷ��յ����շ���ȷ����ϢACK   {
    cout<<"��һ���ַ��ѱ����գ�"<<endl;
    cout<<"������һ�������͵��ַ�,�����س�"; cin>>s; 
 datafile1.open("file1",ios::out|ios::in); if(!datafile1)     {
  cout<<"�ļ���ʧ�ܣ�"<<endl;  exit(0);     }  
 datafile1<<s;//���µĴ������ַ�д��file1i++;
 cout<<"�ַ��ѱ�����"<<endl;     datafile1.close();       
     receiver(i,datafile1,datafile2,datafile3);//���ý��ն˽�����Ӧ����  
 break; 
   }
if(st=='N')//���ͷ��յ����շ��ĳ�����ϢNAK   {
    cout<<"��һ���ַ�����"<<endl;
cout<<"���������·���ԭ�ַ�"<<endl;    datafile1.open("file1",ios::out|ios::in);   
 if(!datafile1)     {
  cout<<"�ļ���ʧ�ܣ�"<<endl;  exit(0);     }
     datafile1<<s;i++;
 cout<<"�ַ��ѱ�����"<<endl;    datafile1.close();  
    receiver(i,datafile1,datafile2,datafile3);//���ý��ն˽�����Ӧ����  
 break;   }  }
   cout<<"��ʱ����ʱ�������·���ԭ�ַ���"<<endl;datafile1.open("file1",ios::out|ios::in); if(!datafile1)     {
  cout<<"�ļ���ʧ�ܣ�"<<endl;  exit(0);     }
     datafile1<<s;i++;
 cout<<"�ַ��ѱ�����"<<endl;datafile1.close(); 
    receiver(i,datafile1,datafile2,datafile3);}}
