#include "main.h"
#include "weh1602_driver.h"
#include "Menu.h"
#include "DisplayFormatter.h"
#include "libc/avr/io.h"
#include "libc/avr/interrupt.h"
#include "util/delay.h"
#include "Types.h"
#include "Modbus.h"
#include <util/setbaud.h>
#include "compat/ina90.h"
#include "DataConvert.h"

extern Element_t* p_List;
Msg_t Msg;
//extern RamDataContainer_t RamData;
//extern Element_t Element[];
extern Element_t Element1[MAIN_MENU_DIM_X][MAIN_MENU_DIM_Y];
//extern RamDataContainer_t* pRam[];
//extern RamList_t* p_ram_list;



RamDataContainer_t RamData;
RamDataContainer_t RamData1;
//RamDataContainer_t* pRam[] = {&RamData, &RamData1};
RamList_t st_ram_list = {.p_ram_main = &RamData, .p_ram_parview = &RamData1};
RamList_t* p_ram_list = &st_ram_list;



void Modbus_MSP_Init(void);
void Buttons_Init(void);

int
main(void)
{
	
	
	/*
		1. 	процедура инициализации дисплея и вывод строки «init…».
	*/
	Driver_Low_Level_Init();
	
	v_LCDSend_v1(LCD_CMD, (0x00 | 0x80));
	v_LCDSend_v1(LCD_ASCII, 'Р');
	v_LCDSend_v1(LCD_ASCII, 'а');
	v_LCDSend_v1(LCD_ASCII, 'с');
	v_LCDSend_v1(LCD_ASCII, 'х');
	v_LCDSend_v1(LCD_ASCII, 'о');
	v_LCDSend_v1(LCD_ASCII, 'д');
	
	
	//p_ram_list->type = RAM_MAIN;
	
	p_ram_list->p_ram_main->pList = &(Element1[0][0]);
	p_ram_list->p_ram_main->Level = LEVEL0;
	//p_ram_list->p_ram_main->pData = &(p_ram_list->p_ram_main->Data1);
	p_ram_list->p_ram_main->pData = NULL;
	p_ram_list->p_ram_main->Data1.pv = NULL;
	p_ram_list->p_ram_main->Data1.Type = 0;
	p_ram_list->p_ram_main->Blank_Menu = false;
	
	//p_ram_list->p_ram_parview->pList = &(Element1[0][0]);
	//RunnerStartPoint(p_ram_list->p_ram_parview->pList);
	p_ram_list->p_ram_parview->pList = &(Element1[0][1]);
	p_ram_list->p_ram_parview->Level = LEVEL0;
	p_ram_list->p_ram_parview->pData = NULL;
	p_ram_list->p_ram_parview->Data1.pv = NULL;
	p_ram_list->p_ram_parview->Data1.Type = 0;
	p_ram_list->p_ram_parview->Blank_Menu = false;
	
	

	
	/*
		3.	Выполняется один раз после включения для заполнения контейнера RAM данными. 
		Указатель p_List должен быть определен перед вызовом
	*/
	
	p_ram_list->p_now = p_ram_list->p_ram_parview;
	Refresh(p_ram_list->p_ram_parview->pList);
	
	p_ram_list->p_now = p_ram_list->p_ram_main;
	Refresh(p_ram_list->p_now->pList);
	
	
	
	
	
	
	
	
	Convert_Init();
	//Init();
	//Modbus_MSP_Init();
	Buttons_Init();
	
	/*
		8. 	Запуск таймеров
	*/
	TCCR1A |= _BV(WGM11);
	TCCR1B |= _BV(CS11) | _BV(CS10);
	
	sei();
	
	for (;;) {
		_delay_ms(20);
		//PORTD ^= 1<<5;
	}
	return 0;
}

void
Modbus_MSP_Init(void)
{
	TIMSK = _BV(OCIE0) | _BV(TOIE1) | _BV(OCIE2) | _BV(TOIE2);
	OCR0 = 220;
	OCR2 = 233;
	
	TCNT0 = 0;
	TCNT2 = 0;
	TCNT1L = 0;
	TCNT1H = 0;
	
	UBRR1L = UBRRL_VALUE;
	UBRR1H = UBRRH_VALUE;
	#if USE_2X
	UCSR1A |= (1 << U2X);
	#else
	UCSR1A &= ~(1 << U2X);
	#endif
	
	UCSR1B = _BV(TXEN1) | _BV(RXEN1);
	UCSR1C = _BV(UCSZ11) | _BV(UCSZ10) | _BV(USBS1);
	while (!(UCSR1A & (1<<UDRE1))){
		_NOP();
	}
	
	DDRD |= (1<<4) | (1<<0) | (1<<1) | (1<<5) | (1<<6) | (1<<7);
	
	//PORTG &= ~(1<<2);
}
/**/

void
Buttons_Init(void)
{
	//ENABLE BUTTONS
	DDRC &= ~((1<<0) | 
		(1<<1) |
		(1<<2) |
		(1<<3)) ;
	DDRG &= ~((1<<0) | 
		(1<<1)) ;
}
/**/

