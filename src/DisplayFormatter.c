#include "DisplayFormatter.h"
#include "compat/ina90.h"

#include "Menu.h"
#include "string.h"
#include "weh1602_driver.h"
#include "stdio.h"
#include "Types.h"
#include "DataConvert.h"
#include "Modbus.h"

char PGM_Buffer0[17];
char PGM_Buffer1[17];

//extern RamDataContainer_t RamData;
extern PGM_P spgm_NULL[];
extern PGM_P spgm_UNK[];
extern PGM_P spgm_UnitName_t[];
extern PGM_P spgm_ICHARGE_MODE[];
extern ConvertTable_t Table;
extern st_NoAnswer_t NoAnswer;
extern	PGM_P spgm_bool[];
extern RamList_t* p_ram_list;
extern PGM_P spgm_MPP[];
extern PGM_P spgm_BAT[];

void PARSE_TYPE_BAT(uint16_t code, char* pbuf);

/*
	???
*/
void
Refresh( Element_t* pin )
{
	void**	ppv = NULL;
	void*	pv = NULL;
	
	ppv = (void**)pgm_read_word(&(pin->ppv_RAM_Data));
	pv = *ppv;
	
	if (*ppv == NULL)
	{
		//PORTD ^= 1<<1;
		LList_MemAlloc(p_ram_list, pin, ppv);
	}
}




/*
	???
*/
void
Fill_PGM_to_RAM_Type_1
( 
	RamList_t* ram_list,
	Element_t* pin, 
	void** ppv 
)
{
	DataType_1_t Data_Type_1_Tmp;
	uint16_t u16_Tmp = (uint16_t)pgm_read_word((PGM_P)(&(pin->pv_PGM_Data)));
	DataType_1_t* pt = (DataType_1_t*)*ppv;
	
	strcpy_P(Data_Type_1_Tmp.Label_Up, 
		(PGM_P)pgm_read_word((PGM_P)u16_Tmp));
	u16_Tmp += sizeof(char*);
	strcpy_P(Data_Type_1_Tmp.Label_Low, 
		(PGM_P)pgm_read_word((PGM_P)u16_Tmp));
	//u16_Tmp += sizeof(char*);
	//Data_Type_1_Tmp.et_Flags = (uint16_t)pgm_read_word((PGM_P)(u16_Tmp));
	//u16_Tmp += sizeof(uint16_t);
	
	

	strcpy(pt->Label_Up, Data_Type_1_Tmp.Label_Up);
	strcpy(pt->Label_Low, Data_Type_1_Tmp.Label_Low);
	//pt->et_Flags = Data_Type_1_Tmp.et_Flags;
	
	
	ram_list->p_now->Data1.Type = DATA_TYPE_1;
	ram_list->p_now->Data1.pv = (void*)pt;
	ram_list->p_now->pData = &(ram_list->p_now->Data1);
	
	//ram_list->p_now->Data1.Type = DATA_TYPE_1;
	//ram_list->p_now->Data1.pv = (void*)pt;
	//ram_list->p_now->pData = &(ram_list->p_now->Data1);
	
	
}



