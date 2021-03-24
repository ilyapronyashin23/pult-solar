#include "DataConvert.h"
#include "Modbus.h"
#include "compat/ina90.h"

ConvertTable_t Table;
Control_t Control;
extern st_Master_t dev;
extern	uint32_t Succesful_Cnt;
uint16_t u16_tmp_0 = 0;

/*
	retval:
		uint16_t - возвращает Control.Focus_Lenght количество запрашиваемых регистров
	
	params:
		uint8_t* pin 	- контейнер. заполняет значения запроса мастера
		uint8_t len		- не исп.
		
	info:
		в зависимости от текущей страницы заполняет запрос мастера 
*/
uint16_t
FillMsg(uint8_t* pin, uint8_t len)
{
	//uint16_t tmp_StartPos 	= 0;
	//uint16_t tmp_Len 		= 0;
	
	

	if (Control.PageCnt >= Control.PageCnt_Max ) Control.PageCnt = 0;
	
	if ((Control.pPage + Control.PageCnt)->Page_Cnt == 
		(Control.pPage + Control.PageCnt)->Page_Cnt_Max)
	{
		Control.Focus_Lenght = (Control.pPage + Control.PageCnt)->Carriage_Num_Last;
		Control.Focus_StartPosition  = (Control.pPage + Control.PageCnt)->Page_Cnt * (Control.pPage + Control.PageCnt)->Carriage_Num;
		
		Control.Focus_Carriage = (Control.pPage + Control.PageCnt)->Page_Cnt;
		(Control.pPage + Control.PageCnt)->Page_Cnt = 0;
		Control.Focus_Page = Control.PageCnt;
		Control.PageCnt	+= 1;
	}
	else if ((Control.pPage + Control.PageCnt)->Page_Cnt < 
		(Control.pPage + Control.PageCnt)->Page_Cnt_Max)
	{
		Control.Focus_Lenght = (Control.pPage + Control.PageCnt)->Carriage_Num;
		Control.Focus_StartPosition = (Control.pPage + Control.PageCnt)->Page_Cnt * (Control.pPage + Control.PageCnt)->Carriage_Num;
		
		Control.Focus_Carriage = (Control.pPage + Control.PageCnt)->Page_Cnt;
		(Control.pPage + Control.PageCnt)->Page_Cnt += 1;
		Control.Focus_Page = Control.PageCnt;
		Control.PageCnt	+= 0;
	}
	
	*(pin + 2) = (Control.Focus_Page & 0x00ff);
	//*(pin + 2) = 0;
	*(pin + 3) = (Control.Focus_StartPosition & 0x00ff);
	*(pin + 4) = (Control.Focus_Lenght & 0xff00) >> 8;
	*(pin + 5) = (Control.Focus_Lenght & 0x00ff);
	
	return Control.Focus_Lenght;
}

void
Convert_Init(void)
{
	Control.PageCnt = 0;
	Control.PageCnt_Max = 1;
	Control.Focus_Lenght = 0;
	Control.Focus_StartPosition = 0;
	Control.Focus_Page = 0;
	Control.Focus_Carriage = 0;
	Control.pPage = malloc(1 * sizeof(ReqPage_t));
	//(Control.pPage+1)	= malloc(1 * sizeof(Page_t));
	

	Control.pPage->Page_Num 			= 1;		//PAGE 0: 20 BYTES SUMMARY
	Control.pPage->Page_Cnt 			= 0;
	Control.pPage->Page_Cnt_Max 		= 0;
	Control.pPage->Carriage_Num 		= 0;
	Control.pPage->Carriage_Num_Last	= 50;
	
	/*
	(Control.pPage+1)->Page_Num 			= 2;	//PAGE 1: 10 BYTES SUMMARY
	(Control.pPage+1)->Page_Cnt 			= 0;
	(Control.pPage+1)->Page_Cnt_Max 		= 0;
	(Control.pPage+1)->Carriage_Num 		= 0;
	(Control.pPage+1)->Carriage_Num_Last	= 10;
	*/
	
	/*
	(Control.pPage+2)->Page_Num 			= 3;	//PAGE 2: 24 BYTES SUMMARY
	(Control.pPage+2)->Page_Cnt 			= 0;
	(Control.pPage+2)->Page_Cnt_Max 		= 0;
	(Control.pPage+2)->Carriage_Num 		= 0;
	(Control.pPage+2)->Carriage_Num_Last	= 24;
	
	(Control.pPage+3)->Page_Num 			= 4;	//PAGE 3: 160 BYTES SUMMARY
	(Control.pPage+3)->Page_Cnt 			= 0;
	(Control.pPage+3)->Page_Cnt_Max 		= 3;
	(Control.pPage+3)->Carriage_Num 		= 40;
	(Control.pPage+3)->Carriage_Num_Last	= 40;
	*/
	
	Init(); //Modbus initialisation
}

