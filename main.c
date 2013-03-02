#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "ks0066.h"


int main()
{
   SystemInit();
	 Init_lcd();

	while(1)
	{
		Lcd_goto(1,0);
		Lcd_write_str("TEST");
	}
}
