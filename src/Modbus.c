#include 	"Modbus.h"
//#include	"High_Level.h"
//#include	"Convert.h"

#include "avr/io.h"
#include "util/delay.h"
#include "compat/ina90.h"
#include "DataConvert.h"
#include "ConvertToSerial.h"


//extern TIM_HandleTypeDef	hTIM3;
st_Master_t dev;
//extern	Dynamic_Data_t			RAM_Data;
//extern	uint16_t				u16_tmp_1;
//extern	uint16_t				u16_tmp_2;
//extern	uint16_t				u16_tmp_3;
//extern	uint8_t			Level;
//extern UART_HandleTypeDef 	hUart;

uint32_t 					Succesful_Cnt = 0;
uint32_t 					Error_Cnt = 0;
Next_Send_Function_t		Next_Send_Function = F_X04;
st_NoAnswer_t				NoAnswer = 
{
	.b_Res = false,
	.u8_Count = 0
};
extern	Msg_t				Msg;
//extern	TMS320_t			Endpoint;

//st_DataRegs_t st_DataRegs = {0, 1, 2, 4, 0, false};
st_DataRegs_t 		st_DataRegs = {1, 1, 1, 1};
st_ControlRegs_t	st_ControlRegs = {false, 0};

//extern uint8_t TxBuffer[32];

void 	Init(void)
{
	
	//dev.Modbus.ADDRESS_ME						= 1;
	dev.Modbus.ADDRESS_SLAVE					= 1;
	dev.Modbus.WAIT_SLAVE_ANSWER				= 0;
	dev.Modbus.Status 							= READY_START_BYTE;
	dev.Modbus.RX_BYTES_IN_BLOCKING_MODE 	= 0;
	dev.Modbus.BYTE_COUNT						= 0;
	dev.Modbus.READY_TO_PROCESS				= false;
	dev.Modbus.BYTES_NUMBER					= UNK;
	dev.Modbus.FUNC_CODE						= 0;
	dev.Modbus.Flags.WRONG_FUNC_CODE			= false;
	dev.Modbus.Flags.TOO_MANY_BYTES			= false;
	
	//dev.Modbus.
	
	dev.Modbus.p_Temp_Data = malloc(1*sizeof(uint8_t));
	
	
	//dev.Received_Data.p_Bytes 		 		= malloc(MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X10 * sizeof(uint8_t));
	dev.Received_Data.p_Bytes 		 		= malloc(MAX_ALLOWED_BYTES_NUM_MASTER_X04 * sizeof(uint8_t));
	dev.Received_Data.ERROR_CODE	 			= OK;
	//dev.Transmit_Data.p_Bytes 		 		= malloc(MAX_ALLOWED_BYTES_NUM_SLAVE_TX_X04 * sizeof(uint8_t));
	dev.Transmit_Data.p_Bytes 				= malloc(MAX_ALLOWED_BYTES_NUM_MASTER_X10 * sizeof(uint8_t));
	dev.Transmit_Data.LAST_BYTE_SENT			= false;

	dev.pv_Receive 							= &Master_Receive;
	dev.pv_Timer_Compare 						= &Master_Timer_Compare;
	
	Modbus_MSP_Init();
}
/**/

void	Modbus_MSP_Init(void)
{
	
}
/**/


void
Send_Switch( RamList_t* ram_list ) {
	
	Timer_Stop();
	Timer_Reset();
	Clear_Struct(&dev);
	dev.Modbus.Status = READY_START_BYTE;
	
	
	switch (Next_Send_Function) {
		case F_X04:
			Send_X04();
		break;
		case F_X10:
			Send_X10(ram_list);
			Next_Send_Function = F_X04;
		break;
		default:
			return;
		break;
	}
	
	// ok request
	PORTD ^= 1<<7;
}
/**/

