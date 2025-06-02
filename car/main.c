#include "motor.h"
#include "delay.h"
#include "uart.h"
#include "time.h"
#include "reg52.h"
extern char speedLeft;
extern char speedRight;
 
 
sbit leftSensor = P2^7;
sbit rightSensor = P2^6;
 
void main()
{
  Time0Init();
  Time1Init();
  //UartInit();
  
  while(1){
    
    if(leftSensor == 0 && rightSensor == 0){
        speedLeft = 32;
        speedRight = 40;
    }
    if(leftSensor == 1 && rightSensor == 0){
        speedLeft = 12;//10份单位时间全速运行，30份停止，所以慢，20ms是40份的500us
        speedRight = 40;
    }
    
    if(leftSensor == 0 && rightSensor == 1){
        speedLeft = 32;
        speedRight = 20;
    }
    
    if(leftSensor == 1 && rightSensor == 1){
      //停
        speedLeft = 0;
        speedRight = 0;
    }
  }
}