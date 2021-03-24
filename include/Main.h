#ifndef _MAIN_H_
#define _MAIN_H_

#define		__SFR_OFFSET 					0x20
#define		SREG 							_SFR_IO8(0x3F)
#define 	F_CPU 							11059200UL
#define 	BAUD							115200
#define 	USART_BRATE 					19200
#define 	UBRATE 							(F_CPU/16/USART_BRATE) - 1

#define _DEBUG_


//void UART_TX_8b(uint8_t* txData, uint8_t lenght);

#endif