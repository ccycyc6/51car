#include <reg52.h>

sbit l_bmo1 = P1^0;//IN1=1,IN2=0  FORWARD
sbit l_bmo2 = P1^5;
sbit r_bmo1 = P1^6;//IN3=0,IN4=1  FORWARD
sbit r_bmo2 = P1^7;

int main()
{
	while(1){
		l_bmo1 = 1;
		l_bmo2 = 0;
		r_bmo1 = 0;
		r_bmo2 = 1;
	}
}