void
Send_X10( RamList_t* ram_list )
{
	uint16_t CRCb;
	uint8_t len = 0;
	
	
	
	if (dev.Transmit_Data.p_Bytes != NULL)
	{
		free(dev.Transmit_Data.p_Bytes);
		dev.Transmit_Data.p_Bytes = NULL;
	}
	dev.Transmit_Data.p_Bytes = malloc(15*sizeof(uint8_t));
	
	/*
	dev.Transmit_Data.p_Bytes[1] = 6;
	dev.Transmit_Data.p_Bytes[2] = 2;
	dev.Transmit_Data.p_Bytes[3] = 0;
	//dev.Transmit_Data.p_Bytes[4] = (uint8_t)((Msg.Value.ret.s16 & 0xff00)>>8);
	//dev.Transmit_Data.p_Bytes[5] = (uint8_t)(Msg.Value.ret.s16 & 0x00ff);
	dev.Transmit_Data.p_Bytes[4] = (uint8_t)((ramdata->Msg.st.ret.u16 & 0xff00)>>8);
	dev.Transmit_Data.p_Bytes[5] = (uint8_t)(ramdata->Msg.st.ret.u16 & 0x00ff);
	
	u8_Len = 8;
	*/
	
	dev.Transmit_Data.p_Bytes[0] = INTERFACE_BOARD_ADDR;
	ConvSerial_Write(ram_list, dev.Transmit_Data.p_Bytes, &len);
	
	/*
	dev.Transmit_Data.p_Bytes[1] = 6;
	dev.Transmit_Data.p_Bytes[2] = 2;
	dev.Transmit_Data.p_Bytes[3] = 0;
	dev.Transmit_Data.p_Bytes[4] = 0;
	dev.Transmit_Data.p_Bytes[5] = 255;
	len = 8;
	*/
	
	
	
	CRCb = CRC16_2(dev.Transmit_Data.p_Bytes, len-2);
	dev.Transmit_Data.p_Bytes[len-2]  = (uint8_t)(CRCb & 0x00ff);
	dev.Transmit_Data.p_Bytes[len-1] = (uint8_t)((CRCb & 0xff00)>>8);
	UART_TX_8b(dev.Transmit_Data.p_Bytes, len);
	if (NoAnswer.u8_Count < 255)
		NoAnswer.u8_Count += 1;
}
/**/

void
v_SendDateTime(uint8_t* len)
{
	/*
	dev.Transmit_Data.p_Bytes[1] = 0x10;
	//dev.Transmit_Data.p_Bytes[2] = Msg.Transmit.Page;
	//dev.Transmit_Data.p_Bytes[3] = Msg.Transmit.Register;
	dev.Transmit_Data.p_Bytes[4] = 0;
	dev.Transmit_Data.p_Bytes[5] = 2;
	dev.Transmit_Data.p_Bytes[6] = 4;
					
	
					
	dev.Transmit_Data.p_Bytes[7] = (uint8_t)((u16_tmp_1 & 0xff00)>>8);
	dev.Transmit_Data.p_Bytes[8] = (uint8_t)(u16_tmp_1 & 0x00ff);
	dev.Transmit_Data.p_Bytes[9] = (uint8_t)((u16_tmp_2 & 0xff00)>>8);
	dev.Transmit_Data.p_Bytes[10] = (uint8_t)(u16_tmp_2 & 0x00ff);
					
	*len = 13;
	*/
}
/**/

void 	Send_X04(void)
{
	uint16_t CRCb;
	
	if (dev.Transmit_Data.p_Bytes != NULL)
	{
		free(dev.Transmit_Data.p_Bytes);
		dev.Transmit_Data.p_Bytes = NULL;
	}
	dev.Transmit_Data.p_Bytes = malloc(8*sizeof(uint8_t));
	
	dev.Transmit_Data.p_Bytes[0] = 1;
	dev.Transmit_Data.p_Bytes[1] = 3;
	dev.Transmit_Data.p_Bytes[2] = 0;
	dev.Transmit_Data.p_Bytes[3] = 0;
	dev.Transmit_Data.p_Bytes[4] = 0;
	dev.Transmit_Data.p_Bytes[5] = 0;
	dev.Transmit_Data.p_Bytes[6] = 0;
	dev.Transmit_Data.p_Bytes[7] = 0;
	
	
	
	dev.Modbus.BYTES_NUMBER = (5 + 2*FillMsg(dev.Transmit_Data.p_Bytes, 8));
	
	CRCb = CRC16_2(dev.Transmit_Data.p_Bytes, 6);
	dev.Transmit_Data.p_Bytes[6]  = (uint8_t)(CRCb & 0x00ff);
	dev.Transmit_Data.p_Bytes[7] = (uint8_t)((CRCb & 0xff00)>>8);
	
	UART_TX_8b(dev.Transmit_Data.p_Bytes, 8);
	if (NoAnswer.u8_Count < 255)
		NoAnswer.u8_Count += 1;
}
/**/

