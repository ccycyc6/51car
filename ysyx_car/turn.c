#include <reg52.h>
#include "motor.h"
#define TIMER_RELOAD 100


unsigned char zkb1 = 0;
unsigned char zkb2 = 0;
unsigned char t = 0;

void init()
{
	EA = 1;
	TMOD = (TMOD & 0xF0) |  0x01;
	TH0 =(65536 - 100) / 256;
	TL0 = (65536 - 100)% 256;	
	ET0 = 1;
	TR0 = 1;
}
 
void timer0(void) interrupt 1
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
		ENA(1);
	}
	else
	{
		ENA(0);
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
		ENB(1);
	}
	else 
	{
		ENB(0);
	}
	++t;
	if(t >= 50)
	{
		t = 0;
	}
	
	
 
}

void qianjin()
{
    IN1(1); IN2(1); IN3(1); IN4(1); // 正转
    zkb1 = 8;
    zkb2 = 8;
}

void stop()
{
    IN1(0); IN2(0); IN3(0); IN4(0); // 停止
    zkb1 = 0;
    zkb2 = 0;
}

void turn_left1()
{
    IN1(1); IN2(1); IN3(0); IN4(0); // 左转
    zkb1 = 13;
    zkb2 = 13;
}

void turn_right1()
{
    IN1(0); IN2(0); IN3(1); IN4(1); // 右转
    zkb1 = 13;
    zkb2 = 13;
}
 