/*
	???
*/
void
Fill_PGM_to_RAM_Type_2
(
	RamList_t* ram_list,
	Element_t* pin, 
	void** ppv
)
{
	DataType_2_t DataType_2_Tmp;
	
	uint16_t u16_Tmp = (uint16_t)pgm_read_word((PGM_P)(&(pin->pv_PGM_Data)));
	DataType_2_t* pt = (DataType_2_t*)*ppv;

	
	strcpy_P(DataType_2_Tmp.Label, (PGM_P)pgm_read_word((PGM_P)u16_Tmp));
	u16_Tmp += sizeof(char*);
	strcpy_P(DataType_2_Tmp.ParamLabel, (PGM_P)pgm_read_word((PGM_P)u16_Tmp));
	u16_Tmp += sizeof(char*);
	DataType_2_Tmp.Value.pvData = (void*)pgm_read_word((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(void*);
	DataType_2_Tmp.Value.Type = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	DataType_2_Tmp.Value.Units = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	DataType_2_Tmp.Tx.Page = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	DataType_2_Tmp.Tx.Reg = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	DataType_2_Tmp.Tx.Bit = (uint16_t)pgm_read_word((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint16_t);
	DataType_2_Tmp.Opt = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	DataType_2_Tmp.Flag = (uint16_t)pgm_read_word((PGM_P)(u16_Tmp));
	//u16_Tmp += sizeof(uint16_t);
	
	//if (DataType_2_Tmp.Value.Units > 10)
	//if (sizeof(UnitName_t) == 2)
		
	//v_GetLimits((Data_Type_3_Tmp.Transmit.Register, &Msg.Value.Limits);
	
	v_GetLimits(DataType_2_Tmp.Tx.Reg, &(ram_list->p_now->Msg.st.Limit));
	

	strcpy(pt->Label, DataType_2_Tmp.Label);
	strcpy(pt->ParamLabel, DataType_2_Tmp.ParamLabel);
	pt->Value.pvData = DataType_2_Tmp.Value.pvData;
	pt->Value.Type = DataType_2_Tmp.Value.Type;
	pt->Value.Units = DataType_2_Tmp.Value.Units;
	pt->Tx.Page = DataType_2_Tmp.Tx.Page;
	pt->Tx.Reg = DataType_2_Tmp.Tx.Reg;
	pt->Tx.Bit = DataType_2_Tmp.Tx.Bit;
	pt->Opt = DataType_2_Tmp.Opt;
	pt->Flag = DataType_2_Tmp.Flag;
	
	/*
	pt->Transmit.Page			= DataType_2_Tmp.Transmit.Page;
	pt->Transmit.Register		= DataType_2_Tmp.Transmit.Register;
	pt->Options				= DataType_2_Tmp.Options;
	*/
	
	ram_list->p_now->Data1.Type = DATA_TYPE_2;
	ram_list->p_now->Data1.pv = (void*)pt;
	ram_list->p_now->pData = &(ram_list->p_now->Data1);
	//RAM_Type 			= RAM_MainRunner;
	
	
	
	/*
	Msg.Value.Value_Type = pt->Value.Value_Type;
	Msg.Value.ret.f32 = *((float32_t*)pt->Value.pv);
	Msg.Transmit.Page = pt->Transmit.Page;
	Msg.Transmit.Register = pt->Transmit.Register;
	*/
}

/*
	???
*/
void
Fill_PGM_to_RAM_Type_Main_3_2
(
	RamList_t* ram_list,
	Element_t* pin, 
	void** ppv
)
{
	DataType_Main_3_2_t Tmp;
	
	uint16_t u16_Tmp = (uint16_t)pgm_read_word((PGM_P)(&(pin->pv_PGM_Data)));
	DataType_Main_3_2_t* pt = (DataType_Main_3_2_t*)*ppv;

	
	strcpy_P(Tmp.ParamLabel_0, (PGM_P)pgm_read_word((PGM_P)u16_Tmp));
	u16_Tmp += sizeof(char*);
	strcpy_P(Tmp.ParamLabel_1, (PGM_P)pgm_read_word((PGM_P)u16_Tmp));
	u16_Tmp += sizeof(char*);
	
	
	Tmp.Value_0.pvData = (void*)pgm_read_word((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(void*);
	Tmp.Value_0.Type = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Value_0.Units = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	
	Tmp.Value_1.pvData = (void*)pgm_read_word((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(void*);
	Tmp.Value_1.Type = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Value_1.Units = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	
	Tmp.Tx.Page = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Tx.Reg = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Tx.Bit = (uint16_t)pgm_read_word((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint16_t);
	Tmp.Opt = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Flag = (uint16_t)pgm_read_word((PGM_P)(u16_Tmp));
	
	
	/*
	Tmp.Tx.Page = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Tx.Reg = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Tx.Bit = (uint16_t)pgm_read_word((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint16_t);
	Tmp.Opt = (uint8_t)pgm_read_byte((PGM_P)(u16_Tmp));
	u16_Tmp += sizeof(uint8_t);
	Tmp.Flag = (uint16_t)pgm_read_word((PGM_P)(u16_Tmp));
	//u16_Tmp += sizeof(uint16_t);
	*/
	
	//v_GetLimits(Tmp.Tx.Reg, &(RamData.Msg.st.Limit));
	

	strcpy(pt->ParamLabel_0, Tmp.ParamLabel_0);
	strcpy(pt->ParamLabel_1, Tmp.ParamLabel_1);
	pt->Value_0.pvData = Tmp.Value_0.pvData;
	pt->Value_0.Type = Tmp.Value_0.Type;
	pt->Value_0.Units = Tmp.Value_0.Units;
	pt->Value_1.pvData = Tmp.Value_1.pvData;
	pt->Value_1.Type = Tmp.Value_1.Type;
	pt->Value_1.Units = Tmp.Value_1.Units;
	
	pt->Tx.Page = Tmp.Tx.Page;
	pt->Tx.Reg = Tmp.Tx.Reg;
	pt->Tx.Bit = Tmp.Tx.Bit;
	pt->Opt = Tmp.Opt;
	pt->Flag = Tmp.Flag;
	
	
	
	/*
	pt->Tx.Page = Tmp.Tx.Page;
	pt->Tx.Reg = Tmp.Tx.Reg;
	pt->Tx.Bit = Tmp.Tx.Bit;
	pt->Opt = Tmp.Opt;
	pt->Flag = Tmp.Flag;
	*/
	
	/*
	pt->Transmit.Page			= DataType_2_Tmp.Transmit.Page;
	pt->Transmit.Register		= DataType_2_Tmp.Transmit.Register;
	pt->Options				= DataType_2_Tmp.Options;
	*/
	
	
	
	ram_list->p_now->Data1.Type = DATA_TYPE_MAIN_3_2;
	ram_list->p_now->Data1.pv = (void*)pt;
	ram_list->p_now->pData = &(ram_list->p_now->Data1);
	
	
	
	
	//RAM_Type 			= RAM_MainRunner;
	
	
	
	/*
	Msg.Value.Value_Type = pt->Value.Value_Type;
	Msg.Value.ret.f32 = *((float32_t*)pt->Value.pv);
	Msg.Transmit.Page = pt->Transmit.Page;
	Msg.Transmit.Register = pt->Transmit.Register;
	*/
}



/*
	???
*/
void
Update_Screen(RamList_t* ram_list)
{
	/*
	RamDataContainer_t* cont;
	
	switch (ram_list->type)
	{
		case (RAM_MAIN):
		cont = ram_list->pram_main;
		break;
		
		case (RAM_PARVIEW):
		cont = ram_list->pram_parview;
		break;
	}
	*/
	
	
	
	if (ram_list->p_now->Level == LEVEL0)
	{
		Main_Printf(ram_list->p_now);
		
	}
	else
	{
		
		switch (ram_list->p_now->pData->Type)
		{
			case (DATA_TYPE_1):
			{
				LCDSend_1(ram_list->p_now);
				break;
			}
			
			case (DATA_TYPE_2):
			{
				LCDSend_2(ram_list->p_now);
				break;
			}
			
			default:
			{
				break;
			}
		}
	}
}

void
Main_Printf( RamDataContainer_t* ramdata )
{
	static CurrentMode_t Prev_Mode = STOP;
	
	if (NoAnswer.u8_Count > 50) {
		if (!NoAnswer.b_Res) {
			NoAnswer.b_Res = true;
			p_ram_list->p_now = p_ram_list->p_ram_main;
			Menu_Step(NO485);
		}
		ramdata->Blank_Menu = true;
	} else {
		if (ramdata->Blank_Menu) {
			ramdata->Blank_Menu = false;
			p_ram_list->p_now = p_ram_list->p_ram_parview;
			//Menu_Step(MAINSCREEN);
		} 
		/*else {
			if (Table.Page0.Mode != Prev_Mode) {
				Menu_Step(MAINSCREEN);
				Prev_Mode = Table.Page0.Mode;
			}
		}*/
	}
	
	if (ramdata->pData->Type == DATA_TYPE_1)
	{
		
		LCDSend_1(ramdata);
	}
	else if (ramdata->pData->Type == DATA_TYPE_MAIN_3_2)
	{
		
		LCDSend_MainScreen(ramdata);
	}
	else{
	}
}


/*
	Вывод на экран элементов типа DATA_TYPE_MAIN_3_2.
	Сейчас реалиовано отображение только нижней строки
*/
void
v_LCDStatus( RamDataContainer_t* ramdata )
{
	uint8_t	i;
	char lbuf[(MAIN_STRING_LENGHT+1)];
	static uint16_t u16_Count = 0;
	
	//GetCenteredString(((DataType_1_t*)ramdata->pData->pv)->Label_Up, lbuf);
	
	v_LCDGotoXY_v1(0, 0);
	v_LCDSend_v1(LCD_BYTE, SYM_TIMER);
	
	v_LCDGotoXY_v1(1, 0);
	v_LCDSend_v1(LCD_ASCII, '0');
	
	v_LCDSend_v1(LCD_CMD, (2 | 0x80));
	v_LCDSend_v1(LCD_ASCII, ' ');
	
	v_LCDSend_v1(LCD_CMD, (3 | 0x80));
	v_LCDSend_v1(LCD_ASCII, '!');
	
	v_LCDSend_v1(LCD_CMD, (4 | 0x80));
	v_LCDSend_v1(LCD_ASCII, '0');
	
	v_LCDSend_v1(LCD_CMD, (5 | 0x80));
	v_LCDSend_v1(LCD_ASCII, ' ');
	
	// SYMBOL 6
	
	v_LCDSend_v1(LCD_CMD, (6 | 0x80));
	if (((Table.Page0.Reg4 != 0) | (Table.Page0.Reg5 != 0)) & (Table.Page0.Mode == RUN)){
		
		v_LCDSend_v1(LCD_BYTE, SYM_SOLAR_BAT);
	}
	else{
		v_LCDSend_v1(LCD_ASCII, ' ');
	}
	
	
	// SYMBOL 7
	// ВРЕМЕННО УСЛОВИМСЯ ЧТО МАКС ОТДАЧА МОЩНОСТИ С ОДНОГО MPPT ОГРАНИЧЕНА 1 кВТ, тогда за ПРЕДЕЛ ШКАЛЫ БЕРЕТСЯ 2 кВТ
	
	v_LCDSend_v1(LCD_CMD, (7 | 0x80));
	
	if ((Table.Page0.Reg_PowMPPT_Out >= 0) & (Table.Page0.Reg_PowMPPT_Out < 20)){
		v_LCDSend_v1(LCD_ASCII, ' ');
	}
	else if ((Table.Page0.Reg_PowMPPT_Out >= 20) & (Table.Page0.Reg_PowMPPT_Out < 100)){
		if ((u16_Count >= 0) & (u16_Count < 90)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 90) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else if ((Table.Page0.Reg_PowMPPT_Out >= 100) & (Table.Page0.Reg_PowMPPT_Out < 500)){
		if ((u16_Count >= 0) & (u16_Count < 50)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 50) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else if ((Table.Page0.Reg_PowMPPT_Out >= 500) & (Table.Page0.Reg_PowMPPT_Out < 2000)){
		if ((u16_Count >= 0) & (u16_Count < 5)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 5) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else{
		v_LCDSend_v1(LCD_ASCII, '?');
	}
	
	
	// SYMBOL 8
	
	v_LCDSend_v1(LCD_CMD, (8 | 0x80));
	if (Table.Page0.RegSTBN >= 490){
		v_LCDSend_v1(LCD_BYTE, SYM_LEAD_BAT_3_3);
	}
	else if ( (Table.Page0.RegSTBN >= 448) & (Table.Page0.RegSTBN < 490) ){
		v_LCDSend_v1(LCD_BYTE, SYM_LEAD_BAT_2_3);
	}
	else if ( (Table.Page0.RegSTBN >= 400) & (Table.Page0.RegSTBN < 448) ){
		v_LCDSend_v1(LCD_BYTE, SYM_LEAD_BAT_1_3);
	}
	else{
		if ((u16_Count >= 0) & (u16_Count < 90)){
			
			v_LCDSend_v1(LCD_BYTE, SYM_LEAD_BAT_0_3);
		}
				
		if ((u16_Count >= 90) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
	}
	
	
	// SYMBOL 9
	
	v_LCDSend_v1(LCD_CMD, (9 | 0x80));
	
	if ((Table.Page0.Reg_PowInverter_Out >= 0) & (Table.Page0.Reg_PowInverter_Out < 20)){
		v_LCDSend_v1(LCD_ASCII, ' ');
	}
	else if ((Table.Page0.Reg_PowInverter_Out >= 20) & (Table.Page0.Reg_PowInverter_Out < 100)){
		if ((u16_Count >= 0) & (u16_Count < 90)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 90) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else if ((Table.Page0.Reg_PowInverter_Out >= 100) & (Table.Page0.Reg_PowInverter_Out < 500)){
		if ((u16_Count >= 0) & (u16_Count < 50)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 50) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else if ((Table.Page0.Reg_PowInverter_Out >= 500) & (Table.Page0.Reg_PowInverter_Out < 2000)){
		if ((u16_Count >= 0) & (u16_Count < 5)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 5) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else{
		v_LCDSend_v1(LCD_ASCII, '?');
	}
	
	
	
	
	/*
	if ((Table.Page0.Reg220VN >= 0) & (Table.Page0.Reg220VN < 10)){
		v_LCDSend_v1(LCD_ASCII, ' ');
	}
	else if ((Table.Page0.Reg220VN >= 10) & (Table.Page0.Reg220VN < 50)){
		if ((u16_Count >= 0) & (u16_Count < 75)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 75) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else if ((Table.Page0.Reg220VN >= 50) & (Table.Page0.Reg220VN < 230)){
		if ((u16_Count >= 0) & (u16_Count < 20)){
			v_LCDSend_v1(LCD_ASCII, ' ');
		}
				
		if ((u16_Count >= 20) & (u16_Count < 100)){
			v_LCDSend_v1(LCD_BYTE, SYM_ARROW);
		}
	}
	else{
		v_LCDSend_v1(LCD_ASCII, '?');
	}
	*/
	
	// SYMBOL 10
	
	v_LCDSend_v1(LCD_CMD, (10 | 0x80));
	if ((Table.Page0.Reg3 != 0) & (Table.Page0.Mode == RUN)){
		v_LCDSend_v1(LCD_BYTE, SYM_XP);
	}
	else{
		v_LCDSend_v1(LCD_ASCII, ' ');
	}
	
	
	// SYMBOL 11
	
	v_LCDSend_v1(LCD_CMD, (11 | 0x80));
	v_LCDSend_v1(LCD_ASCII, ' ');
	
	v_LCDSend_v1(LCD_CMD, (12 | 0x80));
	v_LCDSend_v1(LCD_ASCII, '2');
	
	v_LCDSend_v1(LCD_CMD, (13 | 0x80));
	v_LCDSend_v1(LCD_ASCII, '/');
	
	v_LCDSend_v1(LCD_CMD, (14 | 0x80));
	v_LCDSend_v1(LCD_ASCII, '3');
	
	v_LCDSend_v1(LCD_CMD, (15 | 0x80));
	v_LCDSend_v1(LCD_ASCII, ' ');
	
	//Update_ccram_symbols();
	
	if (u16_Count >= 100)
	{
		u16_Count = 0;
	}
	else
		u16_Count++;
}


/*
	Вывод на экран элементов типа DATA_TYPE_MAIN_3_2.
	Сейчас реалиовано отображение только нижней строки
*/
void
LCDSend_MainScreen( RamDataContainer_t* ramdata )
{
	uint8_t	i;
	char lbuf[(MAIN_STRING_LENGHT+1)];
	uint8_t u8_Tmp_0 = 0;
	uint8_t u8_Tmp_1 = 0;
	uint8_t u8_Tmp_2 = 0;
	uint8_t u8_Tmp_3 = 0;
	bool b_NoParamLabel = false;
	
	
	if (ramdata->pData->Type != DATA_TYPE_MAIN_3_2)
		return;
	
	// 1. Статус
	v_LCDStatus(ramdata);
	
	for (i = 0; i < MAIN_STRING_LENGHT; i++)
		lbuf[i] = ' ';
	lbuf[MAIN_STRING_LENGHT] = 0;
	
	// 1. ДЛИНА НУЛЬ
	u8_Tmp_0 = MAIN_STRING_LENGHT;
	
	strcpy(lbuf, ((DataType_Main_3_2_t*)ramdata->pData->pv)->ParamLabel_0);
	if (strlen(lbuf) == 0)
		b_NoParamLabel = true;
	lbuf[strlen(lbuf)] = ' ';
	
	Parse_UnitName(((DataType_Main_3_2_t*)ramdata->pData->pv)->Value_0.Units, PGM_Buffer0);
	u8_Tmp_1 = strlen(PGM_Buffer0);
	
	// 4. вывод значения
	VST(ramdata, PGM_Buffer1, 0);
	
	u8_Tmp_2 = strlen(PGM_Buffer1);
	u8_Tmp_3 = u8_Tmp_0 - u8_Tmp_2 - u8_Tmp_1;
	
	//u8_Tmp_3 = GetCenteredValue(u8_Tmp_3);
		
	//GetCenteredString(PGM_Buffer0, lbuf);
	if (b_NoParamLabel)
	{
		u8_Tmp_3 = GetCenteredValue(u8_Tmp_3);
	}
	
	strcpy(lbuf + u8_Tmp_3, PGM_Buffer1);
	
	strcpy(lbuf + u8_Tmp_3 + u8_Tmp_2, PGM_Buffer0);
	lbuf[u8_Tmp_3+u8_Tmp_2+u8_Tmp_1] = ' ';
	lbuf[16] = 0;
	
	v_LCDGotoXY_v1(0, 1);
	for (i = 0; i < 16; i++)
		v_LCDSend_v1(LCD_ASCII, (uint8_t)*(lbuf + i));
	
	
}



/*
	???
*/
void
LCDSend_1( RamDataContainer_t* ramdata )
{
	uint8_t	i;
	char lbuf[(LEVEL1_STRING_LENGHT+1)];
	
	if (ramdata->pData->Type != DATA_TYPE_1)
		return;
	
	for (i = 0; i < LEVEL1_STRING_LENGHT; i++)
		lbuf[i] = ' ';
	lbuf[LEVEL1_STRING_LENGHT] = 0;
	
	GetCenteredString(((DataType_1_t*)ramdata->pData->pv)->Label_Up, lbuf);
	
	v_LCDGotoXY_v1(0, 0);
	for (i = 0; i < LEVEL1_STRING_LENGHT; i++)
		v_LCDSend_v1(LCD_ASCII, (uint8_t)*(lbuf + i));
	for (i = 0; i < LEVEL1_STRING_LENGHT; i++)
		lbuf[i] = ' ';
	lbuf[LEVEL1_STRING_LENGHT] = 0;
	
	GetCenteredString(((DataType_1_t*)ramdata->pData->pv)->Label_Low, lbuf);
	
	v_LCDGotoXY_v1(0, 1);
	for (i = 0; i < LEVEL1_STRING_LENGHT; i++)
		v_LCDSend_v1(LCD_ASCII, (uint8_t)*(lbuf + i));
}



/*
	???
*/
void
LCDSend_2( RamDataContainer_t* ramdata )
{
	uint8_t	i;
	char lbuf[17];
	uint8_t u8_Tmp_0 = 0;
	uint8_t u8_Tmp_1 = 0;
	uint8_t u8_Tmp_2 = 0;
	uint8_t u8_Tmp_3 = 0;
	bool b_NoParamLabel = false;
	static uint8_t u8_cnt = 30;
	
	if (ramdata->pData->Type != DATA_TYPE_2)
		return;
	
	for (i = 0; i < 16; i++)
		lbuf[i] = ' ';
	lbuf[16] = 0;
	
	GetCenteredString(((DataType_2_t*)ramdata->pData->pv)->Label, lbuf);
	
	v_LCDGotoXY_v1(0, 0);
	for (i = 0; i < 16; i++)
		v_LCDSend_v1(LCD_ASCII, (uint8_t)*(lbuf + i));
	for (i = 0; i < 16; i++)
		lbuf[i] = ' ';
	lbuf[16] = 0;
	
	
	u8_Tmp_0 = strlen(lbuf);
	
	strcpy(lbuf, ((DataType_2_t*)ramdata->pData->pv)->ParamLabel);
	if (strlen(lbuf) == 0)
		b_NoParamLabel = true;
	lbuf[strlen(lbuf)] = ' ';
	
	Parse_UnitName(((DataType_2_t*)ramdata->pData->pv)->Value.Units, PGM_Buffer0);
	u8_Tmp_1 = strlen(PGM_Buffer0);
	
	
	//if (Msg.Editing)
	//	VST_21(PGM_Buffer0);
	//else
	//VST_3(&RamData.Data1, PGM_Buffer0);
	VST(ramdata, PGM_Buffer1, 0);
	
	u8_Tmp_2 = strlen(PGM_Buffer1);
	u8_Tmp_3 = u8_Tmp_0 - u8_Tmp_2 - u8_Tmp_1;
		
	//GetCenteredString(PGM_Buffer0, lbuf);
	if (b_NoParamLabel)
	{
		u8_Tmp_3 = GetCenteredValue(u8_Tmp_3);
	}
	
	strcpy(lbuf + u8_Tmp_3, PGM_Buffer1);
	
	strcpy(lbuf + u8_Tmp_3 + u8_Tmp_2, PGM_Buffer0);
	lbuf[u8_Tmp_3+u8_Tmp_2+u8_Tmp_1] = ' ';
	lbuf[16] = 0;
	
	v_LCDGotoXY_v1(0, 1);
	for (i = 0; i < 16; i++)
		v_LCDSend_v1(LCD_ASCII, (uint8_t)*(lbuf + i));
}



/*
	Новая версия VST
*/
void
VST(RamDataContainer_t* ramdata, char* pbuf, uint8_t num_of_value)
{
	Retval_t ret;
	ValueType_t type = 0;
	uint16_t* pv = 0;
	uint16_t a;
	uint16_t b;
	uint16_t au16;
	uint16_t bu16;
	static	uint8_t	u8_Divider = PARAMETER_BLINKING;
	static	uint8_t	u8_Divider2 = 1 << PARAMETER_BLINKDIV;
	uint8_t	i = 0;
	int16_t i16temp;
	
	
	
	switch (ramdata->pData->Type)
	{
		case DATA_TYPE_2:
		{
			
			pv = (uint16_t*)((DataType_2_t*)(ramdata->pData->pv))->Value.pvData;
			type = ((DataType_2_t*)(ramdata->pData->pv))->Value.Type;
			
			break;
		}
		
		case DATA_TYPE_3:
		{
			//ret.u16 = (uint16_t)*((uint16_t*)((DataType_3_t*)(ramdata->pData->pv))->Value.pvData);
			//type = ((DataType_3_t*)(ramdata->pData->pv))->Value.Type;
			
			break;
		}
		
		case DATA_TYPE_MAIN_3_2:
		{
			if (num_of_value == 0)
			{
				pv = (uint16_t*)((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_0.pvData;
				type = ((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_0.Type;
			}
			else if (num_of_value == 1)
			{
				pv = (uint16_t*)((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_1.pvData;
				type = ((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_1.Type;
			}	
			
			break;
		}
		
		default:
			break;
	}
	
	
	switch (type)
	{
		case U16:
		case U16nP:
		case S16:
		case S16nP:
		case S16PP:
		{	
			
			if (ramdata->UserEdit)
			{
				ret.u16 = ramdata->Msg.st.ret.u16;
			}
			else
			{
				switch (ramdata->pData->Type)
				{
					case DATA_TYPE_2:
						ret.u16 = (uint16_t)*((uint16_t*)((DataType_2_t*)(ramdata->pData->pv))->Value.pvData);
						break;
						
					case DATA_TYPE_MAIN_3_2:
					{	
						if (num_of_value == 0)
							ret.u16 = (uint16_t)*((uint16_t*)((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_0.pvData);
						else if (num_of_value == 1)
							ret.u16 = (uint16_t)*((uint16_t*)((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_1.pvData);
						break;
					}
						
					default:
						break;
				}
				
			}
			
			if (type == U16)
			{
				Round(ret.u16, &au16, &bu16);
				sprintf((char*)(pbuf), "%01u.%01u",  au16, bu16);
			}
			else if (type == U16nP)
			{
				sprintf((char*)(pbuf), "%01u",  ret.u16);
			}
			else if (type == S16)
			{
				if (RoundS16(ret.s16, &a, &b))
				{
					sprintf((char*)(pbuf), "-%01d.%01d",  a,b);
				}
				else
				{
					sprintf((char*)(pbuf), "%01d.%01d",  a,b);
				}
				
				//i16temp = ret.s16;
				//sprintf((char*)(pbuf), "%01d.%01u",  a, b);
				
			}
			else if (type == S16nP){
				sprintf((char*)(pbuf), "%01d",  ret.s16);
			}
			else if (type == S16PP){
				if (RoundS16(ret.s16, &a, &b))
				{
					sprintf((char*)(pbuf), "-%01d.%01d",  a,b);
				}
				else
				{
					sprintf((char*)(pbuf), "%01d.%01d",  a,b);
				}
			}
			
			
			break;
		}
			
		case (TYPE_Date_1_t):
			if (ramdata->UserEdit)
			{
				PARSE_TYPE_Date_t((DateTime_t*)&(ramdata->Msg.stDateTime), 0, pbuf);
			}
			else
			{
				PARSE_TYPE_Date_t((DateTime_t*)pv, 0, pbuf);
			}
			
			break;
		
		case (TYPE_Time_1_t):
			
			if (ramdata->UserEdit)
			{
				PARSE_TYPE_Time_t((DateTime_t*)&(ramdata->Msg.stDateTime), 1, pbuf);
			}
			else
			{
				PARSE_TYPE_Time_t((DateTime_t*)pv, 1, pbuf);
			}
			break;
			
		case (BOOL):
		{
			if (ramdata->UserEdit)
			{
				ret.u16 = ramdata->Msg.st.ret.u16;
			}
			else
			{
				ret.u16 = (uint16_t)*((uint16_t*)((DataType_2_t*)(ramdata->pData->pv))->Value.pvData);
			}
			
			PARSE_TYPE_bool(ret.u16, pbuf);

			// Выход
			break;
		}
		
		case (TYPE_ICHARGE_MODE):
		case (TYPE_MPP):
		case (TYPE_BAT):
		{
			if (ramdata->UserEdit)
			{
				ret.u16 = ramdata->Msg.st.ret.u16;
			}
			else
			{
				switch (ramdata->pData->Type)
				{
					case DATA_TYPE_2:
						ret.u16 = (uint16_t)*((uint16_t*)((DataType_2_t*)(ramdata->pData->pv))->Value.pvData);
						break;
						
					case DATA_TYPE_MAIN_3_2:
					{	
						if (num_of_value == 0)
							ret.u16 = (uint16_t)*((uint16_t*)((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_0.pvData);
						else if (num_of_value == 1)
							ret.u16 = (uint16_t)*((uint16_t*)((DataType_Main_3_2_t*)(ramdata->pData->pv))->Value_1.pvData);
						break;
					}
						
					default:
						break;
				}
			}
			
			if (type == TYPE_ICHARGE_MODE)
				PARSE_TYPE_ICHARGE_MODE(ret.u16, pbuf);
			else if (type == TYPE_MPP)
				PARSE_TYPE_MPP(ret.u16, pbuf);
			else if (type == TYPE_BAT)
				PARSE_TYPE_BAT(ret.u16, pbuf);
			

			// Выход
			break;
		}
				
		default:
			*pbuf = 0;
			break;
	}
	
	if (ramdata->UserEdit)
	{
		
		switch (type)
		{
			case U16:
			case U16nP:
			case BOOL:
			{
				if (u8_Divider == 0)
				{
					for (i = 0; i < strlen(pbuf); i++)
						*(pbuf + i) = ' ';
					*(pbuf + i + 1) = 0;
				}
				
				break;
			}
				
			case (TYPE_Date_1_t):
			{
				if (u8_Divider == 0)
				{
					if (Table.Unsort.CARRIAGE_TYPE_Date_1_t == 1)
					{
						*(pbuf + 0) = ' ';
						*(pbuf + 1) = ' ';
					}
					else if (Table.Unsort.CARRIAGE_TYPE_Date_1_t == 2)
					{
						*(pbuf + 3) = ' ';
						*(pbuf + 4) = ' ';
					}
					else if (Table.Unsort.CARRIAGE_TYPE_Date_1_t == 3)
					{
						*(pbuf + 6) = ' ';
						*(pbuf + 7) = ' ';
						*(pbuf + 8) = ' ';
						*(pbuf + 9) = ' ';
					}
				}
				
				break;
			}
			
			case (TYPE_Time_1_t):
			{
				if (u8_Divider == 0)
				{
					if (Table.Unsort.CARRIAGE_TYPE_Time_1_t == 1)
					{
						*(pbuf + 0) = ' ';
						*(pbuf + 1) = ' ';
					}
					else if (Table.Unsort.CARRIAGE_TYPE_Time_1_t == 2)
					{
						*(pbuf + 3) = ' ';
						*(pbuf + 4) = ' ';
					}
					else if (Table.Unsort.CARRIAGE_TYPE_Time_1_t == 3)
					{
						*(pbuf + 6) = ' ';
						*(pbuf + 7) = ' ';
					}
				}
				
				break;
			}
					
			default:
				break;
		}
		
		
		
		
		
		
		
		if (u8_Divider == 0)
		{
			if (u8_Divider2 == 0)
			{
				u8_Divider2 = 1 << PARAMETER_BLINKDIV;
				u8_Divider = PARAMETER_BLINKING;
			}
			else
				u8_Divider2--;
		}
		else
		{
			if (u8_Divider2 == 0)
			{
				u8_Divider2 = 1 << PARAMETER_BLINKDIV;
				u8_Divider--;
			}
			else
				u8_Divider2--;
		}
	}
}


void
Round(uint16_t in, uint16_t* out1, uint16_t* out2)
{
	uint16_t a;
	uint16_t b;
	
	a = in / 10;
	b = in - a*10;
	
	*out1 = a;
	*out2 = b;
	
	//return a;
}

/*
	Делим число на целую и десятичную часть. Например 123 преобразуем в 12 и 3. Такое представление можно использовать как для отображения температур и других
	целых параметров, так и дробных вроде токов и напряжений. 
	Функция одинаково работает как для знаковых так и беззнаковых чисел (int16_t и uint16_t)
	Нихуя не работает!!!
	plusminus = 0 - число положит, == 1 число отрицат
*/
bool
RoundS16(int16_t in, uint16_t* out1, uint16_t* out2)
{
	uint16_t a;
	uint16_t b;
	
	uint16_t c;
	//int16_t d;
	
	if (in < 0)
	{
		c = 0xffff - (uint16_t)in;
		//d = (int16_t)c;
		
		a = c / 10;
		b = c - a*10;
		
		*out1 = a;
		*out2 = b;
		
		return true;
	}
	else
	{
		a = in / 10;
		b = in - a*10;
		
		*out1 = a;
		*out2 = b;
		
		return false;
	}
	
	
}


/*
	???
*/
void
GetCenteredString(char* instr, char* dist)
{
	uint8_t u8_Start = 0;
	uint8_t u8_Tmp = 0;
	uint8_t u8_Tmp2 = 0;
	
	u8_Tmp = strlen(instr);
	
	if (u8_Tmp < 16)
	{
		u8_Start = (16 - u8_Tmp) / 2;
	}
	
	strcpy(dist+u8_Start, instr);
	
	u8_Tmp2 = strlen(dist);
	
	dist[u8_Tmp2] = ' ';
}


uint8_t
GetCenteredValue(uint8_t UnusedArea)
{
	uint8_t RetVal = 16;
	
	if (UnusedArea < 16)
		RetVal = UnusedArea / 2;
	
	return RetVal;
}
/**/


void
Parse_UnitName(UnitName_t code, char* pbuf)
{
	//UnitName_t type = (UnitName_t)code;
	
	switch (code)
	{
		case UNITS_TIME:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[0])));
			break;
		case UNITS_FREQ:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[1])));
			break;
		case UNITS_AMPER:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[2])));
			break;
		case UNITS_VOLT:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[3])));
			break;
		case UNITS_TEMP:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[4])));
			break;
		case UNITS_WATT:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[5])));
			break;
		case UNITS_KWATT:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[6])));
			break;
		case UNITS_PERCENT:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[7])));
			break;
		case UNITS_CAP_Ah:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UnitName_t[8])));
			break;
		
		default:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_NULL[0])));
			break;
	}
}

