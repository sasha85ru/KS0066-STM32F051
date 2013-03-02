#include "ks0066.h"
#include "delay_tim6.h"


/* Кодировка русских символов */
const unsigned char russian[]={ 0x41, 0xA0, 0x42, 0xA1, 0xE0, 0x45,
0xA3, 0xA4, 0xA5,0xA6, 0x4B, 0xA7, 0x4D, 0x48, 0x4F, 0xA8, 0x50,0x43,
0x54, 0xA9, 0xAA, 0x58, 0xE1, 0xAB, 0xAC, 0xE2, 0xAD,0xAE, 0x62,
0xAF, 0xB0, 0xB1, 0x61, 0xB2, 0xB3, 0xB4, 0xE3, 0x65, 0xB6, 0xB7,
0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x6F, 0xBE, 0x70, 0x63,0xBF,
0x79, 0xE4, 0x78, 0xE5, 0xC0, 0xC1, 0xE6, 0xC2,0xC3, 0xC4, 0xC5,
0xC6, 0xC7 };

/* Вывод строки, в том числе и на русском языке */
void Lcd_write_str(uint8_t *STRING)
{
  char c; //символ из строки
	while (c=*STRING++){
	if(c>=192) Lcd_write_data(russian[c-192]);
	else Lcd_write_data(c);
	}
}

/* перевод начало строки
 * x = 0 верхняя строка
 * x = 1 нижняя строкаа
 * y - позиция первого символа 0-15*/
void Lcd_goto(uint8_t x,uint8_t y)
{
	int str;
	str = y + 0x80;
	if(x == 1)
	{
	str+= 0x40;
	}
	Lcd_write_cmd(str);
}

/*Вывод пробел по указанному адресу.
 *  * x = 0 верхняя строка
 * x = 1 нижняя строкаа
 * y - позиция первого символа 0-15*/
void Lcd_clear_cell(uint8_t x, uint8_t y)
{
	int str;
	str = y + 0x80;
	if(x == 1)
	{
	str+= 0x40;
	}
	Lcd_write_cmd(str);
	Lcd_write_str(" ");
}

/*Настрока порта на выход*/
void Init_pin_out()
{
	GPIO_InitTypeDef init_pin;
	RCC_clock(init_port, ENABLE);
	init_pin.GPIO_Pin  = pin_e | pin_rs | pin_rw | pin_d7 | pin_d6 | pin_d5 | pin_d4;
	init_pin.GPIO_Mode = GPIO_Mode_OUT;
	init_pin.GPIO_OType =  GPIO_OType_PP;
	init_pin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (port, &init_pin);
}

/*Отправить команду*/
void Lcd_write_cmd(uint8_t cmd )
{
	rw_0;
	rs_0;
	e_0;
	write_byte(cmd>>4); // выставили полубайт
	StrobReset();
	TIM6delay_us(50);
	reset_byte();
	write_byte(cmd&0x0F); //выставили полубайт
	StrobReset();
	TIM6delay_us(50);
	reset_byte();
}

/*Отправить данные*/
void Lcd_write_data(uint8_t data)
{
	rw_0;
	rs_1;
	e_0;
	write_byte(data>>4); // выставили полубайт
	StrobReset();
	TIM6delay_us(50);
	reset_byte();
	write_byte(data&0x0F); //выставили полубайт
	StrobReset();
	TIM6delay_us(50);
	reset_byte();

}

/* Выставить полубайт */
void write_byte(uint8_t byte)
{
	 GPIO_WriteBit(port,pin_d7,0x8&byte);
	 GPIO_WriteBit(port,pin_d6,0x4&byte);
	 GPIO_WriteBit(port,pin_d5,0x2&byte);
	 GPIO_WriteBit(port,pin_d4,0x1&byte);
}

/* Сбросить полубайт */
void reset_byte()
{
	GPIO_ResetBits(port,pin_d7);
	GPIO_ResetBits(port,pin_d6);
	GPIO_ResetBits(port,pin_d5);
	GPIO_ResetBits(port,pin_d4);
}

/*Строба для записи в дислпей + сброс полубайта*/
void StrobReset()
{
	e_1;
	TIM6delay_us(45);
	e_0;
	reset_byte();
}

/*Настройка дисплея*/
void Init_lcd()
{
	InitDelayTIM6();//Настройка таймера6 (TIM6)
	Init_pin_out();//Настроки порта (GPIO)

	TIM6delay_ms(40);
	//function set
	rs_0;
	rw_0;
	e_0;
	write_byte(0b0010);
	StrobReset();
	write_byte(0b0010);
	StrobReset();
	write_byte(0b1100);//2 - строки, дисплей - вкл.
	StrobReset();
	//function set end
	TIM6delay_us(39);
	//Display ON/OFF Control
	write_byte(0b0000);
	StrobReset();
	write_byte(0b1100);//дисплей - вкл.курсор - выкл, мигание курсора - выкл.
	StrobReset();
	//Display ON/OFF Control end
	TIM6delay_us(40);
	//Display Clear
	write_byte(0b0000);
	StrobReset();
	write_byte(0b0001);
	StrobReset();
	//Display Clear end
	TIM6delay_ms(2);
	//Entry Mode Set
	write_byte(0b0000);
	StrobReset();
	write_byte(0b0110);//инкремент, свдиг - выкл.
	StrobReset();
	//Entry Mode Set end

}



void Return_home()
{
	Lcd_write_cmd(0x1);
}









