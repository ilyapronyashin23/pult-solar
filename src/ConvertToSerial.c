#include "ConvertToSerial.h"
#include "ModbusProtocolTable.h"
#include "DisplayFormatter.h"
#include "compat/ina90.h"

void ConvToSerial_U16( RamList_t* ram_list, uint8_t * buf, uint8_t* len);

void
ConvSerial_Write( RamList_t* ram_list, uint8_t * buf, uint8_t * len)
{
	
	switch (ram_list->p_now->Level)
	{
		case LEVEL0:
		{
			ConvToSerial_U16(ram_list, buf, len);
			break;
		}
		
		case LEVEL1:
		{
			
			break;
		}
		
		case LEVEL2:
		case LEVEL3:
		{
			/* Проверка на флаг EditFromAnotherElement. Загрублено */
			if (0)
			{
				
			}
			else
			{
				/* Загрублено. Switch по данным из Data.c */
				
				
				
				switch (ram_list->p_now->pData->Type)
				{
					case (DATA_TYPE_2):
					{
						if ((((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == TYPE_Date_1_t) |
							(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == TYPE_Time_1_t))
						{
							
							if ((ram_list->p_now->Msg.Tx.Page == MODBUS_PAGE_0) & (ram_list->p_now->Msg.Tx.Reg == MODBUS_REG_DATE1))
							{
								
								ConvToSerial_Date(ram_list, buf, len);
							}
							else if ((ram_list->p_now->Msg.Tx.Page == MODBUS_PAGE_0) & (ram_list->p_now->Msg.Tx.Reg == MODBUS_REG_TIME1))
							{
								
								ConvToSerial_Time(ram_list, buf, len);
								
							}
						}
						else if (((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == U16)
						{
							ConvToSerial_U16(ram_list, buf, len);
						}
						else if (((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == U16nP)
						{
							ConvToSerial_U16(ram_list, buf, len);
						}
						else if (((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == S16)
						{
							ConvToSerial_U16(ram_list, buf, len);
						}
						else if (((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == BOOL)
						{
							ConvToSerial_U16(ram_list, buf, len);
						}
						break;
					}
					
					default:
						break;
				}
			}
			break;
		}
		
		default:
			break;
	}
}

void
ConvToSerial_Time( RamList_t* ram_list, uint8_t * buf, uint8_t* len)
{
	uint16_t tmp1, tmp2;
	
	buf[1] = 0x10;
	buf[2] = MODBUS_PAGE_0;
	buf[3] = MODBUS_REG_TIME1;
	buf[4] = 0;
	buf[5] = 2;
	buf[6] = 4;
	
	
	buf[7] = (uint8_t)(ram_list->p_now->Msg.stDateTime.Minute & 0xff);
	buf[8] = (uint8_t)(ram_list->p_now->Msg.stDateTime.Second & 0xff);
	
	buf[9] = 0;
	buf[10] = (uint8_t)(ram_list->p_now->Msg.stDateTime.Hour & 0xff);
	
	*len = 13;
}

void
ConvToSerial_Date( RamList_t* ram_list, uint8_t * buf, uint8_t* len)
{
	uint16_t tmp1, tmp2;
	
	buf[1] = 0x10;
	buf[2] = MODBUS_PAGE_0;
	buf[3] = MODBUS_REG_DATE1;
	buf[4] = 0;
	buf[5] = 2;
	buf[6] = 4;
	
	buf[7] = (uint8_t)(ram_list->p_now->Msg.stDateTime.Month & 0xff);
	buf[8] = (uint8_t)(ram_list->p_now->Msg.stDateTime.Day & 0xff);
	
	buf[9] = 0;
	buf[10] = (uint8_t)(ram_list->p_now->Msg.stDateTime.Year & 0xff);
	
	*len = 13;
}

void
ConvToSerial_U16( RamList_t* ram_list, uint8_t * buf, uint8_t* len)
{
	uint16_t tmp1, tmp2;
	
	
	
	buf[1] = 0x06;
	buf[2] = ram_list->p_now->Msg.Tx.Page;
	buf[3] = ram_list->p_now->Msg.Tx.Reg;
	

	
	buf[4] = (uint8_t)((ram_list->p_now->Msg.st.ret.u16 & 0xff00) >> 8);
	buf[5] = (uint8_t)(ram_list->p_now->Msg.st.ret.u16 & 0x00ff);

	
	*len = 8;
}

void
//ConvSerial_Page0_Reg77(Msg.Value.ret, Msg.Bits);(void)
ConvSerial_Page0_Reg77(void)
{
	
}
