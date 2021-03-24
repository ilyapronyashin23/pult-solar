#include "Keyboard.h"
//#include	"Menu_LinkedList.h"
//#include	"Display_Driver_MT16S2D.h"
#include "avr/io.h"
#include "Modbus.h"
#include "DataConvert.h"
#include "DisplayFormatter.h"
#include "Main.h"
#include "libc/avr/pgmspace.h"

EXTIPush_t ButtonCodes[6] = {NoEXTI, NoEXTI, NoEXTI, NoEXTI, NoEXTI, NoEXTI};
bool PORT_Keyb[6] = {false,	false, false, false, false, false};
uint8_t u8BlinkCount[6] = {0, 0, 0, 0, 0, 0};
uint8_t DelayCount[6] = {DELAY_COUNT, DELAY_COUNT, DELAY_COUNT, DELAY_COUNT, DELAY_COUNT, DELAY_COUNT};
uint16_t u16_SpeedCount[6] = {0, 0, 0, 0, 0, 0};
extern Next_Send_Function_t Next_Send_Function;
extern ConvertTable_t Table;
extern bool Blank_Menu;
extern st_NoAnswer_t NoAnswer;

/*
extern	MenuLevel_t			et_MenuLevel;
extern	Dynamic_Data_t		RAM_Data;
extern	Msg_t				Msg;
extern	Element_t*			p_List;
extern	Settings			st_Settings;
*/

bool b_Latch = true;
bool b_Latch2 = false;


