#ifndef	_WEH1602_H_
#define	_WEH1602_H_

#include	"stdint.h"
//#include	"High_Level.h"

#define SYM_LENGHT (16)
#define BUF_LENGHT (SYM_LENGHT+1)

#define DPIN  PINA
#define DDDR  DDRA
#define DPORT PORTA

#define DB0	0// DB0
#define DB1	1// DB1
#define DB2	2// DB2	
#define DB3	3// DB3		
#define DB4	4// DB4  
#define DB5	5// DB5
#define DB6	6// DB6
#define DB7	7// DB7 + BF флаг занятости дисплея.

//Указываем порт к которому подключены выводы дисплея E, RS, R/W.
#define CDDR  DDRC
#define CPORT PORTC

#define E	5	// E	 СТРОБ.
#define RW	6   // R/W   R/W=1 читаем из LCD, R/W=0 записываем в LCD.
#define RS	7 	// RS	 RS=0 посылаем команду в LCD, RS=1 посылаем данные в LCD.

#define LINE0 0x00
#define LINE1 0x40

/*
#define SYM_SOLAR_BAT		1
#define	SYM_LEAD_BAT_3_3	2
#define	SYM_LEAD_BAT_2_3	3
#define	SYM_LEAD_BAT_1_3	4
#define	SYM_LEAD_BAT_0_3	5
#define	SYM_XP				6
#define	SYM_ARROW			7
#define	SYM_TIMER			8
*/

#define CCRAM(a) (uint8_t)(a * 8)

typedef enum en_LCDSend_Type
{
	LCD_BYTE = 0,
	LCD_CMD,
	LCD_ASCII	
}
LCDSend_Type_t;

typedef enum {
	SYM_SOLAR_BAT 		= 1,
	SYM_LEAD_BAT_3_3 	= 8,
	SYM_LEAD_BAT_2_3	= 7,
	SYM_LEAD_BAT_1_3 	= 6,
	SYM_LEAD_BAT_0_3 	= 2,
	SYM_XP			 	= 3,
	SYM_ARROW 			= 4,
	SYM_TIMER 			= 5
} CCRAM_Symbol_t;

void Driver_Low_Level_Init(void);
void v_LCDSend_v1(LCDSend_Type_t type, uint8_t i);
void v_LCDGotoXY_v1(uint8_t x,uint8_t y);
void v_LCDInit_v1(void);
void CCRAM_Load(void);
void Update_ccram_symbols(void);

#endif