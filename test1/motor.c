#include "reg52.h"
//这里定义1为前，2为后,A为1，B为0时前进89
sbit IN1 = P1^0; 
sbit IN2 = P1^1;
sbit ENA = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;
sbit ENB = P1^5;

/*sbit ENALeftCon2 = P2^4;
sbit ENALeftCon1 = P2^6;
sbit ENARightCon1 = P2^7;
sbit ENARightCon2 = P2^5;*/

void goForward()
{
	LeftCon1A = 1;
	LeftCon1B = 0;
	LeftCon2A = 1;
	LeftCon2B = 0;
	RightCon1A = 1;
	RightCon1B = 0;
	RightCon2A = 1;
  RightCon2B = 0;
}

void goLeft()
{
	LeftCon1A = 1;
	LeftCon1B = 0;
	LeftCon2A = 1;
  LeftCon2B = 0;
	RightCon1A = 0;
	RightCon1B = 1;
  RightCon2A = 0;
  RightCon2B = 1;
}


void goRight()
{
	LeftCon1A = 0;
	LeftCon1B = 1;
	LeftCon2A = 0;
	LeftCon2B = 1;
	RightCon1A = 1;
	RightCon1B = 0;
  RightCon2A = 1;
  RightCon2B = 0;
}

void goBack()
{
	LeftCon1A = 0;
	LeftCon1B = 1;
	LeftCon2A = 0;
	LeftCon2B = 1;
	RightCon1A = 0;
	RightCon1B = 1;
  RightCon2A = 0;
  RightCon2B = 1;
}

void stop()
{
	LeftCon1A = 0;
	LeftCon1B = 0;
	LeftCon2A = 0;
	LeftCon2B = 0;
	RightCon1A = 0;
	RightCon1B = 0;
	RightCon2A = 0;
	RightCon2B = 0; 
}