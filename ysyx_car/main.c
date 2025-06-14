#include <reg52.h>
#include "motor.h"
#include "turn.h"
#include "xunji.h"


// 50ms延时函数，适用于24MHz晶振
/*void delay_50ms(void) {
	unsigned char i, j, k;
	for(k = 0; k < 5; k++) {      // 5*10ms = 50ms
		for(i = 38; i > 0; i--)
			for(j = 250; j > 0; j--);
	}
}*/

void main()
{
	 init();
	while(1)
	{
	//		delay_50ms(); // 延时50ms
			xunji();
	}
}