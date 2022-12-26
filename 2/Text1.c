#include <reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit DULA=P2^6;
sbit WELA=P2^7;
sbit D1=P1^0;
uchar num,temp,tt,a;
uchar code table[]={
   0x3f,0x06,0x5b,0x4f,
   0x66,0x6d,0x7d,0x07,
   0x7f,0x6f,0x77,0x7c,
   0x39,0x5e,0x79,0x71};
void main() 
{    
   num=0;tt=0;temp=0;a=0;
   TMOD=0x01;//���ö�ʱ��0�����ҹ�����ʽΪ1
   TH0=(65536-50000)/256;//����N=50000(��50MS)ʱTH0���߰�λ���ĳ�ֵ
   TL0=(65536-50000)%256;//����N=50000(��50MS)ʱTL0���Ͱ�λ���ĳ�ֵ
   EA=1;//�����ж�
   ET0=1;//�򿪶�ʱ��0�ж�����
   TR0=1;//������ʱ��0
   IT0=0;//�����жϴ�����ʽΪ��ƽ������ʽ��Ĭ��Ϊ��ƽ������ʽ��
   temp=0xfe;
   P1=temp;
   WELA=1;//��λѡ
   P0=0xc0;//ѡλ
   WELA=0;//���棨�رգ�λѡ
   DULA=1;
   P0=0x3f;
   DULA=0;
   while (1)
      {
	 ;
      }
}
 void exter0() interrupt 1//�������ж����
 {
    TH0=(65536-50000)/256;
    TL0=(65536-50000)%256;//����ʱ���������ٸ�һ�γ�ֵ
    tt++;//��¼��ʱ�������Ĵ���������һ��ΪN*1΢�룬��50MS��
    if(tt/10==0)
    {
       temp=_crol_(temp,1);
	       P1=temp;
    }
    if(tt==20)//��ʱ������20�Σ����Ѽ�ʱ1S
	    {
	       /*temp=_crol_(temp,1);
	       P1=temp;*/
	      /* a++;
	       if(a/2==0)
	       {
		  temp=_crol_(temp,1);
	       P1=temp;
	       }*/
	       tt=0;//ʹ��ʱ��������һ��1S�ļ�ʱ
	       num++;
	       if(num==16)
		  num=0;
	       DULA=1;//�򿪶�ѡ
	       P0=table[num];//ѡ��
	       DULA=0;//�رն�ѡ
	    }
 }