void 	Master_Receive(void* device, uint8_t rdata)
{
	st_Master_t*	ldev	= (st_Master_t*)device;
	uint8_t Tmp;
	
	if (ldev->Modbus.Status == READY_START_BYTE)
	{
		if (rdata == ldev->Modbus.ADDRESS_SLAVE)
		{
			//перводим в Wait rx
			//ЗАПУСКАЕМ ТИМЕР
			
			PORTD ^= 1<<6;
			
			ldev->Modbus.WAIT_SLAVE_ANSWER 	= true;
			ldev->Modbus.Status 			= READY_NEXT_BYTE;
			ldev->Modbus.BYTE_COUNT 		= 1;
			ldev->Modbus.p_Temp_Data[0] 	= rdata;
			
			Timer_Stop();
			Timer_Change_Compare(66);	//1146 us = 2xT
			//Timer_Reset_And_Start_x128();
			Timer_Reset_And_Start_x32();
		}
	}
	else
	{
		if (ldev->Modbus.Status == READY_NEXT_BYTE)
		{
			if (ldev->Modbus.Flags.TOO_MANY_BYTES | ldev->Modbus.Flags.WRONG_FUNC_CODE )
			{
				Timer_Stop();
				Timer_Reset();
				Clear_Struct(&dev);
				dev.Modbus.Status = READY_START_BYTE;
			}
			else
			{
				Timer_Reset();
				
				if (ldev->Modbus.BYTE_COUNT == 1)
				{
					switch (rdata){
						case 0X3:
							ldev->Modbus.FUNC_CODE 				= 0X03;
						case 0X4:
							//ldev->Modbus.BYTES_NUMBER 			= FUNC_CODE_MASTER_X04;
							ldev->Modbus.FUNC_CODE 				= 0X04;
							ldev->Modbus.Flags.WRONG_FUNC_CODE 	= false;
							
							Tmp = dev.Modbus.p_Temp_Data[0];
							
							if (dev.Modbus.p_Temp_Data != NULL)
							{
								free(dev.Modbus.p_Temp_Data);
								dev.Modbus.p_Temp_Data = NULL;
							}
							
							dev.Modbus.p_Temp_Data = malloc(ldev->Modbus.BYTES_NUMBER*sizeof(uint8_t));
							dev.Modbus.p_Temp_Data[0] = Tmp;
							break;
						case 0X10:
							ldev->Modbus.BYTES_NUMBER 			= FUNC_CODE_MASTER_X10;
							ldev->Modbus.FUNC_CODE 				= 0X10;
							ldev->Modbus.Flags.WRONG_FUNC_CODE 	= false;
							
							free(dev.Modbus.p_Temp_Data);
							dev.Modbus.p_Temp_Data = malloc(ldev->Modbus.BYTES_NUMBER*sizeof(uint8_t));
							break;
						default:
							ldev->Modbus.BYTES_NUMBER 			= UNK;
							ldev->Modbus.FUNC_CODE 				= 0;
							ldev->Modbus.Flags.WRONG_FUNC_CODE 	= true;
					}
				}
				if (ldev->Modbus.BYTE_COUNT < ldev->Modbus.BYTES_NUMBER)
				{
					ldev->Modbus.p_Temp_Data[ldev->Modbus.BYTE_COUNT] = rdata;
					
					//if ((ldev->Modbus.BYTE_COUNT == 6) & (ldev->Modbus.FUNC_CODE == 0X10)){
					//	ldev->Modbus.BYTES_NUMBER = 9 + rdata;
					//}
					
					if (ldev->Modbus.BYTE_COUNT == (ldev->Modbus.BYTES_NUMBER - 1)){
						ldev->Modbus.READY_TO_PROCESS = true;
						//TIFR = _BV(OCF0);
					}
					else ldev->Modbus.BYTE_COUNT++;
				}
				else
				{
					ldev->Modbus.Flags.TOO_MANY_BYTES = true;
					//TIFR = _BV(OCF0);
				}
			}
		}
		
		if (ldev->Modbus.Status == BLOCKING_ANY_BYTE)
		{
			ldev->Modbus.RX_BYTES_IN_BLOCKING_MODE++;
			
			if (ldev->Modbus.RX_BYTES_IN_BLOCKING_MODE > 128)
			{
				ldev->Modbus.RX_BYTES_IN_BLOCKING_MODE = 0;
				Timer_Stop();
				Timer_Reset();
				Clear_Struct(&dev);
				dev.Modbus.Status = READY_START_BYTE;
			}
		}
	}
}
/**/