/*
	void	PARSE_TYPE_Date_t
	code - 	input pointer to struct of type DateTime_t,
	mode - 	input 8-bit var: 0 or 1,
	pbuf - 	output pointer to array of char,
*/
void
PARSE_TYPE_Date_t(DateTime_t* code, uint8_t mode, char* pbuf)
{
	sprintf((char*)pbuf, "%02u", code->Day);
	pbuf[2] = '-';
	sprintf((char*)(pbuf + 3), "%02u", code->Month);
	pbuf[5] = '-';
	sprintf((char*)(pbuf + 6), "%04u", code->Year);
	pbuf[6] = '2';
	//pbuf[10] = ' ';
	
	if (mode == 1)
	{
		pbuf[10] = ' ';
		sprintf((char*)(pbuf + 11), "%02u", code->Hour);
		pbuf[13] = ':';
		sprintf((char*)(pbuf + 14), "%02u", code->Minute);
	}
}

/*
	void	PARSE_TYPE_Time_t
	code - 	input pointer to struct of type DateTime_t,
	mode - 	input 8-bit var: 0 or 1,
	pbuf - 	output pointer to array of char,
*/
void
PARSE_TYPE_Time_t(DateTime_t* code, uint8_t mode, char* pbuf)
{
	sprintf((char*)pbuf, "%02u", code->Hour);
	pbuf[2] = ':';
	sprintf((char*)(pbuf + 3), "%02u", code->Minute);
	if (mode == 1)
	{
		pbuf[5] = ':';
		sprintf((char*)(pbuf + 6), "%02u", code->Second);
	}
}

