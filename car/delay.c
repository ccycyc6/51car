#include "intrins.h"

void Delay2000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 15;
	j = 2;
	k = 235;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay300ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 26;
	k = 223;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay150ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 2;
	j = 13;
	k = 237;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay450ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 39;
	k = 209;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