void	Master_Timer_Compare(void* device)
{
	uint8_t i;
	st_Master_t*	ldev	= (st_Master_t*)device;
	
	Timer_Stop();
	
	if (!(ldev->Modbus.WAIT_SLAVE_ANSWER))
	{
		ldev->Received_Data.ERROR_CODE = NO_ANSWER;
		User_Callback(false);
		return;
	}
	
	if (ldev->Modbus.Status == READY_NEXT_BYTE)
	{
		if (ldev->Modbus.Flags.TOO_MANY_BYTES | ldev->Modbus.Flags.WRONG_FUNC_CODE)
		{
			//возникла проблема. сбрасываем
			for (i = 0; i < MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X10; i++)	ldev->Received_Data.p_Bytes[i] = 0;
			
			ldev->Modbus.Flags.TOO_MANY_BYTES ? 
				(ldev->Received_Data.ERROR_CODE = TOO_MANY_BYTES) : 
				(ldev->Received_Data.ERROR_CODE = ldev->Received_Data.ERROR_CODE) ;
				
			ldev->Modbus.Flags.WRONG_FUNC_CODE ? 
				(ldev->Received_Data.ERROR_CODE = WRONG_FUNC_CODE) : 
				(ldev->Received_Data.ERROR_CODE = ldev->Received_Data.ERROR_CODE) ;
			
			User_Callback(false);
			Clear_Struct(ldev);
			
		}
		else
		{
			ldev->Modbus.Status = BLOCKING_ANY_BYTE;
			
			Timer_Change_Compare(132);	//2292 us = 4xT
			//Timer_Reset_And_Start_x128();
			Timer_Reset_And_Start_x32();
			
		}
	}
	else if (ldev->Modbus.Status == BLOCKING_ANY_BYTE)
	{
		//окончание приема. если RX_BYTES_IN_BLOCKING_MODE ==0, проимходит проверка полученных данных
		//изменить OCR0
		
		if (ldev->Modbus.RX_BYTES_IN_BLOCKING_MODE == 0)
		{
			
			if (ldev->Modbus.READY_TO_PROCESS)
			{
				for (i = 0; i < ldev->Modbus.BYTES_NUMBER; i++)
					ldev->Received_Data.p_Bytes[i] = ldev->Modbus.p_Temp_Data[i];
				
				
				
				if (MASTER_Process_Receive(ldev))
				{
					ldev->Received_Data.ERROR_CODE = OK;
					User_Callback(true);
					
					NoAnswer.u8_Count = 0;
					NoAnswer.b_Res = false;
					//Process_Transmit();
					//PORTD ^= 1<<7;
					
				}
				else
				{
					ldev->Received_Data.ERROR_CODE = ldev->Received_Data.ERROR_CODE;
					User_Callback(false);
				}
			}
			else
			{
				for (i = 0; i < MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X10; i++)	ldev->Received_Data.p_Bytes[i] = 0;
				ldev->Received_Data.ERROR_CODE = BYTES_MISSING;
				
				User_Callback(false);
			}
		}
		else
		{
			
			for (i = 0; i < MAX_ALLOWED_BYTES_NUM_SLAVE_RX_X10; i++)	ldev->Received_Data.p_Bytes[i] = 0;
			ldev->Received_Data.ERROR_CODE = BYTES_CONFUSED;
			
			User_Callback(false);
		}

		Clear_Struct(ldev);
	}
}
/**/

