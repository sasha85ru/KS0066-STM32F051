#ifndef __ks0066_h
#define __ks0066_h

/* Подключем дисплей WH1602b на контроллере
 * ks0066 к STM32F0-DICOVERY.
 * Подключения осуществляется по толерантным к 5 Вольтам
 * выводам микроконтроллера */

/* Функция задержки испульзует таймер6 TIM6*/

/* Внимание! После сброса М.К. без выключения дислпея иногда не проходит конфигурация дисплея.
 * Однако при одновременной подаче питания на М.К. и дислпей такого глюка не замеченно,
 * так же конфигурация стабильно работает при подключения по 8-битной шине*/
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

/*Datasheet http://pdf1.alldatasheet.com/datasheet-pdf/view/37318/SAMSUNG/KS0066.html*/
/*Расположения выводов дисплея WH1602B
 * 1  GND
 * 2  +5V
 * 3  Vo (Contrast)
 * 4  RS
 * 5  R/W
 * 6  E
 * 7  DB0
 * 8  DB1
 * 9  DB2
 * 10 DB3
 * 11 DB4
 * 12 DB5
 * 13 DB6
 * 14 DB7
 * 15 LED+ (4.2V)
 * 16 LED-
 * */




#define port      GPIOC// выбор порта для подключения дисплея
#define init_port 	RCC_AHBPeriph_GPIOC //Тактирование дисплея
#define RCC_clock   RCC_AHBPeriphClockCmd // /Тактирование дисплея

/* Пины управления */
#define pin_rs		GPIO_Pin_6
#define pin_rw		GPIO_Pin_7
#define pin_e 		GPIO_Pin_8

/* Пины данных  */
#define pin_d4		GPIO_Pin_9
#define pin_d5		GPIO_Pin_10
#define pin_d6		GPIO_Pin_11
#define pin_d7		GPIO_Pin_12


/*Операции с пинами управления дисплея*/
#define rs_1	GPIO_SetBits   (port, pin_rs);
#define rs_0	GPIO_ResetBits (port, pin_rs);
#define e_1 	GPIO_SetBits   (port, pin_e);
#define e_0		GPIO_ResetBits (port, pin_e);
#define rw_1	GPIO_SetBits   (port, pin_rw)
#define rw_0	GPIO_ResetBits (port, pin_rw);




void Init_pin_out(void);
void Init_lcd(void);
void Lcd_write_data(uint8_t byte);
void Lcd_write_cmd(uint8_t byte);
void Lcd_clear(void);
void Return_home(void);
void Lcd_goto(uint8_t x, uint8_t y);
void Lcd_write_str(uint8_t *STRING);
void Lcd_clear_cell(uint8_t x, uint8_t y);
void write_byte(uint8_t byte);
void reset_byte();
void StrobReset();
#endif