void DoAction( RamList_t* ram_list, EXTIPush_t* pt_ButtonCodes)
{
	static uint8_t u8_Divider = PARAMETER_MENUSCROLL;
	
	
	
	switch (ram_list->p_now->Level)
	{
		case (LEVEL0):
		{
			
			
			/**/
			
			if (pt_ButtonCodes[5] == But1)
			{
				if (ram_list->p_now == ram_list->p_ram_parview)
				{
					ram_list->p_now = ram_list->p_ram_main;
				}
			}
			
			/**/
			
			if (pt_ButtonCodes[4] == But2)
			{
			}
			if (pt_ButtonCodes[4] == But2_Long_First)
			{
				if (ram_list->p_now == ram_list->p_ram_parview){
					ram_list->p_now = ram_list->p_ram_main;
				}
				
				LList_Low(ram_list);
				
				
			}
			
			/**/
			
			if (pt_ButtonCodes[3] == But3)
			{
				if (!b_IsModeEqualsParview(ram_list))
				{
					ram_list->p_now = ram_list->p_ram_parview;
					//Jump_RunnerParamView(ram_list);
				}
				else
				{
					LList_Prev(ram_list);
				}
			}
			
			/**/
			
			if (pt_ButtonCodes[2] == But4)
			{
				
				
				if (!b_IsModeEqualsParview(ram_list))
				{
					ram_list->p_now = ram_list->p_ram_parview;
					//Jump_RunnerParamView(ram_list);
				}
				else
				{
					LList_Next(ram_list);
				}
			}
			
			/**/
			
			if (pt_ButtonCodes[1] == But5)
			{
				LList_Stop(ram_list);
			}
			if (pt_ButtonCodes[1] == But5_Long_First)
			{
				LList_Stop(ram_list);
			}
			
			/**/
			
			if (pt_ButtonCodes[0] == But6)
			{
				
			}
			if (pt_ButtonCodes[0] == But6_Long_First)
			{
				LList_Start(ram_list);
			}	
			
			//if ( pgm_read_byte(&(ram_list->p_ram_parview->pList->Type)) == DATA_TYPE_MAIN_3_2)
			//{
			//}
			
			
			if (b_IsScreen0Page(ram_list))
			{
				
				if (!b_IsModeEqualsParview(ram_list))
					ram_list->p_now = ram_list->p_ram_parview;
					//Jump_RunnerParamView(ram_list);
			}
			
		
			break;
		}
		
		case (LEVEL1):
		{
			if (pt_ButtonCodes[5] == But1)
			{
				ram_list->p_now->Blank_Menu = true;
				NoAnswer.b_Res = false;
				LList_Up(ram_list);
			}
			if (pt_ButtonCodes[5] == But1_Long_First)
			{
				ram_list->p_now->Blank_Menu = true;
				NoAnswer.b_Res = false;
				LList_Up(ram_list);
			}
			
			
			
			if (pt_ButtonCodes[4] == But2)
			{
				LList_Low(ram_list);
			}
			if (pt_ButtonCodes[4] == But2_Long_First)
			{
				LList_Low(ram_list);
				//ramdata->UserEdit ^= 1;
			}
			
			
			
			if (pt_ButtonCodes[3] == But3)
			{
				LList_Prev(ram_list);
			}
			if (pt_ButtonCodes[3] == But3_Long_First)
			{
				LList_Prev(ram_list);
			}
			
			
			
			if (pt_ButtonCodes[2] == But4)
			{
				LList_Next(ram_list);
			}
			if (pt_ButtonCodes[2] == But4_Long_First)
			{
				LList_Next(ram_list);
			}
			
			
			
			if (pt_ButtonCodes[1] == But5)
			{
				
			}
			
			
			
			if (pt_ButtonCodes[0] == But6)
			{
				
			}
			
			break;
		}
		
		case (LEVEL2):
		case (LEVEL3):
		{
			if (pt_ButtonCodes[5] == But1)
			{
				if (ram_list->p_now->UserEdit)
				{
					Table.Unsort.ENTER_PASSWORD = 0;
					Table.Unsort.CARRIAGE_DIGIT = 0;
					LList_Cancel(ram_list);
				}
				else
				{
					//PORTD ^= 1<<7;
					Table.Unsort.t_PASSWORD_STEP = PSW_Step_Enter;
					LList_Up(ram_list);
				}
				
			}
			
			/**/
			
			if (pt_ButtonCodes[4] == But2)
			{
				if (ram_list->p_now->UserEdit)
				{
					switch (ram_list->p_now->pData->Type)
					{
						case (DATA_TYPE_2):
						{					
							if ((((DataType_2_t*)ram_list->p_now->pData->pv)->Opt == 1) |
								(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == TYPE_Date_1_t) |
								(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type == TYPE_Time_1_t))
							{
								LList_Edit(ram_list);
							}
							
							break;
						}
						
						default:
							break;
					}
				}
				else
				{
					LList_Low(ram_list);
				}
				
				
				
				
			}
			if (pt_ButtonCodes[4] == But2_Long_First)
			{
				
				switch (ram_list->p_now->pData->Type)
				{
					case (DATA_TYPE_2):
					{
						//
						if (ram_list->p_now->UserEdit)
						{
							Table.Unsort.CARRIAGE_INV_DIGITAL_INPUT = 0;
							Table.Unsort.CARRIAGE_TYPE_Date_1_t = 0;
							Table.Unsort.CARRIAGE_TYPE_Time_1_t = 0;
							
							/*
							switch (((DataType_2_t*)(ramdata->pData->pv))->Value.Type)
							{
								case (TYPE_Date_1_t):
								{
									Msg.t_EditFromAnotherElem.Active = true;
									Msg.t_EditFromAnotherElem.Type = EDIT_AN_ELEM_DATESET;
									v_Navigation_Next_V2();
									
									break;
								}
								
								case (TYPE_Time_1_t):
								{
									Msg.t_EditFromAnotherElem.Active = true;
									Msg.t_EditFromAnotherElem.Type = EDIT_AN_ELEM_TIMESET;
									Navigation_Up();
									
									
									break;
								}
								
								default:
									break;
							}
							*/
							
							/*
							if ((((DataType_2_t*)(ramdata->pData->pv))->Opt == 0) &
								(((DataType_2_t*)(ramdata->pData->pv))->Value.Type = ))
							{
								
							}
							*/
							
							ram_list->p_now->UserEdit = false;
							Next_Send_Function = F_X10;
						}
						
						//Вход в меню редактирования
						else
						{
							
							LList_Edit(ram_list);
						}
						
						break;
					}
					
					default:
						break;
				}
				
				
				
			}
			
			/**/
			
			if (pt_ButtonCodes[3] == But3)
			{
				if (ram_list->p_now->UserEdit)
				{
					//Navigation_MinusParam(INCREMENT_1, 0);
					LList_MinusParam(ram_list, INCREMENT_1, 0);
				}
				else
				{
					LList_Prev(ram_list);
				}
				
			}
			
			if ((pt_ButtonCodes[3] == But3_Long) |
				(pt_ButtonCodes[3] == But3_Long_x5Speed) |
				(pt_ButtonCodes[3] == But3_Long_x10Speed) |
				(pt_ButtonCodes[3] == But3_Long_x50Speed) |
				(pt_ButtonCodes[3] == But3_Long_x100Speed))
			{
				if (ram_list->p_now->UserEdit)
				{
					switch (pt_ButtonCodes[3])
					{
						case (But3_Long):
							//Navigation_MinusParam(INCREMENT_1, u8_Divider);
							LList_MinusParam(ram_list, INCREMENT_1, u8_Divider);
							break;
						
						case (But3_Long_x5Speed):
							//Navigation_MinusParam(INCREMENT_5, u8_Divider);
							LList_MinusParam(ram_list, INCREMENT_5, u8_Divider);
							break;
							
						case (But3_Long_x10Speed):
							//Navigation_MinusParam(INCREMENT_10, u8_Divider);
							LList_MinusParam(ram_list, INCREMENT_10, u8_Divider);
							break;
							
						case (But3_Long_x50Speed):
							//Navigation_MinusParam(INCREMENT_50, u8_Divider);
							LList_MinusParam(ram_list, INCREMENT_50, u8_Divider);
							break;
						
						case (But3_Long_x100Speed):
							//Navigation_MinusParam(INCREMENT_100, u8_Divider);
							LList_MinusParam(ram_list, INCREMENT_100, u8_Divider);
							break;
							
						default:
							break;
					}
				}
				else
				{
					if (u8_Divider == 0)
					{
						LList_Prev(ram_list);
					}
				}
			}
			
			/**/
			
			if (pt_ButtonCodes[2] == But4)
			{
				if (ram_list->p_now->UserEdit)
				{
					
					LList_PlusParam(ram_list, INCREMENT_1, 0);
					
				}
				else
				{
					// ИЗБЕГАНИЕ ОБХОДА ВВОДА ПАРОЛЯ
					// Для всех случаев кроме DATA_TYPE_2. причем проверять на ...Options != 1 нужно убедившись что тип именно DATA_TYPE_3.
					if (ram_list->p_now->pData->Type == DATA_TYPE_2)
					{
						if	(((DataType_2_t*)ram_list->p_now->pData->pv)->Opt != 1)
						{
							LList_Next(ram_list);
						}
					}
					else
					{
						LList_Next(ram_list);
					}
				}
			}
			
			if ((pt_ButtonCodes[2] == But4_Long) |
				(pt_ButtonCodes[2] == But4_Long_x5Speed) |
				(pt_ButtonCodes[2] == But4_Long_x10Speed) |
				(pt_ButtonCodes[2] == But4_Long_x50Speed) |
				(pt_ButtonCodes[2] == But4_Long_x100Speed))
			{
				if (ram_list->p_now->UserEdit)
				{
					switch (pt_ButtonCodes[2])
					{
						case (But4_Long):
						LList_PlusParam(ram_list, INCREMENT_1, u8_Divider);
						break;
					
						case (But4_Long_x5Speed):
						LList_PlusParam(ram_list, INCREMENT_5, u8_Divider);
						break;
						
						case (But4_Long_x10Speed):
						LList_PlusParam(ram_list, INCREMENT_10, u8_Divider);
						break;
						
						case (But4_Long_x50Speed):
						LList_PlusParam(ram_list, INCREMENT_50, u8_Divider);
						break;
						
						case (But4_Long_x100Speed):
						LList_PlusParam(ram_list, INCREMENT_100, u8_Divider);
						break;
						
						default:
							break;
					}
				}
				else
				{
					
					if (u8_Divider == 0)
					{
#ifdef _DEBUG_
						LList_Next(ram_list);
#else					
						if (ram_list->p_now->pData->Type == DATA_TYPE_2)
						{
							if	(((DataType_2_t*)ram_list->p_now->pData->pv)->Opt != 1)
							{
								LList_Next(ram_list);
							}
						}
						else
						{
							LList_Next(ram_list);
						}
#endif
					}
					
				}
			}
			
			/**/
			
			if (pt_ButtonCodes[1] == But5)
			{
				
			}
			
			/**/
			
			if (pt_ButtonCodes[0] == But6)
			{
				
			}
			
			break;
		}
		
		default:
			break;
	}
	
	if (u8_Divider == 0)
		u8_Divider = PARAMETER_MENUSCROLL;
	else
		u8_Divider--;
}
/**/