bool 	Process_Transmit(void)
{
	uint8_t* txData = NULL;
	//uint8_t* p_txFrame = NULL;
	uint8_t i;
	uint16_t CRCb;
	
	switch (dev.Received_Data.p_Bytes[1])
	{
		case 0x04:
		{
			txData = malloc(2 * dev.Modbus.REQ_BYTES_NUM * sizeof(uint8_t));
	
			txData[0] = (uint8_t)((st_ControlRegs.PWM & 0xff00) >> 8);
			txData[1] = (uint8_t)(st_ControlRegs.PWM & 0xff);
			txData[2] = (uint8_t)((Succesful_Cnt & 0xff00) >> 8);
			txData[3] = (uint8_t)(Succesful_Cnt & 0xff);
			txData[4] = (uint8_t)((Error_Cnt & 0xff00) >> 8);
			txData[5] = (uint8_t)(Error_Cnt & 0xff);
			txData[6] = (uint8_t)((st_DataRegs.ADC4_Value & 0xff00) >> 8);
			txData[7] = (uint8_t)(st_DataRegs.ADC4_Value & 0xff);
			txData[8] = 0;
			if (st_ControlRegs.InvEnabled)	txData[9] = 1;
			else txData[9] = 0;
			
			
			if (dev.Transmit_Data.p_Bytes != NULL)
			{
				free(dev.Transmit_Data.p_Bytes);
				dev.Transmit_Data.p_Bytes = NULL;
			}
			dev.Transmit_Data.p_Bytes = malloc((2 * dev.Modbus.REQ_BYTES_NUM + 5)*sizeof(uint8_t));
			//p_txFrame = malloc((2 * Modbus.REQ_BYTES_NUM + 5)*sizeof(uint8_t));
			
			//*(dev.Transmit_Data.p_Bytes) = dev.Modbus.ADDRESS_ME;
			*(dev.Transmit_Data.p_Bytes) = dev.Modbus.ADDRESS_SLAVE;
			*(dev.Transmit_Data.p_Bytes + 1) = dev.Modbus.FUNC_CODE;
			*(dev.Transmit_Data.p_Bytes + 2) = 2 * dev.Modbus.REQ_BYTES_NUM;
			for (i = dev.Modbus.REQ_BYTES_START_POS; i <= dev.Modbus.REQ_BYTES_START_POS + dev.Modbus.REQ_BYTES_NUM; i++)
			{
				*(dev.Transmit_Data.p_Bytes + 2*(i - dev.Modbus.REQ_BYTES_START_POS) + 3) = txData[2*i];
				*(dev.Transmit_Data.p_Bytes + 2*(i - dev.Modbus.REQ_BYTES_START_POS) + 3 + 1) = txData[2*i + 1];
			}
			
			CRCb = CRC16_2(dev.Transmit_Data.p_Bytes, 2 * dev.Modbus.REQ_BYTES_NUM + 3);
			*(dev.Transmit_Data.p_Bytes + (2 * dev.Modbus.REQ_BYTES_NUM+3)) = (uint8_t)(CRCb & 0x00ff);
			*(dev.Transmit_Data.p_Bytes + (2 * dev.Modbus.REQ_BYTES_NUM+4)) = (uint8_t)((CRCb & 0xff00)>>8);
			
			UART_TX_8b(dev.Transmit_Data.p_Bytes, (2 * dev.Modbus.REQ_BYTES_NUM + 5));
			
			free(txData);
		}
		break;
		
		case 0x10:
		{
			if (dev.Transmit_Data.p_Bytes != NULL)
			{
				free(dev.Transmit_Data.p_Bytes);
				dev.Transmit_Data.p_Bytes = NULL;
			}
			dev.Transmit_Data.p_Bytes = malloc((MAX_ALLOWED_BYTES_NUM_SLAVE_TX_X10)*sizeof(uint8_t));
			//p_txFrame = malloc((2 * Modbus.REQ_BYTES_NUM + 5)*sizeof(uint8_t));
			
			//*(dev.Transmit_Data.p_Bytes) = dev.Modbus.ADDRESS_ME;
			//*(dev.Transmit_Data.p_Bytes) = dev.Modbus.ADDRESS_ME;
			*(dev.Transmit_Data.p_Bytes) = dev.Modbus.ADDRESS_SLAVE;
			*(dev.Transmit_Data.p_Bytes + 1) = dev.Modbus.FUNC_CODE;
			*(dev.Transmit_Data.p_Bytes + 2) = (uint8_t)((dev.Modbus.REQ_BYTES_START_POS & 0xff00)>>8);
			*(dev.Transmit_Data.p_Bytes + 3) = (uint8_t)(dev.Modbus.REQ_BYTES_START_POS & 0x00ff);
			*(dev.Transmit_Data.p_Bytes + 4) = (uint8_t)((dev.Modbus.REQ_BYTES_NUM & 0xff00)>>8);
			*(dev.Transmit_Data.p_Bytes + 5) = (uint8_t)(dev.Modbus.REQ_BYTES_NUM & 0x00ff);
			
			CRCb = CRC16_2(dev.Transmit_Data.p_Bytes, 6);
			*(dev.Transmit_Data.p_Bytes + 6) = (uint8_t)(CRCb & 0x00ff);
			*(dev.Transmit_Data.p_Bytes + 7) = (uint8_t)((CRCb & 0xff00)>>8);
			
			UART_TX_8b(dev.Transmit_Data.p_Bytes, MAX_ALLOWED_BYTES_NUM_SLAVE_TX_X10);
		}
		break;
	}
	
	

	return true;
}
/**/

