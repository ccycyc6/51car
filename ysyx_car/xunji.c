#include <reg52.h>
#include "motor.h"
#include "turn.h"


sbit left1 = P1^2;
sbit right1 = P1^3;
sbit right2 = P1^4;
sbit left2 = P1^5;


void delay_50ms(void) {
	unsigned char i, j, k;
	for(k = 0; k < 5; k++) {      // 5*10ms = 50ms
		for(i = 38; i > 0; i--)
			for(j = 250; j > 0; j--);
	}
}


void xunji()
{
	unsigned char flag = 0;
	if((right1 == 0)&&(left1 == 0)&&(right2 == 0)&&(left2 == 0))
	{
		flag = 0;
	}
	if((right1 == 0)&&(left1 == 1)&&(right2 == 0)&&(left2 == 0))   //left1
	{
		flag = 1;
	}
	if((right1 == 1)&&(left1 == 0)&&(right2 == 0)&&(left2 == 0))   //right1
	{
		flag = 2;
	}
    if((right1 == 1)&&(left1 == 1))                                //stop
    {
        flag = 3;
    }
	if((right2 == 1)&&(left2 == 0)&&(right1 == 0)&&(left1 == 0)) //right2
	{
		flag = 4;
	}
	if((right2 == 0)&&(left2 == 1)&&(right1 == 0)&&(left1 == 0)) //left2
	{
		flag = 5;
	}

    switch(flag)
    {
        case 0: qianjin(); break;
        case 1: turn_left1(); break;
        case 2: turn_right1(); break;
        case 3: stop(); break;
        case 4: // 右急转，减速
            zkb1 = 0; zkb2 = 0; // 低速
            turn_right2();
            while(1) {
                // 实时检测flag变化
                if(!((right2 == 1)&&(left2 == 0)&&(right1 == 0)&&(left1 == 0))) {
                    break;	
                }
            }
            zkb1 = 7; zkb2 = 7; // 恢复正常速度
            break;
        case 5: // 左急转，减速
            zkb1 = 2; zkb2 = 2; // 低速
            turn_left2();
            while(1) {
                if(!((right2 == 0)&&(left2 == 1)&&(right1 == 0)&&(left1 == 0))) {
                    break;
                }
            }
            zkb1 = 7; zkb2 = 7; // 恢复正常速度
            break;
        default: qianjin(); break;
    }
}