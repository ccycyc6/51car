#include <reg52.h>

sbit asA = P1^0;//IN1=1,IN2=0  FORWARD
sbit asB = P1^5;
sbit dsA = P1^6;//IN3=0,IN4=1  FORWARD
sbit dsB = P1^7;
sbit awA = P2^0;
sbit awB = P2^1;
sbit dwA = P2^2;
sbit dwB = P2^3;
sbit ENAas = P2^4;
sbit ENAds = P2^5;
sbit ENAaw = P2^6;
sbit ENAdw = P2^7;

int main()
{
	while(1){
		ENAas = 1; // Enable motor A
		ENAds = 1; // Enable motor D
		ENAaw = 1; // Enable motor A
		ENAdw = 1; // Enable motor D
		asA = 1; // Set IN1 for motor A forward
		asB = 0; // Set IN2 for motor A forward
		dsA = 0; // Set IN3 for motor D forward
		dsB = 1; // Set IN4 for motor D forward
		awA = 1; // Set IN1 for motor A forward
		awB = 0; // Set IN2 for motor A forward
		dwA = 0; // Set IN3 for motor D forward
		dwB = 1; // Set IN4 for motor D forward
		

	}
}