bool 	MASTER_Process_Receive(st_Master_t*	ldev)
{
	uint16_t CRCb;
	uint16_t i = 0, j = 0;
	
	switch (ldev->Received_Data.p_Bytes[1])
	{
		case 0x03:
		case 0x04:
		{
			CRCb = CRC16_2(ldev->Received_Data.p_Bytes, ldev->Modbus.BYTES_NUMBER - 2);
			if (CRCb != ((ldev->Received_Data.p_Bytes[ldev->Modbus.BYTES_NUMBER-1]<<8) |
				ldev->Received_Data.p_Bytes[ldev->Modbus.BYTES_NUMBER-2]))
			{
				ldev->Received_Data.ERROR_CODE = BAD_CRC;
				return false;
			}
			
			if (ldev->Received_Data.p_Bytes[2] != ldev->Modbus.BYTES_NUMBER - 5)
			{
				ldev->Received_Data.ERROR_CODE = WRONG_BYTES_NUM;
				return false;
			}
		}
		break;
		
		case 0x10:
		{
			CRCb = CRC16_2(ldev->Received_Data.p_Bytes, ldev->Modbus.BYTES_NUMBER - 2);
			if (CRCb != ((ldev->Received_Data.p_Bytes[ldev->Modbus.BYTES_NUMBER-1]<<8) |
				ldev->Received_Data.p_Bytes[ldev->Modbus.BYTES_NUMBER-2]))
			{
				ldev->Received_Data.ERROR_CODE = BAD_CRC;
				return false;
			}
			
			i = (ldev->Received_Data.p_Bytes[2]<<8) | (ldev->Received_Data.p_Bytes[3]);
			if (i >= MAX_ALLOWED_DATABYTES_NUM_MASTER_X10)
			{
				ldev->Received_Data.ERROR_CODE = WRONG_START_POS;
				return false;
			}
			
			j = (ldev->Received_Data.p_Bytes[4]<<8) | ldev->Received_Data.p_Bytes[5];
			if ((j >= MAX_ALLOWED_DATABYTES_NUM_MASTER_X10 + 1) |
				(j = 0) |
				((i+j) > MAX_ALLOWED_DATABYTES_NUM_MASTER_X10))
			{
				ldev->Received_Data.ERROR_CODE = WRONG_BYTES_NUM;
				return false;
			}
		}
		break;
	}
	
	return true;
}

