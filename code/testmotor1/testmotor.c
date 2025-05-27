#include <reg52.h>

sbit in1 = P1^0;
sbit in2 = P1^1;
sbit ENA1 = P0^0;
sbit in3 = P1^2;
sbit in4 = P1^3;
sbit ENA2 = P0^1;	


void delay(unsigned int z);
void delay_us(unsigned int aa);

void main(){
    while(1)
    {
        unsigned int i, cycle=0, T = 1024; // 减少T到512（1/4）
        in1 = 1;
        in2 = 0;
        in3 = 1;
        in4 = 0;
        for(i=0;i<100;i++) 
        {
            delay(10); // 保持50%占空比，延时不变
            ENA1 = ~ENA1;
            ENA2 = ~ENA2;
        }
        in1 = 0;
        in2 = 1;
        in3 = 0;
        in4 = 1;
        for(i=0;i<100;i++)
        {
            delay(20); // 保持50%占空比，延时不变
            ENA1 = ~ENA1;
            ENA2 = ~ENA2;
        }
        in1 = 1;
        in2 = 0;
        in3 = 1;
        in4 = 0;
        while(cycle!=T) // T从2048减少到512
        {
            ENA1 = 1;
            ENA2 = 1;
            delay_us(cycle++);
            ENA1 = 0;
            ENA2 = 0;
            delay_us(T-cycle);
        }
        in1=0;
        in2=1;
        in3=0;
        in4=1;
        while(cycle!=T) // T从2048减少到512
        {
            ENA1 = 1;
            ENA2 = 1;
            delay_us(cycle++);
            ENA1 = 0;
            ENA2 = 0;
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