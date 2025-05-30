#include "reg52.h"
#include "hc04.h"
#include "delay.h"
#include "sg90.h"
#include "Oled.h"
#include "motor.h"

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2

#define BZ 1
#define XJ 2
#define GS 3


sbit A25 = P1^5;
sbit A26 = P1^6;
sbit A27 = P1^7;

sbit leftSensorX = P2^7;
sbit rightSensorX = P2^6;

sbit leftSensorG = P2^5;
sbit rightSensorG = P2^4;

char dir;
	
double disMiddle;
double disLeft;
double disRight;

void xunjiMode()
{
		if(leftSensorX == 0 && rightSensorX == 0){
			goForward();
		}
		if(leftSensorX == 1 && rightSensorX == 0){
			goLeft();
		}
		
		if(leftSensorX == 0 && rightSensorX == 1){
			goRight();
		}
		
		if(leftSensorX == 1 && rightSensorX == 1){
			//停
			stop();
		}
}

void gensuiMode()
{
		if(leftSensorG == 0 && rightSensorG == 0){
			goForward();
		}
		if(leftSensorG == 1 && rightSensorG == 0){
			goRight();
		}
		
		if(leftSensorG == 0 && rightSensorG == 1){
			
			goLeft();
		}
		
		if(leftSensorG == 1 && rightSensorG == 1){
			//停
			stop();
		}
}

/*void bizhangMode()
{
	if(dir != MIDDLE){
			sgMiddle();
			dir = MIDDLE;
			Delay300ms();
		}
		disMiddle = get_distance();
		
		if(disMiddle > 35){
			//前进
			goForward();
		}else if(disMiddle < 10){
			goBack();
			
		}else
		{
			//停止
			stop();
			//测左边距离
			sgLeft();
			Delay300ms();
			disLeft = get_distance();
			
			sgMiddle();
			Delay300ms();
			
			sgRight();
			dir = RIGHT;
			Delay300ms();
			disRight = get_distance();
			
			if(disLeft < disRight){
				goRight();
				Delay150ms();
				stop();
			}
			if(disRight < disLeft){
				goLeft();
				Delay150ms();
				stop();
			}
		}

}*/

void main()
{

	int mark = 0;
	
	Time0Init();
	Time1Init();
	//舵机的初始位置

	sgMiddle();
	Delay300ms();
	Delay300ms();
	dir = MIDDLE;
	
	/*Oled_Init();
	Oled_Clear();
	Oled_Show_Str(2,2,"-----Ready----");*/
	
	while(1){
		//满足寻迹模式的条件
		if(A25 == 0 && A26 == 1 && A27 == 1){
			/*if(mark != XJ){
				Oled_Clear();
				Oled_Show_Str(2,2,"-----XunJi----");
			}*/
			mark = XJ;
			xunjiMode();
		}
		//满足跟随模式的条件
		if(A25 == 1 && A26 == 0 && A27 == 1){
			/*if(mark != GS){
				Oled_Clear();
				Oled_Show_Str(2,2,"-----GenSui----");
			}*/
			mark = GS;
			gensuiMode();
		}
		//满足避障模式的条件
		if(A25 == 1 && A26 == 1 && A27 == 0){
			if(mark != BZ){
				/*Oled_Clear();
				Oled_Show_Str(2,2,"-----BiZhang----");*/
			}
			mark = BZ;
			bizhangMode();
		}
	
	}
}
