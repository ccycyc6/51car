#include <reg52.h>
 
sbit IN1 = P1^0; 
sbit IN2 = P1^1;
sbit ENA = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;
sbit ENB = P1^5;
 
sbit left1 = P0^0;
sbit left2 = P0^1;
sbit right1 = P0^2;
sbit right2 = P0^3;
 
unsigned char zkb1 = 0;
unsigned char zkb2 = 0;
unsigned char t = 0;
 
 
void init()
{
	EA = 1;
	TMOD |= 0x01;
	TH0 =(65536 - 100) / 256;
	TL0 = (65536 - 100)% 256;	
	ET0 = 1;
	TR0 = 1;
}
 
void timer0() interrupt 1
{
 
	TH0 = (65536 - 100) / 256;
	TL0 = (65536 - 100) % 256;
		
	if(t < zkb1)
	{
// 		if(t % 2 == 0)
// 		{
// 		    ENA = 1;
// 	    }
// 		else 
// 		{
// 			ENA = 0;
// 		}
		ENA = 1;
	}
	else
	{
		ENA = 0;
	}
	if(t < zkb2)
	{
// 		if(t%2 == 0)
// 		{
// 		    ENB = 1;
// 		}
// 		else 
// 		{
// 			ENB = 0;
// 		}
		ENB =1;
	}
	else 
	{
		ENB = 0;
	}
	++t;
	if(t >= 50)
	{
		t = 0;
	}
	
	
 
}
 
void turn_left1()
{
	zkb1 = 13;
	zkb2 = 0;
 
}
 
void turn_left2()
{
 
	zkb1 = 13;
	zkb2 = 0;
}
 
void turn_right1()
{
	zkb1 = 0;
	zkb2 = 13;
}
 
void turn_right2()
{
	zkb1 = 0;
	zkb2 = 13;
}
 
void qianjin()
{
	zkb1 = 8;
	zkb2 = 8;
}
void xunji()
{
	unsigned char flag;
	if((right2 == 0)&&(right1 == 0)&&(left1 == 0)&&(left2 == 0))
	{
		flag = 0;
	}
	if((right2 == 0)&&(right1 ==1)&&(left1 == 0)&&(left2 == 0))
	{
		flag = 1;
	}
	if((right2 == 0)&&(right1 == 0)&&(left1 == 1)&&(left2 == 0))
	{
		flag = 2;
	}
	if((right2 == 0)&&(right1 == 0)&&(left1 == 0)&&(left2 == 1))
	{
		flag = 3;
	}
	if((right2 == 1)&&(right1 == 0)&&(left1 == 0)&&(left2 == 0))
	{
		flag = 4;
	}
	switch(flag)
	{
		case 0:qianjin();break;
		
		case 1:turn_right1();break;
		
		case 2:turn_left1();break;
		
		case 3:turn_left2();break;
		
		case 4:turn_right2();break;
		
		default:qianjin();break;
	}
}
 
void main()
{
	init();
// 	zkb1 = 40;
// 	zkb2 = 30;
	IN1 = 0; 
	IN2 = 1;
    IN3 = 0;
    IN4 = 1;
	while(1)
	{
			
			xunji();
		
	}
}