void
User_Callback(bool val)
{
	if (val)
	{
		Convert(dev.Received_Data.p_Bytes);
		Succesful_Cnt++;
	}
	else
	{
	}
}

void
Convert(uint8_t*	pin)
{
	switch (Control.Focus_Page)
	{
		case 0:
			Convert_Page_0(pin, Control.Focus_Carriage);
			break;
		
		case 1:
			Convert_Page_1(pin, Control.Focus_Carriage);
			break;
		
		default:
			break;
	}
}



void
Convert_Page_0(uint8_t* pin, uint8_t car)
{
	uint16_t	j = 0;
	uint16_t	i = 3;
	uint16_t	u16_Temp = 0;
	uint16_t	u16_Temp2 = 0;
	
	
	for (j = (0+(car*MAX_ALLOWED_DATABYTES_NUM_MASTER_X04)); j < (MAX_ALLOWED_DATABYTES_NUM_MASTER_X04+(car*MAX_ALLOWED_DATABYTES_NUM_MASTER_X04)); j++)
	{
		u16_tmp_0 = (uint16_t)((*(pin + i++)) << 8);
		u16_tmp_0 |= (uint16_t)(*(pin + i++));
			
		switch (j)
		{			
			case (MODBUS_REG_TIME1):
				Table.DateTime.Second = BCD_to_DEC(u16_tmp_0, 0);
				Table.DateTime.Minute = BCD_to_DEC(u16_tmp_0, 1);
				break;
				
			case (MODBUS_REG_TIME2):
				Table.DateTime.Hour = BCD_to_DEC(u16_tmp_0, 0);
				
				break;
				
			case (MODBUS_REG_DATE1):
				Table.DateTime.Day = BCD_to_DEC(u16_tmp_0, 0);
				Table.DateTime.Month = BCD_to_DEC(u16_tmp_0, 1);
				
				break;
			
			case (MODBUS_REG_DATE2):
				Table.DateTime.Year = BCD_to_DEC(u16_tmp_0, 0);
				break;
				
			case (MODBUS_REG_0):
				Table.Page0.Reg0 = u16_tmp_0;
				break;
				
			case (MODBUS_REG_1):
				Table.Page0.Reg1 = u16_tmp_0;
				break;
				
			case (MODBUS_REG_2):
				Table.Page0.Reg2 = u16_tmp_0;
				break;
				
			case (MODBUS_REG_INVERTER):
				Table.Page0.Reg3 = u16_tmp_0;
				break;
			case (MODBUS_REG_MPPT1):
				Table.Page0.Reg4 = u16_tmp_0;
				break;
			case (MODBUS_REG_MPPT2):
				Table.Page0.Reg5 = u16_tmp_0;
				break;
				
			case (MODBUS_STARTSTOP):
				if (u16_tmp_0 <= NO485)
				{
					Table.Page0.Mode = u16_tmp_0;
				}
				else
					Table.Page0.Mode = CM_UNK;
				break;
			
			case (MODBUS_ADC_TSTB):
				Table.Page0.RegTSTB = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_ADC_TRAD):
				Table.Page0.RegTRAD = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_ADC_220VN):
				Table.Page0.Reg220VN = (int16_t)u16_tmp_0;
				//Table.Page0.Reg220VN = 500;
				break;
				
			case (MODBUS_ADC_ISTBN):
				Table.Page0.RegISTBN = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_ADC_TTR):
				Table.Page0.RegTTR = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_ADC_STBN):
				Table.Page0.RegSTBN = (int16_t)u16_tmp_0;
				//Table.Page0.RegSTBN = 450;
				break;
				
			case (MODBUS_ADC_IINVN):
				Table.Page0.RegIINVN = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_ADC_I220N):
				Table.Page0.RegI220N = (int16_t)u16_tmp_0;
				//Table.Page0.RegI220N = 20;
				break;
				
			case (MODBUS_ADC_IO2N):
				Table.Page0.RegIO2N = (int16_t)u16_tmp_0;
				//Table.Page0.RegIO2N = 150;
				break;
				
			case (MODBUS_ADC_SB2N):
				Table.Page0.RegSB2N = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_ADC_SB1N):
				Table.Page0.RegSB1N = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_ADC_IO1N):
				Table.Page0.RegIO1N = (int16_t)u16_tmp_0;
				//Table.Page0.RegIO1N = 200;
				break;
			
			case (MODBUS_SOLBAT_CH1_U_MPP):
				
				Table.Page0.Reg_SOLBAT_CH1_U_MPP = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH1_U_XX):
				Table.Page0.Reg_SOLBAT_CH1_U_XX = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH1_NUM_SERIAL):
				Table.Page0.Reg_SOLBAT_CH1_NUM_SERIAL = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH1_NUM_PARAL):
				Table.Page0.Reg_SOLBAT_CH1_NUM_PARAL = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH1_I_KZ):
				Table.Page0.Reg_SOLBAT_CH1_I_KZ = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH1_I_MPP):
				Table.Page0.Reg_SOLBAT_CH1_I_MPP = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH1_MODE):
				Table.Page0.Reg_SOLBAT_CH1_MODE = (int16_t)u16_tmp_0;
				break;
			
			case (MODBUS_REG_DEBUG_TEMP0):
				Table.Page0.RegTemp0 = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_REG_DEBUG_TEMP1):
				Table.Page0.RegTemp1 = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_REG_DEBUG_TEMP2):
				Table.Page0.RegTemp2 = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_INVERTER_UOUT_SET):
				Table.Page0.Reg_INVERTER_UOUT_SET = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_REG_DEBUG_TEMP3):
				Table.Page0.RegTemp3 = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_RELAY_P2):
				Table.Page0.Reg_RELAY_P2 = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_RELAY_P3):
				Table.Page0.Reg_RELAY_P3 = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH2_U_MPP):
				Table.Page0.Reg_SOLBAT_CH2_U_MPP = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH2_U_XX):
				Table.Page0.Reg_SOLBAT_CH2_U_XX = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH2_NUM_SERIAL):
				Table.Page0.Reg_SOLBAT_CH2_NUM_SERIAL = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH2_NUM_PARAL):
				Table.Page0.Reg_SOLBAT_CH2_NUM_PARAL = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH2_I_KZ):
				Table.Page0.Reg_SOLBAT_CH2_I_KZ = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH2_I_MPP):
				Table.Page0.Reg_SOLBAT_CH2_I_MPP = (int16_t)u16_tmp_0;
				break;
				
			case (MODBUS_SOLBAT_CH2_MODE):
				Table.Page0.Reg_SOLBAT_CH2_MODE = (int16_t)u16_tmp_0;
				break;
				
			default:
				break;
		}
		
		u16_Temp = Table.Page0.RegSTBN / 10;
		u16_Temp *= Table.Page0.RegIO1N;
		//u16_Temp /= 1000;
		
		u16_Temp2 = Table.Page0.RegSTBN / 10;
		u16_Temp2 *= Table.Page0.RegIO2N;
		//u16_Temp2 /= 1000;
		
		u16_Temp2 += u16_Temp;
		u16_Temp2 /= 10;
		
		Table.Page0.Reg_PowMPPT_Out = u16_Temp2;
		//Table.Page0.Reg_PowMPPT_Out = 10;
		
		u16_Temp = Table.Page0.Reg220VN / 10;
		u16_Temp *= Table.Page0.RegI220N;
		//u16_Temp /= 10;
		
		//Table.Page0.Reg_PowInverter_Out = 18;
		Table.Page0.Reg_PowInverter_Out = (uint16_t)u16_Temp;
	}
}



