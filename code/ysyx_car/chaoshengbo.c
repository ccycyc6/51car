#include <REGX52.H>
#include <intrins.H>
#include <xingshi.H>
#include <Timer.H>
sbit Trig = P2^1;
sbit Echo = P2^2;


unsigned char sum; //超声波测距
unsigned char stence; //与障碍物的限制距离
 
//***************************************************
void Delay1000ms()		//@11.0592MHz 延时一秒
{
	unsigned char i, j, k;
 
	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
 
//**********************************************
void Delay20us()		//@11.0592MHz  延时20us
{
	unsigned char i;
 
	_nop_();
	i = 6;
	while (--i);
}
 
//******************************************
 
void chaoshengbo()
{
	
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0;				//设置定时初始值
	TH1 = 0;				//设置定时初始值
				
 
	Trig = 1; //发射20US的脉冲
	Delay20us();
	Trig = 0;  //关闭
	
	while(!Echo);//等待返回脉冲
		TR1 = 1;							//打开定时器1
	while(!Echo);//返回脉冲结束
		TR1 = 0;							//关闭定时器1
	
	sum = ((TH1*256+TL1)*0.034)/2+1;					//计算距离公式
	
	if( stence > sum)
	{
		tingzhi();
		Delay1000ms();
	}
	
}
 
 
 
 
 
 