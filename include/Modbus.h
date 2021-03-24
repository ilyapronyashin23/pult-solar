#ifndef	_MODBUS_H_
#define	_MODBUS_H_

//#include "stm32f1xx_hal.h"
//#include	"Global.h"
#include "stdlib.h"
//#include	"General.h"
#include "inttypes.h"
#include "Types.h"
#include "Menu.h"
#include "ModbusProtocolTable.h"

//SLAVE
#define MAX_ALLOWED_DATABYTES_SLAVE_NUM_RX_X04	5
#define MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X04		8
#define MAX_ALLOWED_BYTES_NUM_SLAVE_TX_X04		5 + 2*MAX_ALLOWED_DATABYTES_SLAVE_NUM_RX_X04
#define MAX_ALLOWED_DATABYTES_SLAVE_NUM_RX_X10	2
#define MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X10		9 + 2*MAX_ALLOWED_DATABYTES_SLAVE_NUM_RX_X10
#define MAX_ALLOWED_BYTES_NUM_SLAVE_TX_X10		8

//MASTER
#define MAX_ALLOWED_DATABYTES_NUM_MASTER_X04	64
#define MAX_ALLOWED_BYTES_NUM_MASTER_X04		5 + 2*MAX_ALLOWED_DATABYTES_NUM_MASTER_X04
#define START_INDEX_DATABYTES_NUM_MASTER_X10	0
#define MAX_ALLOWED_DATABYTES_NUM_MASTER_X10	MAX_ALLOWED_DATABYTES_NUM_MASTER_X04
#define MAX_ALLOWED_BYTES_NUM_MASTER_X10		8

enum			en_Next_Send_Function;

typedef	enum	en_Next_Send_Function	Next_Send_Function_t;

enum	en_Next_Send_Function
{
	F_X04 = 1,
	F_X10 = 2
};

typedef enum
{
	READY_START_BYTE = 1,
	READY_NEXT_BYTE,
	BLOCKING_ANY_BYTE
}
en_Status_t;

typedef enum
{
	UNK = 0,
	//FUNC_CODE_MASTER_X04 = MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X04,	//ÂÑÅ ÄÀÍÍÛÅ ÁÅÇ ÀÄÐÅÑÀ
	FUNC_CODE_MASTER_X04 = MAX_ALLOWED_BYTES_NUM_MASTER_X04,
	//FUNC_CODE_MASTER_X10 = MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X10	//
	FUNC_CODE_MASTER_X10 = MAX_ALLOWED_BYTES_NUM_MASTER_X10	
}
en_BytesNumber_t;

typedef enum
{
	OK = 0,
	TOO_MANY_BYTES,
	BYTES_CONFUSED,
	BYTES_MISSING,
	WRONG_FUNC_CODE,
	BAD_CRC,
	WRONG_START_POS,
	WRONG_BYTES_NUM,
	WRONG_REQ_NUM,
	
	NO_ANSWER
}
en_ErrorCode_t;

typedef struct
{
	bool TOO_MANY_BYTES;
	bool WRONG_FUNC_CODE;
}
st_Flags;

typedef struct
{
	uint8_t*		p_Bytes;
	en_ErrorCode_t	ERROR_CODE;
}
st_ReceivedData_t;

typedef struct
{
	uint8_t*	p_Bytes;
	bool		LAST_BYTE_SENT;
}
st_TransmitData_t;

typedef struct
{
	uint8_t					ADDRESS_SLAVE;
	en_Status_t				Status;
	bool					WAIT_SLAVE_ANSWER;
	uint8_t 				RX_BYTES_IN_BLOCKING_MODE;
	uint8_t*				p_Temp_Data;
	uint8_t					BYTE_COUNT;
	bool					READY_TO_PROCESS;
	en_BytesNumber_t		BYTES_NUMBER;
	uint8_t					FUNC_CODE;
	st_Flags				Flags;
	uint16_t				REQ_BYTES_START_POS;						//ONLY IN SLAVE MODE
	uint16_t				REQ_BYTES_NUM;								//ONLY IN SLAVE MODE
}
st_Modbus_t;

typedef struct
{
	uint8_t					ADDRESS_ME;
	en_Status_t				Status;
	uint8_t 				RX_BYTES_IN_BLOCKING_MODE;
	uint8_t*				p_Temp_Data;
	uint8_t					BYTE_COUNT;
	bool					READY_TO_PROCESS;
	en_BytesNumber_t		BYTES_NUMBER;
	uint8_t					FUNC_CODE;
	st_Flags				Flags;
	uint16_t				REQ_BYTES_START_POS;						//ONLY IN SLAVE MODE
	uint16_t				REQ_BYTES_NUM;								//ONLY IN SLAVE MODE
}
st_SLAVE_Modbus_t;
//st_ModbusMaster_t;

typedef struct
{
	uint16_t	ADC1_Value;
	uint16_t	ADC2_Value;
	uint16_t	ADC3_Value;
	uint16_t	ADC4_Value;
}
st_DataRegs_t;

typedef struct
{
	bool 		InvEnabled;
	uint16_t	PWM;
}
st_ControlRegs_t;

/******************************************************************/

typedef struct
{
	st_Modbus_t	Modbus;
	void		(*pv_Receive)(void*, uint8_t);
	void		(*pv_Timer_Compare)(void*);
	st_ReceivedData_t	Received_Data;
	st_TransmitData_t	Transmit_Data;
}
st_Master_t;

typedef struct
{
	st_SLAVE_Modbus_t	Modbus;
	void		(*pv_Receive)(void*, uint8_t);
	void		(*pv_Timer_Compare)(void*);
	st_ReceivedData_t	Received_Data;
	st_TransmitData_t	Transmit_Data;
}
st_Slave_t;

typedef	struct
{
	bool	b_Res;
	uint8_t	u8_Count;
}
st_NoAnswer_t;

void 	Master_Receive(void*, uint8_t);
void	Master_Timer_Compare(void*);
bool 	MASTER_Process_Receive(st_Master_t*	ldev);
bool 	SLAVE_Process_Receive(st_Slave_t*	ldev);
void 	Clear_Struct(st_Master_t*	ldev);
void 	Timer_Reset(void);
void 	Timer_Reset_And_Start_x32(void);
void 	Timer_Reset_And_Start_x128(void);
void 	Timer_Reset_And_Start_x1024(void);
void 	Timer_Stop(void);
void 	Timer_Change_Compare(uint8_t value);
uint16_t CRC16_2(const uint8_t *nData, uint16_t wLength);
void 	UART_TX_8b(uint8_t* txData, uint8_t lenght);
//void 	Send(void);
void Init(void);
bool Process_Transmit(void);
void Modbus_MSP_Init(void) __attribute__((weak));

void Send_Switch( RamList_t* ram_list );
void Send_X10( RamList_t* ram_list );
void Send_X04(void);
void v_SendDateTime(uint8_t* len);
void usart_putchar(uint8_t c);

#endif