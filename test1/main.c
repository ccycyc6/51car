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
        unsigned int i, cycle=0, T = 1024; // 减少T到512（1/4）
        goForward();
        for(i=0;i<100;i++) 
        {
            delay(10); // 保持50%占空比，延时不变
            ENALeftCon1 = ~ENALeftCon1;
            ENALeftCon2 = ~ENALeftCon2;
            ENARightCon1 = ~ENARightCon1;
            ENARightCon2 = ~ENARightCon2;
        }
        goBack();
        for(i=0;i<100;i++)
        {
            delay(20); // 保持50%占空比，延时不变
            ENALeftCon1 = ~ENALeftCon1;
            ENALeftCon2 = ~ENALeftCon2;
            ENARightCon1 = ~ENARightCon1;
            ENARightCon2 = ~ENARightCon2;
        }
        goLeft();
        while(cycle!=T) // T从2048减少到512
        {
            ENALeftCon1 = 1;
            ENALeftCon2 = 1;
            ENARightCon1 = 1;
            ENARightCon2 = 1;
            delay_us(cycle++);
            ENALeftCon1 = 0;
            ENALeftCon2 = 0;
            ENARightCon1 = 0;
            ENARightCon2 = 0;
            delay_us(T-cycle);
        }
        goLeft();
        while(cycle!=T) // T从2048减少到512
        {
            ENALeftCon1 = 1;
            ENALeftCon2 = 1;
            ENARightCon1 = 1;
            ENARightCon2 = 1;
            delay_us(cycle++);
            ENALeftCon1 = 0;
            ENALeftCon2 = 0;
            ENARightCon1 = 0;
            ENARightCon2 = 0;
            delay_us(T-cycle);
        }
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


