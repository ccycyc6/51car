#include <REGX52.H>
               //前进方向
sbit M1A=P1^6; //0                              //前左侧A端 IN3  
sbit M1B=P1^7; //1                              //前左侧B端 IN4
 
sbit M2A=P1^4; //1                              //前右侧A端 IN1
sbit M2B=P1^5; //0                              //前右侧B端 IN2
 
sbit M3A=P1^0; //1                              //后左侧A端 IN1
sbit M3B=P1^1; //0                              //后左侧B端 IN2

sbit M4A=P1^2; //1                              //后右侧A端 IN3
sbit M4B=P1^3; //0                              //后右侧B端 IN4
 
sbit EN1A = P0^0;                               //M1A/B电机使能端
sbit EN1B = P0^1;                               //M2A/B电机使能端
 
sbit EN2A = P0^2;                               //M3A/B电机使能端
sbit EN2B = P0^3;                               //M4A/B电机使能端
 
unsigned char coutern,compare;

void yundong()  //  
{
    M1A = 0;
    M1B = 1;
    M2A = 1;
    M2B = 0;
    
    M3A = 1;
    M3B = 0;
    M4A = 1;
    M4B = 0;
    
}
 
void Timer0_Init(void)        //100微秒@11.0592MHz
{
//    AUXR &= 0x7F;            //定时器时钟12T模式
    TMOD &= 0xF0;            //设置定时器模式
    TMOD |= 0x01;            //设置定时器模式
    TL0 = 0xA4;                //设置定时初始值
    TH0 = 0xFF;                //设置定时初始值
    TF0 = 0;                //清除TF0标志
    TR0 = 1;            //定时器0开始计时
    ET0 = 1;
    EA = 1;    
    PT0=0;
}


void Timer0_Serve() interrupt 1
{
    TL0 = 0xA4;                //设置定时初始值
    TH0 = 0xFF;           //设置定时初始值 
    compare = 10;
    coutern ++;
    if(coutern > 100)
    {
        coutern = 0;
    
    }
    if(coutern < compare)
    {
        EN1A = 1;
        EN1B = 1;
        EN2A = 1;
        EN2B = 1;
    }
    else
    {
        EN1A = 0;
        EN1B = 0;
        EN2A = 0;
        EN2B = 0;
        
    }
}
 
void main()
{
    
    Timer0_Init();
    while(1)
    {
        yundong();
    }        
}