#include "reg52.h"

sbit RightCon1A = P3^7;
sbit RightCon1B = P3^3;
sbit RightCon2A = P3^6;
sbit RightCon2B = P3^2;

sbit LeftCon1A = P3^4;
sbit LeftCon1B = P3^5;
sbit LeftCon2A = P3^1;
sbit LeftCon2B = P3^0;

void goForward()
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

void goRight()
{
	LeftCon1A = 0;
	LeftCon1B = 1;
	LeftCon2A = 0;
    LeftCon2B = 1;
	RightCon1A = 0;
	RightCon1B = 0;
    RightCon2A = 0;
    RightCon2B = 0;
}


void goLeft()
{
	LeftCon1A = 0;
	LeftCon1B = 0;
	LeftCon2A = 0;
	LeftCon2B = 0;
	RightCon1A = 0;
	RightCon1B = 1;
    RightCon2A = 0;
    RightCon2B = 1;
}

void goBack()
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

