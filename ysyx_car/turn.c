#include <reg52.h>
#include "motor.h"


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
 
 
void turn_right1()
{
	zkb1 = 0;
	zkb2 = 13;
}
 


void qianjin()
{
	zkb1 = 8;
	zkb2 = 8;
}

void stop()
{
	zkb1 = 0;
	zkb2 = 0;
}
 