void 	Clear_Struct(st_Master_t*	ldev)
{
	uint8_t i;
	
	//ldev->Modbus.ADDRESS_SLAVE = 2;
	
	
	ldev->Modbus.Status = READY_START_BYTE;
	ldev->Modbus.RX_BYTES_IN_BLOCKING_MODE = 0;
	ldev->Modbus.BYTE_COUNT = 0;
	ldev->Modbus.READY_TO_PROCESS = false;
	ldev->Modbus.WAIT_SLAVE_ANSWER = false;
	
	ldev->Modbus.FUNC_CODE = 0;
	ldev->Modbus.Flags.TOO_MANY_BYTES = false;
	ldev->Modbus.Flags.WRONG_FUNC_CODE 	= false;
	ldev->Modbus.REQ_BYTES_START_POS = 0;
	ldev->Modbus.REQ_BYTES_NUM = 0;
	
	for (i = 0; i < ldev->Modbus.BYTES_NUMBER; i++)
	{
		ldev->Modbus.p_Temp_Data[i] = 0;
	}
	ldev->Modbus.BYTES_NUMBER = UNK;
	
}
/**/

uint16_t CRC16_2(const uint8_t *nData, uint16_t wLength)
{
    static const uint16_t wCRCTable[] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040};

    uint8_t nTemp;
    uint16_t wCRCWord = 0xFFFF;

    while (wLength--)
    {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord  ^= wCRCTable[(nTemp & 0xFF)];
    }
    return wCRCWord;
}
/**/

void
Timer_Reset()
{
	TCNT0 = 0;
}
/**/

void
Timer_Reset_And_Start_x128()
{
	TCNT0 = 0;
	TCCR0 = _BV(CS02) | _BV(CS00);
}
/**/

void
Timer_Reset_And_Start_x32()
{
	TCNT0 = 0;
	TCCR0 = _BV(CS01) | _BV(CS00);
}
/**/

void
Timer_Reset_And_Start_x1024()
{
	TCNT0 = 0;
	TCCR0 = _BV(CS02) | _BV(CS01) | _BV(CS00);
}
/**/

void
Timer_Stop()
{
	//TCNT0 = 0;
	TCCR0 = 0;
}
/**/

void
Timer_Change_Compare(uint8_t value)
{
	//For 11 059 200 Hz Clock Generator
	//x64 prescaller
	// 1.5T = 148 Value
	// 3.5T - 1.5T = 196 Value
	OCR0 = value;
}
/**/

void 
UART_TX_8b(uint8_t* txData, uint8_t lenght)
{
	uint8_t i;
	
	UCSR1B &= ~(_BV(RXCIE1));

	PORTD |= 1<<4;
	_delay_us(50);

	for (i = 0; i < lenght; i++)
	{
		usart_putchar(txData[i]);
	}
	while(bit_is_clear(UCSR1A, UDRE1))
	{
		
	}
	_delay_us(10);

	UCSR1B |= (_BV(RXCIE1));
	
	_delay_us(10);
	PORTD &= ~(1<<4);
	_delay_us(10);

}
/**/

void 
usart_putchar(uint8_t c)
{ 
    while(bit_is_clear(UCSR1A, UDRE1));
    UDR1 = c; 
	_delay_us(100);
}
