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
   TMOD=0x01;//设置定时器0工作且工作方式为1
   TH0=(65536-50000)/256;//设置N=50000(即50MS)时TH0（高八位）的初值
   TL0=(65536-50000)%256;//设置N=50000(即50MS)时TL0（低八位）的初值
   EA=1;//打开总中断
   ET0=1;//打开定时器0中断允许
   TR0=1;//启动定时器0
   IT0=0;//设置中断触发方式为电平触发方式（默认为电平触发方式）
   temp=0xfe;
   P1=temp;
   WELA=1;//打开位选
   P0=0xc0;//选位
   WELA=0;//锁存（关闭）位选
   DULA=1;
   P0=0x3f;
   DULA=0;
   while (1)
      {
	 ;
      }
}
 void exter0() interrupt 1//这里是中断序号
 {
    TH0=(65536-50000)/256;
    TL0=(65536-50000)%256;//当定时器加满后再赋一次初值
    tt++;//记录定时器加满的次数（加满一次为N*1微秒，即50MS）
    if(tt/10==0)
    {
       temp=_crol_(temp,1);
	       P1=temp;
    }
    if(tt==20)//计时器加满20次，即已计时1S
	    {
	       /*temp=_crol_(temp,1);
	       P1=temp;*/
	      /* a++;
	       if(a/2==0)
	       {
		  temp=_crol_(temp,1);
	       P1=temp;
	       }*/
	       tt=0;//使计时器进入下一个1S的计时
	       num++;
	       if(num==16)
		  num=0;
	       DULA=1;//打开段选
	       P0=table[num];//选段
	       DULA=0;//关闭段选
	    }
 }