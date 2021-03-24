#include "weh1602_driver.h"
#include "avr/io.h"
#include "util/delay.h"
#include "avr/pgmspace.h"

uint8_t u8_Send_byte_v1(uint8_t i);
uint8_t u8_TableLCD(uint8_t c);

uint8_t	u8_TableHD44780[64]	PROGMEM =
{
	0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,
	0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
	0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,
	0xAC,0xE2,0xAD,0xAE,0xAD,0xAF,0xB0,0xB1,
	0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,
	0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
	0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,
	0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7
};

//uint8_t u8_Char_Timer[8] = {0, 0, 0x0e, 0x15, 0x17, 0x11, 0x0e, 0};

//uint8_t u8_play_symbol[8] = {0, 0, 0x2, 0x6, 0xe, 0x6, 0x2, 0};
//uint8_t u8_pause_symbol[8] = {0, 0, 0x0a, 0x1f, 0x1f, 0x1f, 0, 0};

//uint8_t u8_solar_bat_symbol[8] = {0, 0xa, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0};
//uint8_t u8_xp_symbol1[8] = {0, 0xa, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0};

uint8_t u8_lead_battery_symbol_charge_3_3[8] = { 0x0a, 0x1f, 0X1F, 0x1f, 0x1f, 0x1f, 0, 0};
uint8_t u8_lead_battery_symbol_charge_2_3[8] = { 0x0a, 0x1f, 0x11, 0x1f, 0x1f, 0x1f, 0, 0};
uint8_t u8_lead_battery_symbol_charge_1_3[8] = { 0x0a, 0x1f, 0x11, 0X11, 0x1f, 0x1f, 0, 0};
uint8_t u8_lead_battery_symbol_charge_0_3[8] = { 0x0a, 0x1f, 0x11, 0X11, 0X11, 0x1f, 0, 0};

uint8_t u8_solar_battery_symbol[8] = {0x1f, 0x15, 0x1f, 0x15, 0x1f, 0x4, 0xe, 0};

uint8_t u8_xp_symbol[8] = {0xa, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x4, 0};

uint8_t u8_arrow_symbol[8] = {0, 0, 0xc, 0x6, 0xc, 0, 0, 0};

uint8_t u8_Char_Timer[8] = {0, 0, 0x0e, 0x15, 0x17, 0x11, 0x0e, 0};

/********************************************************************/

void Driver_Low_Level_Init(void)
{
	DDRG |= (1<<2);
	_delay_ms(500);
	
	PORTG &= ~(1<<2);
	//_delay_ms(500);
	
	
	v_LCDInit_v1();
	
	CCRAM_Load();
}
/**/

void 	v_LCDInit_v1(void)
{
	_delay_ms(50);
	
	CDDR	|=  (1<<RS)|(1<<E)|(1<<RW);
	CPORT	&=~	((1<<RS)|(1<<E)|(1<<RW));
	DDDR 	=	0xFF;
	DPORT	=	0;
	
	DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4)|(0<<DB3)|(0<<DB2)|(0<<DB1)|(0<<DB0);
	
	CPORT |= (1<<E);
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	CPORT &= ~(1<<E);
	
	_delay_ms(5);
		
	CPORT |= (1<<E);
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	CPORT &= ~(1<<E);
	
	_delay_us(100);
		
	CPORT |= (1<<E);
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	CPORT &= ~(1<<E);
	
	_delay_us(100);
	
	/*for (i = 0; i < 3; i++)
	{
		CPORT |= (1<<E);
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		CPORT &= ~(1<<E);
	}*/
	
	DPORT = 0;
	
	//v_LCDSend_v1(LCD_CMD, (uint8_t)0b00111010);	//8ми битный интерфейс, две строки, 5x8 точек.
	v_LCDSend_v1(LCD_CMD, 0x3A);	//8ми битный интерфейс, две строки, 5x8 точек.
	_delay_us(100);
	
	//v_LCDSend_v1(LCD_CMD, (uint8_t)0b1100);		//Включаем дисплей + без отображения курсоров.
	v_LCDSend_v1(LCD_CMD, 0x0C);		//Включаем дисплей + без отображения курсоров.
	_delay_us(100);
	
	//v_LCDSend_v1(LCD_CMD, (uint8_t)0b110);		//Счетчик адреса всегда будет смещаться на n+1
	v_LCDSend_v1(LCD_CMD, 6);
	_delay_us(100);
	
	//v_LCDSend_v1(LCD_CMD, (uint8_t)0b10);		//курсор в позицию 0,0 + сброс всех сдвигов
	v_LCDSend_v1(LCD_CMD, 2);
	_delay_us(100);
	
	//v_LCDSend_v1(LCD_CMD, (uint8_t)0b1);			//очистка дисплея
	v_LCDSend_v1(LCD_CMD, 1);
	_delay_ms(3);
	
	//CPORT |= (1<<RW);
	DDDR = 	0;
}
/**/

