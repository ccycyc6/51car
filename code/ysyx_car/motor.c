#include <REGX52.H>               // 包含 8051 单片机头文件

// 前进方向引脚定义
sbit M1A=P1^6; //0                // 前左侧A端 IN3
sbit M1B=P1^7; //1                // 前左侧B端 IN4

sbit M2A=P1^4; //1                // 前右侧A端 IN1
sbit M2B=P1^5; //0                // 前右侧B端 IN2

sbit M3A=P1^0; //1                // 后左侧A端 IN1
sbit M3B=P1^1; //0                // 后左侧B端 IN2

sbit M4A=P1^2; //1                // 后右侧A端 IN3
sbit M4B=P1^3; //0                // 后右侧B端 IN4

sbit EN1A = P0^0;                 // M1A/B 电机使能端
sbit EN1B = P0^1;                 // M2A/B 电机使能端

sbit EN2A = P0^2;                 // M3A/B 电机使能端
sbit EN2B = P0^3;                 // M4A/B 电机使能端

unsigned char coutern,compare;    // 定义两个无符号字符变量，计数器和比较值

void run()  // 电机运动函数
{
    M1A = 0;                      // 前左A端低电平
    M1B = 1;                      // 前左B端高电平
    M2A = 1;                      // 前右A端高电平
    M2B = 0;                      // 前右B端低电平
    
    M3A = 1;                      // 后左A端高电平
    M3B = 0;                      // 后左B端低电平
    M4A = 1;                      // 后右A端高电平
    M4B = 0;                      // 后右B端低电平
}

void Timer0_Init(void)        // 定时器0初始化，100微秒@11.0592MHz
{
    // AUXR &= 0x7F;           // 定时器时钟12T模式（注释掉不用）
    TMOD &= 0xF0;             // 清除定时器0模式位
    TMOD |= 0x01;             // 设置定时器0为模式1（16位定时器）
    TL0 = 0xA4;               // 设置定时初始值低8位
    TH0 = 0xFF;               // 设置定时初始值高8位
    TF0 = 0;                  // 清除定时器0溢出中断标志
    TR0 = 1;                  // 启动定时器0
    ET0 = 1;                  // 允许定时器0中断
    EA = 1;                   // 允许总中断
    PT0=0;                    // 设置定时器0优先级为低
}

void Timer0_Serve() interrupt 1   // 定时器0中断服务函数
{
    TL0 = 0xA4;               // 重载定时初始值低8位
    TH0 = 0xFF;               // 重载定时初始值高8位
    compare = 10;             // 设置PWM占空比比较值
    coutern ++;               // 计数器加1
    if(coutern > 100)         // 如果计数器大于100
    {
        coutern = 0;          // 计数器清零
    }
    if(coutern < compare)     // 如果计数器小于比较值
    {
        EN1A = 1;             // 打开所有电机使能
        EN1B = 1;
        EN2A = 1;
        EN2B = 1;
    }
    else                      // 否则
    {
        EN1A = 0;             // 关闭所有电机使能
        EN1B = 0;
        EN2A = 0;
        EN2B = 0;
    }
}

void main()
{
    Timer0_Init();            // 初始化定时器0
    while(1)
    {
        yundong();            // 持续调用运动函数
    }        
}
