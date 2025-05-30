#include <reg52.h>
#include "motor.h"

sbit ENALeftCon2 = P2^4;
sbit ENALeftCon1 = P2^6;
sbit ENARightCon1 = P2^7;
sbit ENARightCon2 = P2^5;

void delay(unsigned int z);
void delay_us(unsigned int aa);

void main(){
    while(1)
    {
        goForward();
        delay(300); // 前进3秒

        goBack();
        delay(300); // 后退3秒

        goLeft();
        delay(300); // 左转3秒

        goRight();
        delay(300); // 右转3秒
    }
}

void delay(unsigned int z)
{
    unsigned int x, y;
    for(x=z;x>0;x--)
        for(y=110;y>0;y--);
}

void delay_us(unsigned int aa)
{
    while(aa--);
}


