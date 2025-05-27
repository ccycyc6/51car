 
 
#include <REGX52.H>
#include <Delay.H>
#include <xingshi.H>
 
 
sbit out1 = P0^4;  //左边的红外探头
sbit out2 = P0^5;  //右边的红外探头


void HWbizhang()
{
    if(out1 == 0)     //左边检测到障碍物
    {
        tingzhi() ;     //小车停止
        Delay(500);            //停止500ms
    houtui();              //小车后退
        Delay(1000);    //后退1000ms
        youzhuan();     //小车右转
        Delay(2000);
    qianji();         
    }
    
    if(out2 == 0)     //右边检测到障碍物
    {
        tingzhi() ;     //小车停止
        Delay(500);            //停止500ms
    houtui();              //小车后退
        Delay(1000);    //后退1000ms
        zuozhuan();     //小车左转
        Delay(2000);
    qianji();         
    }
    
    if((out1 == 1)&&(out2 == 1))
    {
        qianji();     
    }
    
    if((out1 == 0)&&(out1 == 0))
    {
        tingzhi() ;     //小车停止
        Delay(500);            //停止500ms
    houtui();              //小车后退
        Delay(1000);    //后退1000ms
        youzhuan();     //小车右转
        Delay(2000);
    qianji();         
    }
}