void 	v_LCDGotoXY_v1(uint8_t x,uint8_t y)
{
	 uint8_t Address;
	
	switch(y)
	{
		case 0: Address = LINE0+x; 
				break;
		case 1: Address = LINE1+x; 
				break;
		default: Address = LINE0+x;
	}
	
	v_LCDSend_v1(LCD_CMD, (0x80 | Address));
}
/**/

uint8_t		u8_Send_byte_v1(uint8_t i)
{
	uint8_t u8_Retval = 0;
	
	if ((i&1)==1)
		u8_Retval |=(1<<DB0);
	i=i>>1;
			
	if ((i&1)==1)
		u8_Retval |=(1<<DB1);
	i=i>>1;
			
	if ((i&1)==1)
		u8_Retval |=(1<<DB2);
	i=i>>1;
			
	if ((i&1)==1)
		u8_Retval |=(1<<DB3);
	i=i>>1;
			
	if ((i&1)==1)
		u8_Retval |=(1<<DB4);
	i=i>>1;
		
	if ((i&1)==1)
		u8_Retval |=(1<<DB5);
	i=i>>1;
			
	if ((i&1)==1)
		u8_Retval |=(1<<DB6);
	i=i>>1;
			
	if ((i&1)==1)
		u8_Retval |=(1<<DB7);
		
	return u8_Retval;
}

void	v_LCDSend_v1(LCDSend_Type_t type, uint8_t i)
{
	uint8_t	u8_Tmp1 = 0;

	DDDR =0xFF;
	DPORT=0;
	
	if (type == LCD_ASCII)
	{
		u8_Tmp1 = u8_Send_byte_v1(u8_TableLCD(i));
		CPORT |= (1<<RS);
	}
	else if (type == LCD_CMD)
	{
		u8_Tmp1 = i;
		CPORT &= ~(1<<RS);
	}
	else if (type == LCD_BYTE)
	{
		u8_Tmp1 = u8_Send_byte_v1(i);
		CPORT |= (1<<RS);
	}
	
	CPORT &= ~(1<<RW);
	
	DPORT = u8_Tmp1;
	CPORT |= (1<<E);
	
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	
	CPORT &= ~(1<<E);
	DPORT = 0;
	CPORT |= (1<<RW);
	if ((type == LCD_ASCII) | (type == LCD_BYTE))
		CPORT &= ~(1<<RS);
	else if (type == LCD_CMD)
		CPORT |= (1<<RS);
	
	DDDR = 	0;
}
/**/

uint8_t u8_TableLCD(uint8_t c)
{

	if  (c > 191)
	{
		c -=192;
		c= pgm_read_byte(&u8_TableHD44780[c]);
	}

	return c;
}
/**/

void
CCRAM_Load(void)
{
	uint8_t i;
	
	//1
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_SOLAR_BAT) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_solar_battery_symbol[i]);
	}
	
	//2
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_LEAD_BAT_0_3) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_lead_battery_symbol_charge_0_3[i]);
	}
	
	//2
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_XP) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_xp_symbol[i]);
	}
	
	//4
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_ARROW) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_arrow_symbol[i]);
	}
	
	//5
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_TIMER) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_Char_Timer[i]);
	}
	
	//6
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_LEAD_BAT_1_3) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_lead_battery_symbol_charge_1_3[i]);
	}
	
	//7
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_LEAD_BAT_2_3) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_lead_battery_symbol_charge_2_3[i]);
	}
	
	//8
	v_LCDSend_v1(LCD_CMD, (CCRAM(SYM_LEAD_BAT_3_3) | 0x40));
	for (i = 0; i < 8; i++)
	{
		v_LCDSend_v1(LCD_BYTE, u8_lead_battery_symbol_charge_3_3[i]);
	}
}

void
Update_ccram_symbols(void)
{
	static uint16_t u16_Count = 0;
	uint8_t i;
	
	//if (u16_Count >= 40)
	//{
		if (1)
		{
			v_LCDSend_v1(LCD_CMD, (0x0 | 0x80));
			v_LCDSend_v1(LCD_BYTE, 1);
		}
		else
		{
		//	v_LCDSend_v1(LCD_CMD, (0x0 | 0x80));
		//	v_LCDSend_v1(LCD_ASCII, ' ');
		}
	//}
	
	
	if (u16_Count >= 80)
	{
		u16_Count = 0;
	}
	else
		u16_Count++;
}