void
Convert_Page_1(uint8_t* pin, uint8_t car)
{
	uint16_t	j = 0;
	uint16_t	k = 0;
	uint16_t	i = 3;
	
	for (j = (0+(car*12)); j < (12+(car*12)); j++)
	{
		for (k = 0; k < 3; k++)
		{
			u16_tmp_0 = (uint16_t)((*(pin + i++)) << 8);
			u16_tmp_0 |= (uint16_t)(*(pin + i++));
			
			
		}
	}
}


/*
	BCD_to_DEC
	params:
		uint16_t	in - 	input BCD,
		uint8_t		tetra - mode of converting^
			0 - 1 tetrade
			1 - 2 tetrade
			2 - 1..4 tetrades
			3 - 2 tetrade without 4 bit (60 sec)
	return value:
		uint16_t
*/
uint16_t
BCD_to_DEC(uint16_t in, uint8_t tetra)
{
	uint8_t 	u8_Tmp = 0;
	uint16_t 	u16_Tmp = 0;
	uint16_t	u16_Return = 0;
	
	switch (tetra)
	{
		case (0):	//Day
			u8_Tmp = in & 0x000f;
			u16_Return = u8_Tmp;
			
			u8_Tmp = in & 0x00f0;
			u8_Tmp = u8_Tmp >> 4;
			u8_Tmp *= 10;
			u16_Return += u8_Tmp;
			
			break;
		
		case (1):	//Month
			u16_Tmp = in & 0x0f00;
			u8_Tmp = (uint8_t)(u16_Tmp >> 8);
			u16_Return = u8_Tmp;
			
			u16_Tmp = in & 0xf000;
			u8_Tmp = (uint8_t)(u16_Tmp >> 12);
			u8_Tmp *= 10;
			u16_Return += u8_Tmp;
			break;
			
		case (2):	//Year
			u8_Tmp = in & 0x000f;
			u16_Return = u8_Tmp;
			
			u8_Tmp = in & 0x00f0;
			u8_Tmp = u8_Tmp >> 4;
			//u8_Tmp *= 10;
			u16_Return +=(10 * u8_Tmp);
		
			u16_Tmp = in & 0x0f00;
			u8_Tmp = (uint8_t)(u16_Tmp >> 8);
			u16_Return += (100 * u8_Tmp);
			
			u16_Tmp = in & 0xf000;
			u8_Tmp = (uint8_t)(u16_Tmp >> 12);
			//u8_Tmp *= 10;
			u16_Return += (1000 * u8_Tmp);
			break;
			
		case (3):	//Without 
			u16_Tmp = in & 0x0f00;
			u8_Tmp = (uint8_t)(u16_Tmp >> 8);
			u16_Return = u8_Tmp;
			
			u16_Tmp = in & 0x7000;
			u8_Tmp = (uint8_t)(u16_Tmp >> 12);
			u8_Tmp *= 10;
			u16_Return += u8_Tmp;
			break;
	}
	
	return u16_Return;
}

uint16_t
DEC_to_BCD(uint16_t in, uint8_t param)
{
	uint8_t 	u8_Tmp = 0;
	uint16_t 	u16_Tmp = 0;
	uint16_t	u16_Return = 0;
	
	switch (param)
	{
		case (0):
		{
			u8_Tmp = in / 10;
			u8_Tmp = u8_Tmp << 4;
			u16_Return = u8_Tmp & 0x00f0;
		
			u8_Tmp = in - ((in / 10)*10);
			u16_Return += u8_Tmp & 0x000f;
			
			break;
		}
		
		case (1):
		{
			u16_Tmp = in / 10;
			u16_Tmp = u16_Tmp << 12;
			u16_Return = u16_Tmp & 0xf000;
		
			u16_Tmp = in - ((in / 10)*10);
			u16_Tmp = u16_Tmp << 8;
			u16_Return += u16_Tmp & 0x0f00;
			break;
		}
	}
	
	return u16_Return;
}
/**/