void
PARSE_TYPE_bool(uint16_t code, char* pbuf)
{
	bool type = (bool)code;
	
	switch (type)
	{
		case true:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_bool[0])));
			break;
		case false:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_bool[1])));
			break;
		default:
			break;
	}
}

void
PARSE_TYPE_ICHARGE_MODE(uint16_t code, char* pbuf)
{
	MpptChargeStage_t type = (MpptChargeStage_t)code;
	
	switch (type)
	{
		case MPPT_CHARGESTAGE_MPPT:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_ICHARGE_MODE[0])));
			break;
		case MPPT_CHARGESTAGE_DCVOLTAGE:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_ICHARGE_MODE[1])));
			break;
		case MPPT_CHARGESTAGE_DISABLED:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_ICHARGE_MODE[2])));
			break;
		default:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UNK[0])));
			break;
	}
}

void
PARSE_TYPE_MPP(uint16_t code, char* pbuf)
{
	MPP_t type = (MPP_t)code;
	
	switch (type)
	{
		case MPP_DIS:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_MPP[0])));
			break;
		case MPP_NORM:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_MPP[1])));
			break;
		case MPP_STAB:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_MPP[2])));
			break;
		case MPP_KZ:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_MPP[3])));
			break;
		default:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UNK[0])));
			break;
	}
}

void
PARSE_TYPE_BAT(uint16_t code, char* pbuf)
{
	BatType_t type = (BatType_t)code;
	
	switch (type)
	{
		case BAT_LEAD_ACID:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_BAT[0])));
			break;
		case BAT_GEL_AGM:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_BAT[1])));
			break;
		case BAT_LIION_37:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_BAT[2])));
			break;
		case BAT_LIION_39:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_BAT[3])));
			break;
		default:
			strcpy_P(pbuf, (PGM_P)pgm_read_word(&(spgm_UNK[0])));
			break;
	}
}
