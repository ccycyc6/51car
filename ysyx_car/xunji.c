#include <reg52.h>
#include "motor.h"
#include "turn.h"


sbit left1 = P1^2;

sbit right1 = P1^3;


void xunji()
{
	unsigned char flag = 0;
	if((right1 == 0)&&(left1 == 0))
	{
		flag = 0;
	}
	if((right1 == 0)&&(left1 == 1))
	{
		flag = 1;
	}
	if((right1 == 1)&&(left1 == 0))
	{
		flag = 2;
	}
    if((right1 == 1)&&(left1 == 1))
    {
        flag = 3;
    }

	switch(flag)
	{
		case 0:qianjin();break;
		
		case 1:turn_left1();break;
		
		case 2:turn_right1();break;

		case 3:stop();break;

		default:qianjin();break;
	}
}