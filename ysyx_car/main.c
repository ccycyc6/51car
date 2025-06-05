#include <reg52.h>
#include "motor.h"
#include "turn.h"
#include "xunji.h"


// 50ms延时函数，适用于24MHz晶振
void delay_50ms(void) {
	unsigned char i, j, k;
	for(k = 0; k < 5; k++) {      // 5*10ms = 50ms
		for(i = 38; i > 0; i--)
			for(j = 250; j > 0; j--);
	}
}

void main()
{
	 init();
// 	zkb1 = 40;
// 	zkb2 = 30;
	//IN1(1);
	//IN2(1);
    //IN3(1);
    //IN4(1);
	while(1)
	{
	//		delay_50ms(); // 延时50ms
			xunji();
			/*IN1(1);
			IN2(1);
			IN3(1);
			IN4(1);
			ENA(1);
			ENB(1);*/
	}
}