void
GetButtonCodes(EXTIPush_t* pt_ButtonCodes_Container)
{
	static	bool	longpress[6] 	= {false, false, false, false, false, false};
	static	bool	afterlong[6] 	= {false, false, false, false, false, false};
	static	bool	firstlong[6]	= {true, true, true, true, true, true};
	
	pt_ButtonCodes_Container[0] = NoEXTI;
	pt_ButtonCodes_Container[1] = NoEXTI;
	pt_ButtonCodes_Container[2] = NoEXTI;
	pt_ButtonCodes_Container[3] = NoEXTI;
	pt_ButtonCodes_Container[4] = NoEXTI;
	pt_ButtonCodes_Container[5] = NoEXTI;
	
	(PING & 1) ?
		(PORT_Keyb[0] = true) :
		(PORT_Keyb[0] = false) ;
	(PING & 2) ?
		(PORT_Keyb[1] = true) :
		(PORT_Keyb[1] = false) ;
	(PINC & 1) ?
		(PORT_Keyb[2] = true) :
		(PORT_Keyb[2] = false) ;
	(PINC & 2) ?
		(PORT_Keyb[3] = true) :
		(PORT_Keyb[3] = false) ;
	(PINC & 4) ?
		(PORT_Keyb[4] = true) :
		(PORT_Keyb[4] = false) ;
	(PINC & 8) ?
		(PORT_Keyb[5] = true) :
		(PORT_Keyb[5] = false) ;
	
	/*
		Определение характера нажатия и защита от дребезга
	*/
	if (true)	//РѕР±С‹С‡РЅС‹Р№
	{
		/******0*********/
		if (!PORT_Keyb[0]){
			u8BlinkCount[0] = 4;
			if (!longpress[0])
			{
				if (DelayCount[0] > 0) DelayCount[0]--;
				if (DelayCount[0] == 0) longpress[0] = true;
			}
		}
		else if (PORT_Keyb[0]){
			DelayCount[0] = 10;
			longpress[0] = false;
			firstlong[0] = true;
		}
		/****************/
		
		
		/*******1********/
		if (!PORT_Keyb[1]){
			u8BlinkCount[1] = 4;
			if (!longpress[1])
			{
				if (DelayCount[1] > 0) DelayCount[1]--;
				if (DelayCount[1] == 0) longpress[1] = true;
			}
		}
		else if (PORT_Keyb[1]){
			DelayCount[1] = 10;
			longpress[1] = false;
		}
		/****************/
		
		/********2*******/
		if (!PORT_Keyb[2]){
			u8BlinkCount[2] = 4;
			if (!longpress[2])
			{
				if (DelayCount[2] > 0) DelayCount[2]--;
				if (DelayCount[2] == 0) longpress[2] = true;
			}
		}
		else if (PORT_Keyb[2]){
			DelayCount[2] = 10;
			longpress[2] = false;
			u16_SpeedCount[2] = 0;
		}	
		/****************/
		
		/*******3*******/
		if (!PORT_Keyb[3]){
			u8BlinkCount[3] = 4;
			if (!longpress[3])
			{
				if (DelayCount[3] > 0) DelayCount[3]--;
				if (DelayCount[3] == 0) longpress[3] = true;
			}
		}
		else if (PORT_Keyb[3]){
			DelayCount[3] = 10;
			longpress[3] = false;
			u16_SpeedCount[3] = 0;
		}
		/****************/
		
		/*******4********/
		if (!PORT_Keyb[4]){
			u8BlinkCount[4] = 4;
			if (!longpress[4])
			{
				if (DelayCount[4] > 0) DelayCount[4]--;
				if (DelayCount[4] == 0) longpress[4] = true;
			}
		}
		else if (PORT_Keyb[4]){
			DelayCount[4] = 10;
			longpress[4] = false;
			firstlong[4] = true;
		}
		/****************/
		
		/*******5********/
		if (!PORT_Keyb[5]){
			u8BlinkCount[5] = 4;
			if (!longpress[5])
			{
				if (DelayCount[5] > 0) DelayCount[5]--;
				if (DelayCount[5] == 0) longpress[5] = true;
			}
		}
		else if (PORT_Keyb[5]){
			DelayCount[5] = 10;
			longpress[5] = false;
			firstlong[5] = true;
		}
		/****************/
		
		/*
			Определение кратко нажатых кнопок
		*/
		
		if (u8BlinkCount[0] != 0){
			u8BlinkCount[0]--;
			if (u8BlinkCount[0] == 0){
				if (afterlong[0])
				{
					afterlong[0] = false;
					pt_ButtonCodes_Container[0] = NoEXTI;
				}
				else
					if (longpress[5])
						pt_ButtonCodes_Container[0] = But1Long_But6;
					else
						pt_ButtonCodes_Container[0] = But6;
					//pt_ButtonCodes_Container[0] = But6;
			}
		}
		if (u8BlinkCount[1] != 0){
			u8BlinkCount[1]--;
			if (u8BlinkCount[1] == 0){
				if (afterlong[1])
				{
					afterlong[1] = false;
					pt_ButtonCodes_Container[1] = NoEXTI;
				}
				else
					if (longpress[5])
						pt_ButtonCodes_Container[1] = But1Long_But5;
					else
						pt_ButtonCodes_Container[1] = But5;
			}
		}
		if (u8BlinkCount[2] != 0){
			u8BlinkCount[2]--;
			if (u8BlinkCount[2] == 0){
				if (afterlong[2])
				{
					afterlong[2] = false;
					pt_ButtonCodes_Container[2] = NoEXTI;
				}
				else
					if (longpress[5])
						pt_ButtonCodes_Container[2] = But1Long_But4;
					else
						pt_ButtonCodes_Container[2] = But4;
			}
		}
		if (u8BlinkCount[3] != 0){
			u8BlinkCount[3]--;
			if (u8BlinkCount[3] == 0){
				if (afterlong[3])
				{
					afterlong[3] = false;
					pt_ButtonCodes_Container[3] = NoEXTI;
				}
				else
					//pt_ButtonCodes_Container[3] = But3;
					if (longpress[5])
						pt_ButtonCodes_Container[3] = But1Long_But3;
					else
						pt_ButtonCodes_Container[3] = But3;
			}
		}
		if (u8BlinkCount[4] != 0){
			u8BlinkCount[4]--;
			if (u8BlinkCount[4] == 0){
				if (afterlong[4])
				{
					afterlong[4] = false;
					pt_ButtonCodes_Container[4] = NoEXTI;
				}
				else
				{
					pt_ButtonCodes_Container[4] = But2;
				}
			}
		}
		if (u8BlinkCount[5] != 0){
			u8BlinkCount[5]--;
			if (u8BlinkCount[5] == 0){
				if (afterlong[5])
				{
					afterlong[5] = false;
					pt_ButtonCodes_Container[5] = NoEXTI;
				}
				else
					pt_ButtonCodes_Container[5] = But1;
			}
		}
	}
		
/***********************************************************************************/

	/*
		Определение долго нажатых кнопок
	*/
	
	if (longpress[0])		//editing
	{
		afterlong[0] = true;
		
		if (!PORT_Keyb[0] & (DelayCount[0] == 0)){
			DelayCount[0] = 4;
		}
		else if (!PORT_Keyb[0] & (DelayCount[0] != 0)){
			DelayCount[0]--;
			if (DelayCount[0] == 0){
				if (firstlong[0])
				{
					firstlong[0] = false;
					pt_ButtonCodes_Container[0] = But6_Long_First;
				}
				else
					pt_ButtonCodes_Container[0] = But6_Long;
			}
		}
	}
	
	if (longpress[1])		//editing
	{
		afterlong[1] = true;
		
		if (!PORT_Keyb[1] & (DelayCount[1] == 0)){
			DelayCount[1] = 4;
		}
		else if (!PORT_Keyb[1] & (DelayCount[1] != 0)){
			DelayCount[1]--;
			if (DelayCount[1] == 0){
				if (firstlong[1])
				{
					firstlong[1] = false;
					pt_ButtonCodes_Container[1] = But5_Long_First;
				}
				else
					pt_ButtonCodes_Container[1] = But5_Long;
			}
		}
	}
	
	if (longpress[2])		//editing
	{
		afterlong[2] = true;
		
		if (!PORT_Keyb[2] & (DelayCount[2] == 0)){
			DelayCount[2] = 4;
		}
		else if (!PORT_Keyb[2] & (DelayCount[2] != 0))
		{
			DelayCount[2]--;
			if (DelayCount[2] == 0)
			{
				if (longpress[5])
					pt_ButtonCodes_Container[2] = But1Long_But4Long;
				else
				{
					if ((u16_SpeedCount[2] > 0) & (u16_SpeedCount[2] <= 50))
					{
						pt_ButtonCodes_Container[2] = But4_Long;
					}
						
					else if ((u16_SpeedCount[2] > 50) & (u16_SpeedCount[2] <= 100))
					{
						pt_ButtonCodes_Container[2] = But4_Long_x5Speed;
					}
						
					//else if (u16_SpeedCount[2] > 200)
					else if ((u16_SpeedCount[2] > 100) & (u16_SpeedCount[2] <= 400))
					{
						pt_ButtonCodes_Container[2] = But4_Long_x10Speed;
					}
					
					//else if (u16_SpeedCount[2] > 300)
					else if ((u16_SpeedCount[2] > 400) & (u16_SpeedCount[2] <= 750))
					{
						pt_ButtonCodes_Container[2] = But4_Long_x50Speed;
					}
					
					else if (u16_SpeedCount[2] > 750)
					{
						pt_ButtonCodes_Container[2] = But4_Long_x100Speed;
					}
						
					
					if (u16_SpeedCount[2] <= 750+1)
						u16_SpeedCount[2] += 1;
				}
			}
		}
	}
	
	if (longpress[3])		//editing
	{
		afterlong[3] = true;
		
		if (!PORT_Keyb[3] & (DelayCount[3] == 0))
		{
			DelayCount[3] = 4;
		}
		else if (!PORT_Keyb[3] & (DelayCount[3] != 0))
		{
			DelayCount[3]--;
			if (DelayCount[3] == 0)
			{
				if (longpress[5])
					pt_ButtonCodes_Container[3] = But1Long_But3Long;
				else
				{
					if ((u16_SpeedCount[3] > 0) & (u16_SpeedCount[3] <= 50))
					{
						pt_ButtonCodes_Container[3] = But3_Long;
					}
						
					else if ((u16_SpeedCount[3] > 50) & (u16_SpeedCount[3] <= 100))
					{
						pt_ButtonCodes_Container[3] = But3_Long_x5Speed;
					}
						
					//else if (u16_SpeedCount[3] > 200)
					else if ((u16_SpeedCount[3] > 100) & (u16_SpeedCount[3] <= 400))
					{
						pt_ButtonCodes_Container[3] = But3_Long_x10Speed;
						
					}
					
					else if ((u16_SpeedCount[3] > 400) & (u16_SpeedCount[3] <= 750))
					//else if (u16_SpeedCount[3] > 300)
					{
						pt_ButtonCodes_Container[3] = But3_Long_x50Speed;
					}
					
					else if (u16_SpeedCount[3] > 750)
					{
						pt_ButtonCodes_Container[3] = But3_Long_x100Speed;
					}
						
					
					if (u16_SpeedCount[3] <= 750+1)
						u16_SpeedCount[3] += 1;
				}
			}
		}
	}
	
	if (longpress[4])		//editing
	{
		afterlong[4] = true;
		
		if (!PORT_Keyb[4] & (DelayCount[4] == 0)){
			DelayCount[4] = 4;
		}
		else if (!PORT_Keyb[4] & (DelayCount[4] != 0)){
			DelayCount[4]--;
			if (DelayCount[4] == 0){
				if (firstlong[4])
				{
					firstlong[4] = false;
					pt_ButtonCodes_Container[4] = But2_Long_First;
				}
				else
				{
					pt_ButtonCodes_Container[4] = But2_Long;
				}
			}
		}
	}
	
	
	if (longpress[5])		//editing
	{
		afterlong[5] = true;
		
		if (!PORT_Keyb[5] & (DelayCount[5] == 0)){
			DelayCount[5] = 4;
		}
		else if (!PORT_Keyb[5] & (DelayCount[5] != 0)){
			DelayCount[5]--;
			if (DelayCount[5] == 0){
				if (firstlong[5])
				{
					firstlong[5] = false;
					pt_ButtonCodes_Container[5] = But1_Long_First;
				}
				else
					pt_ButtonCodes_Container[5] = But1_Long;	
			}
		}
	}
}

