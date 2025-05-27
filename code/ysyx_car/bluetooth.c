#include <REGX52.H>
#include <intrins.H>
#include <xingshi.H>
 
 
#define left     'C'
#define right    'D'
#define up       'A'
#define down     'B'
#define stop     'F'
 
unsigned char U_data;     //接受数据存放
unsigned char Way; 
 
 
void UartInit(void)        //9600bps@11.0592MHz
{
    PCON &= 0x7F;            //波特率不倍速
    SCON = 0x50;            //8位数据,可变波特率
//AUXR &= 0xBF;            //定时器时钟12T模式
//AUXR &= 0xFE;            //串口1选择定时器1为波特率发生器
    TMOD &= 0x0F;             //设置定时器模式
    TMOD |= 0x20;             //设置定时器模式
    TL1 = 0xFD;                //设置定时初始值
    TH1 = 0xFD;                //设置定时重载值
    ET1 = 0;                     //禁止定时器中断
    TR1 = 1;                  //定时器1开始计时
    EA  = 1;
    ES  = 1;
}
 
void receive(unsigned char m)
{
    
    switch(m)
    {
        
        case  'A':      //前进
            qianji();
        break;
        
        case  'C':
            zuozhuan();    // 左转
        break;
        
        case  'D':
            youzhuan();     // 右转
        break;
        
        case 'B':
            houtui();   //  后退
        break;
        
        case 'F':      // 停止
             tingzhi();
        break;
        
    }
        
}
//***************************************************************************
    
void UartInit_seve() interrupt 4
{
    
    tingzhi();
    RI = 0;                  //清除接受中断标志位
    U_data = SBUF;                    //接受数据
    receive(U_data);
    
}