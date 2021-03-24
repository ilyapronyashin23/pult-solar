#include "Menu.h"
#include "Data.h"
#include "libc/avr/pgmspace.h"
#include "compat/ina90.h"
#include "stdlib.h"
#include "Modbus.h"
#include "string.h"

extern RamDataContainer_t RamData;
extern RamDataContainer_t RamData1;
extern RamList_t* p_ram_list;
extern Next_Send_Function_t Next_Send_Function;
extern ConvertTable_t Table;
extern TableJump_t Jumps[];
extern	PGM_Data_1_t PGM_Data_1[DATA1_MENU_DIM];
extern	PGM_Data_2_t PGM_Data_2[DATA2_MENU_DIM_X][DATA2_MENU_DIM_Y];
extern PGM_Data_Main_3_2_t PGM_Data_Main_3_2[DATAMAIN_MENU_DIM];
extern char	sram_0_2_LABEL[];

Element_t Element1[MAIN_MENU_DIM_X][MAIN_MENU_DIM_Y] PROGMEM =
{
	{	//0 LEVEL0 Главный экран
		{//0,0
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[0]),
			.pt_Next = NULL,
			.pt_Prev = NULL,
			.pt_Up = NULL,
			.pt_Low = &(Element1[1][0])
		},
		{//0,1
			.Type = DATA_TYPE_MAIN_3_2,
			.ppv_RAM_Data = &(RamData1.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_Main_3_2[0]),
			.pt_Next = &(Element1[0][2]),
			.pt_Prev = &(Element1[0][6]),
			.pt_Up = NULL,
			.pt_Low = &(Element1[1][0])
		},
		{//0,2
			.Type = DATA_TYPE_MAIN_3_2,
			.ppv_RAM_Data = &(RamData1.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_Main_3_2[1]),
			.pt_Next = &(Element1[0][3]),
			.pt_Prev = &(Element1[0][1]),
			.pt_Up = NULL,
			.pt_Low = &(Element1[1][0])
		},
		{//0,3
			.Type = DATA_TYPE_MAIN_3_2,
			.ppv_RAM_Data = &(RamData1.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_Main_3_2[2]),
			.pt_Next = &(Element1[0][5]),
			.pt_Prev = &(Element1[0][2]),
			.pt_Up = NULL,
			.pt_Low = &(Element1[1][0])
		},
		{//0,4
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[10]),
			.pt_Next = NULL,
			.pt_Prev = NULL,
			.pt_Up = NULL,
			.pt_Low = &(Element1[1][0])
		},
		{//0,5
			.Type = DATA_TYPE_MAIN_3_2,
			.ppv_RAM_Data = &(RamData1.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_Main_3_2[3]),
			.pt_Next = &(Element1[0][6]),
			.pt_Prev = &(Element1[0][3]),
			.pt_Up = NULL,
			.pt_Low = &(Element1[1][0])
		},
		{//0,6
			.Type = DATA_TYPE_MAIN_3_2,
			.ppv_RAM_Data = &(RamData1.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_Main_3_2[4]),
			.pt_Next = &(Element1[0][1]),
			.pt_Prev = &(Element1[0][5]),
			.pt_Up = NULL,
			.pt_Low = &(Element1[1][0])
		},
		{
			//0,4
		},
		{
			//0,4
		},
		{
			//0,4
		},
		{
			//0,4
		},
		{
			//0,4
		},
		{
			//0,4
		},
		{
			//0,4
		},
		{
			//0,14
		}
	},
	{	//1 LEVEL1 Список подменю
		{//1,0 УПРАВЛЕНИЕ ИНВЕРТОРОМ
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[1]),
			.pt_Next = &(Element1[1][1]),
			.pt_Prev = &(Element1[1][9]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[3][0])
		},
		{//1,1 ИЗМЕРЕНИЯ С ДАТЧИКОВ
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[2]),
			.pt_Next = &(Element1[1][2]),
			.pt_Prev = &(Element1[1][0]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[2][0])
		},
		{//1,2 УСТАНОВКА ДАТЫ/ВРЕМЕНИ
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[3]),
			.pt_Next = &(Element1[1][3]),
			.pt_Prev = &(Element1[1][1]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[4][0])
		},
		{//1,3 ПАНЕЛИ СОЛН. ВЫБОР КАНАЛА 
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[4]),
			.pt_Next = &(Element1[1][4]),
			.pt_Prev = &(Element1[1][2]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[1][7])
		},
		{//1,4 АККУМУЛЯТОР
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[5]),
			.pt_Next = &(Element1[1][5]),
			.pt_Prev = &(Element1[1][3]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[6][0])
		},
		{//1,5 КОНТР.ЗАРЯДА общий для обоих каналов 1,2
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[6]),
			.pt_Next = &(Element1[1][6]),
			.pt_Prev = &(Element1[1][4]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[7][0])
		},
		{//1,6 ИНВЕРТОР
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[7]),
			.pt_Next = &(Element1[1][9]),
			.pt_Prev = &(Element1[1][5]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[8][0])
		},
		{//1,7 СОЛН КАНАЛ 1
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[8]),
			.pt_Next = &(Element1[1][8]),
			.pt_Prev = &(Element1[1][8]),
			.pt_Up = &(Element1[1][3]),
			.pt_Low = &(Element1[5][0])
		},
		{//1,8 СОЛН КАНАЛ 2
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[9]),
			.pt_Next = &(Element1[1][7]),
			.pt_Prev = &(Element1[1][7]),
			.pt_Up = &(Element1[1][3]),
			.pt_Low = &(Element1[9][0])
		},
		{//1,9 ВЫБОР РЕЛЕ
			.Type = DATA_TYPE_1,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_1[11]),
			.pt_Next = &(Element1[1][0]),
			.pt_Prev = &(Element1[1][6]),
			.pt_Up = &(Element1[0][0]),
			.pt_Low = &(Element1[10][0])
		},
		{//1,10
		},
		{//1,11
		},
		{//1,12
		},
		{//1,13
		},
		{//1,14
		}
	},
	{	//2 LEVEL2 Измерения с датчиков
		{	//2,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][0]),
			.pt_Next = &(Element1[2][1]),
			.pt_Prev = &(Element1[2][14]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][1]),
			.pt_Next = &(Element1[2][2]),
			.pt_Prev = &(Element1[2][0]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,2
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][2]),
			.pt_Next = &(Element1[2][3]),
			.pt_Prev = &(Element1[2][1]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,3
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][3]),
			.pt_Next = &(Element1[2][4]),
			.pt_Prev = &(Element1[2][2]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,4
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][4]),
			.pt_Next = &(Element1[2][5]),
			.pt_Prev = &(Element1[2][3]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,5
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][5]),
			.pt_Next = &(Element1[2][6]),
			.pt_Prev = &(Element1[2][4]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,6
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][6]),
			.pt_Next = &(Element1[2][7]),
			.pt_Prev = &(Element1[2][5]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,7
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][7]),
			.pt_Next = &(Element1[2][8]),
			.pt_Prev = &(Element1[2][6]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,8
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][8]),
			.pt_Next = &(Element1[2][9]),
			.pt_Prev = &(Element1[2][7]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,9
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][9]),
			.pt_Next = &(Element1[2][10]),
			.pt_Prev = &(Element1[2][8]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,10
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][10]),
			.pt_Next = &(Element1[2][11]),
			.pt_Prev = &(Element1[2][9]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,11
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][11]),
			.pt_Next = &(Element1[2][12]),
			.pt_Prev = &(Element1[2][10]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,12
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][12]),
			.pt_Next = &(Element1[2][13]),
			.pt_Prev = &(Element1[2][11]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,13
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][13]),
			.pt_Next = &(Element1[2][14]),
			.pt_Prev = &(Element1[2][12]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		},
		{	//2,14
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[0][14]),
			.pt_Next = &(Element1[2][0]),
			.pt_Prev = &(Element1[2][13]),
			.pt_Up = &(Element1[1][1]),
			.pt_Low = NULL,
		}
	},
/*********************************** Управление инвертором *********************************************/
	{	//3 LEVEL2 Управление инвертором
		{//3,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[1][0]),
			.pt_Next = &(Element1[3][1]),
			.pt_Prev = &(Element1[3][5]),
			.pt_Up = &(Element1[1][0]),
			.pt_Low = NULL,
		},
		{//3,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[1][1]),
			.pt_Next = &(Element1[3][2]),
			.pt_Prev = &(Element1[3][0]),
			.pt_Up = &(Element1[1][0]),
			.pt_Low = NULL,
		},
		{//3,2
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[1][2]),
			.pt_Next = &(Element1[3][3]),
			.pt_Prev = &(Element1[3][1]),
			.pt_Up = &(Element1[1][0]),
			.pt_Low = NULL,
		},
		{//3,3
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[1][3]),
			.pt_Next = &(Element1[3][4]),
			.pt_Prev = &(Element1[3][2]),
			.pt_Up = &(Element1[1][0]),
			.pt_Low = NULL,
		},
		{//3,4
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[1][4]),
			.pt_Next = &(Element1[3][5]),
			.pt_Prev = &(Element1[3][3]),
			.pt_Up = &(Element1[1][0]),
			.pt_Low = NULL,
		},
		{//3,5
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[1][5]),
			.pt_Next = &(Element1[3][0]),
			.pt_Prev = &(Element1[3][4]),
			.pt_Up = &(Element1[1][0]),
			.pt_Low = NULL,
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		}
	},
	{	//4 LEVEL2 Установка времени/даты
		{
			//4,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[2][0]),
			.pt_Next = &(Element1[4][1]),
			.pt_Prev = &(Element1[4][1]),
			.pt_Up = &(Element1[1][2]),
			.pt_Low = NULL,
		},
		{
			//4,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[2][1]),
			.pt_Next = &(Element1[4][0]),
			.pt_Prev = &(Element1[4][0]),
			.pt_Up = &(Element1[1][2]),
			.pt_Low = NULL,
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		}
	},
	{	//5 LEVEL2 ПАНЕЛИ СОЛН. канал 1
		{//5,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[3][6]),
			.pt_Next = &(Element1[5][1]),
			.pt_Prev = &(Element1[5][6]),
			.pt_Up = &(Element1[1][7]),
			.pt_Low = NULL,
		},
		{//5,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[3][0]),
			.pt_Next = &(Element1[5][2]),
			.pt_Prev = &(Element1[5][0]),
			.pt_Up = &(Element1[1][7]),
			.pt_Low = NULL,
		},
		{//5,2
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[3][1]),
			.pt_Next = &(Element1[5][3]),
			.pt_Prev = &(Element1[5][1]),
			.pt_Up = &(Element1[1][7]),
			.pt_Low = NULL,
		},
		{//5,3
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[3][2]),
			.pt_Next = &(Element1[5][4]),
			.pt_Prev = &(Element1[5][2]),
			.pt_Up = &(Element1[1][7]),
			.pt_Low = NULL,
		},
		{//5,4
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[3][3]),
			.pt_Next = &(Element1[5][5]),
			.pt_Prev = &(Element1[5][3]),
			.pt_Up = &(Element1[1][7]),
			.pt_Low = NULL,
		},
		{//5,5
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[3][4]),
			.pt_Next = &(Element1[5][6]),
			.pt_Prev = &(Element1[5][4]),
			.pt_Up = &(Element1[1][7]),
			.pt_Low = NULL,
		},
		{//5,6
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[3][5]),
			.pt_Next = &(Element1[5][0]),
			.pt_Prev = &(Element1[5][5]),
			.pt_Up = &(Element1[1][7]),
			.pt_Low = NULL,
		},
		{//5,7
		},
		{//5,8
		},
		{//5,9
		},
		{//5,10
		},
		{//5,11
		},
		{//5,12
		},
		{//5,13
		},
		{//5,14
		}
	},
	{	//6 LEVEL2 АККУМУЛЯТОР
		{//6,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[4][0]),
			.pt_Next = &(Element1[6][1]),
			.pt_Prev = &(Element1[6][7]),
			.pt_Up = &(Element1[1][4]),
			.pt_Low = NULL,
		},
		{//6,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[4][1]),
			.pt_Next = &(Element1[6][2]),
			.pt_Prev = &(Element1[6][0]),
			.pt_Up = &(Element1[1][4]),
			.pt_Low = NULL,
		},
		{//6,2
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[4][2]),
			.pt_Next = &(Element1[6][3]),
			.pt_Prev = &(Element1[6][1]),
			.pt_Up = &(Element1[1][4]),
			.pt_Low = NULL,
		},
		{//6,3
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[4][3]),
			.pt_Next = &(Element1[6][4]),
			.pt_Prev = &(Element1[6][2]),
			.pt_Up = &(Element1[1][4]),
			.pt_Low = NULL,
		},
		{//6,4
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[4][4]),
			.pt_Next = &(Element1[6][5]),
			.pt_Prev = &(Element1[6][3]),
			.pt_Up = &(Element1[1][4]),
			.pt_Low = NULL,
		},
		{//6,5
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[4][5]),
			.pt_Next = &(Element1[6][6]),
			.pt_Prev = &(Element1[6][4]),
			.pt_Up = &(Element1[1][4]),
			.pt_Low = NULL,
		},
		{//6,6
		},
		{//6,7
		},
		{//6,8
		},
		{//6,9
		},
		{//6,10
		},
		{//6,11
		},
		{//6,12
		},
		{//6,13
		},
		{//6,14
		}
	},
	{	//7 LEVEL2 КОНТР.ЗАРЯДА общий для обоих каналов 1,2
		{//7,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[5][0]),
			.pt_Next = &(Element1[7][1]),
			.pt_Prev = &(Element1[7][3]),
			.pt_Up = &(Element1[1][5]),
			.pt_Low = NULL,
		},
		{//7,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[5][1]),
			.pt_Next = &(Element1[7][2]),
			.pt_Prev = &(Element1[7][0]),
			.pt_Up = &(Element1[1][5]),
			.pt_Low = NULL,
		},
		{//7,2
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[5][2]),
			.pt_Next = &(Element1[7][3]),
			.pt_Prev = &(Element1[7][1]),
			.pt_Up = &(Element1[1][5]),
			.pt_Low = NULL,
		},
		{//7,3
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[5][3]),
			.pt_Next = &(Element1[7][0]),
			.pt_Prev = &(Element1[7][2]),
			.pt_Up = &(Element1[1][5]),
			.pt_Low = NULL,
		},
		{//6,4
		},
		{//6,5
		},
		{//6,6
		},
		{//6,7
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		}
	},
	{	//8 LEVEL2 ИНВЕРТОР
		{//8,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[6][0]),
			.pt_Next = &(Element1[8][1]),
			.pt_Prev = &(Element1[8][1]),
			.pt_Up = &(Element1[1][6]),
			.pt_Low = NULL,
		},
		{//8,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[6][1]),
			.pt_Next = &(Element1[8][0]),
			.pt_Prev = &(Element1[8][0]),
			.pt_Up = &(Element1[1][6]),
			.pt_Low = NULL,
		},
		{//8,2
		},
		{//8,3
		},
		{//8,4
		},
		{//8,5
		},
		{//8,6
		},
		{//8,7
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		},
		{
		}
	},
	{	//9 LEVEL2 ПАНЕЛИ СОЛН. канал 2
		{//9,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[7][6]),
			.pt_Next = &(Element1[9][1]),
			.pt_Prev = &(Element1[9][6]),
			.pt_Up = &(Element1[1][8]),
			.pt_Low = NULL,
		},
		{//9,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[7][0]),
			.pt_Next = &(Element1[9][2]),
			.pt_Prev = &(Element1[9][0]),
			.pt_Up = &(Element1[1][8]),
			.pt_Low = NULL,
		},
		{//9,2
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[7][1]),
			.pt_Next = &(Element1[9][3]),
			.pt_Prev = &(Element1[9][1]),
			.pt_Up = &(Element1[1][8]),
			.pt_Low = NULL,
		},
		{//9,3
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[7][2]),
			.pt_Next = &(Element1[9][4]),
			.pt_Prev = &(Element1[9][2]),
			.pt_Up = &(Element1[1][8]),
			.pt_Low = NULL,
		},
		{//9,4
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[7][3]),
			.pt_Next = &(Element1[9][5]),
			.pt_Prev = &(Element1[9][3]),
			.pt_Up = &(Element1[1][8]),
			.pt_Low = NULL,
		},
		{//9,5
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[7][4]),
			.pt_Next = &(Element1[9][6]),
			.pt_Prev = &(Element1[9][4]),
			.pt_Up = &(Element1[1][8]),
			.pt_Low = NULL,
		},
		{//9,6
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[7][5]),
			.pt_Next = &(Element1[9][0]),
			.pt_Prev = &(Element1[9][5]),
			.pt_Up = &(Element1[1][8]),
			.pt_Low = NULL,
		},
		{//9,7
		},
		{//9,8
		},
		{//9,9
		},
		{//9,10
		},
		{//9,11
		},
		{//9,12
		},
		{//9,13
		},
		{//9,14
		}
	},
	{	//10 LEVEL2 РЕЛЕ
		{//10,0
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[8][0]),
			.pt_Next = &(Element1[10][1]),
			.pt_Prev = &(Element1[10][1]),
			.pt_Up = &(Element1[1][9]),
			.pt_Low = NULL,
		},
		{//10,1
			.Type = DATA_TYPE_2,
			.ppv_RAM_Data = &(RamData.Data1.pv),
			.pv_PGM_Data = &(PGM_Data_2[8][1]),
			.pt_Next = &(Element1[10][0]),
			.pt_Prev = &(Element1[10][0]),
			.pt_Up = &(Element1[1][9]),
			.pt_Low = NULL,
		},
		{//10,2
		},
		{//10,3
		},
		{//10,4
		},
		{//10,5
		},
		{//10,6
		},
		{//10,7
		},
		{//10,8
		},
		{//10,9
		},
		{//10,10
		},
		{//10,11
		},
		{//10,12
		},
		{//10,13
		},
		{//10,14
		}
	},
};

ParView_init_t	spgm_par_view_init[] PROGMEM =
{
	{
		.pst = &Element1[0][1]
	}
};

void
RunnerStartPoint(Element_t* plist)
{
	//p_List = (Element_t*)pgm_read_word(&(spgm_RunnerStartPoint[0].pst));
	//p_List2 = (Element_t*)pgm_read_word(&(spgm_RunnerStartPoint[1].pst));
	plist = (Element_t*)pgm_read_word(&(spgm_par_view_init[0].pst));
	//p_List3 = (Element_t*)pgm_read_word(&(spgm_RunnerStartPoint[2].pst));
}
/**/

Limit_t Limit[LIMITS_LENGHT][2] = 
{
	{	//0	empty
		{
			.Type = 0,
			.u.u16 = 0
		},
		{
			.Type = 0,
			.u.u16 = 0
		}
	},
	{	//1	empty
		{
			.Type = 0,
			.u.u16 = 0
		},
		{
			.Type = 0,
			.u.u16 = 0
		}
	},
	{	//2 empty
		{
			.Type = 0,
			.u.u16 = 0
		},
		{
			.Type = 0,
			.u.u16 = 0
		}
	},
	{	//3 empty
		{
			.Type = 0,
			.u.u16 = 0
		},
		{
			.Type = 0,
			.u.u16 = 0
		}
	},
	{	//4 MODBUS_REG_0
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 250
		}
	},
	{	//5 MODBUS_REG_1
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 81
		}
	},
	{	//6 MODBUS_REG_2
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 82
		}
	},
	{//7 empty
	},
	{//8 empty
	},
	{//9 empty
	},
	{//10 empty
	},
	{//11 empty
	},
	{//12 empty
	},
	{//13 empty
	},
	{//14 empty
	},
	{//15 empty
	},
	{//16 empty
	},
	{//17 empty
	},
	{//18 empty
	},
	{//19 empty
	},
	{//20 empty
	},
	{//21 empty
	},
	{//22 empty
	},
	{//23 MODBUS_SOLBAT_CH1_U_MPP
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 1200
		}
	},
	{//24 MODBUS_SOLBAT_CH1_U_XX
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 1600
		}
	},
	{//25 MODBUS_SOLBAT_CH1_NUM_SERIAL
		{
			.Type = LIMIT_U16,
			.u.u16 = 1
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 4
		}
	},
	{//26 MODBUS_SOLBAT_CH1_NUM_PARAL
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		}
	},
	{//27 MODBUS_SOLBAT_CH1_I_KZ
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 100
		}
	},
	{//28 MODBUS_SOLBAT_CH1_I_MPP
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 100
		}
	},
	{//29 MODBUS_SOLBAT_CH1_MODE

	},
	{//30 MODBUS_REG_DEBUG_TEMP0
	},
	{//31 MODBUS_REG_DEBUG_TEMP1
	},
	{//32 MODBUS_REG_DEBUG_TEMP2
	},
	{//33 MODBUS_INVERTER_UOUT_SET
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 250
		}
	},
	{//34 MODBUS_REG_DEBUG_TEMP3
	},
	{//35 MODBUS_RELAY_P2
	},
	{//36 MODBUS_RELAY_P3
	},
	{//37 MODBUS_SOLBAT_CH2_U_MPP
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 1200
		}
	},
	{//38 MODBUS_SOLBAT_CH2_U_XX
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 1600
		}
	},
	{//39 MODBUS_SOLBAT_CH2_NUM_SERIAL
		{
			.Type = LIMIT_U16,
			.u.u16 = 1
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 4
		}
	},
	{//40 MODBUS_SOLBAT_CH2_NUM_PARAL
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		}
	},
	{//41 MODBUS_SOLBAT_CH2_I_KZ
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 100
		}
	},
	{//42 MODBUS_SOLBAT_CH2_I_MPP
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 100
		}
	},
	{//43 MODBUS_SOLBAT_CH2_MODE  empty
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		},
		{
			.Type = LIMIT_U16,
			.u.u16 = 0
		}
	},
};


/*
	Переход на след.элемент по сетке меню
*/
void
LList_Next( RamList_t* ram_list )
{
	void**	ppv;
	Element_t* elem = (Element_t*)pgm_read_word(&(ram_list->p_now->pList->pt_Next));
	
	if (elem == NULL)
		return;

	ram_list->p_now->pList = elem;
	ppv = (void**)pgm_read_word(&(ram_list->p_now->pList->ppv_RAM_Data));
	if (*ppv != NULL)
		LList_MemFree(ram_list, ppv);
	LList_MemAlloc(ram_list, ram_list->p_now->pList, ppv);
	
	/*
	if (ram_list->p_now == ram_list->p_ram_main)
	{
		elem = (Element_t*)pgm_read_word(&(ram_list->p_ram_main->pList->pt_Next));
	}
	else if (ram_list->p_now == ram_list->p_ram_parview)
	{
		elem = (Element_t*)pgm_read_word(&(ram_list->p_ram_parview->pList->pt_Next));
	}
	*/
	
	
	/*
	 = (Element_t*)pgm_read_word(&(ram_list->p_ram_main->pList->pt_Next));
	Element_t* elem2 = (Element_t*)pgm_read_word(&(ram_list->p_ram_parview->pList->pt_Next));
	
	if (ram_list->p_now == ram_list->p_ram_main)
	{
		if (elem1 != NULL) {
			ram_list->p_ram_main->pList = elem1;
			ppv = (void**)pgm_read_word(&(ram_list->p_ram_main->pList->ppv_RAM_Data));
			if (*ppv != NULL)
				LList_MemFree(ram_list, ppv);
			LList_MemAlloc(ram_list, ram_list->p_ram_main->pList, ppv);
		}
	}
	else if (ram_list->p_now == ram_list->p_ram_parview)
	{
		if (elem2 != NULL)
		{
			if ( pgm_read_byte(&(elem2->Type)) == DATA_TYPE_MAIN_3_2)
			{
				ram_list->p_ram_parview->pList = elem2;
				//ppv = &(RAM_Data2.pv_Data);	//забыл уже что такое
				ppv = (void**)pgm_read_word(&(ram_list->p_ram_parview->pList->ppv_RAM_Data));
				if (*ppv != NULL)
					LList_MemFree(ram_list, ppv);
					//Memory_Free(ppv);
				//*ppv = malloc(sizeof(Data_Main_Type_3_2_t));
				LList_MemAlloc(ram_list, ram_list->p_ram_parview->pList, ppv);

				//Fill_PGM_to_RAM_Type_12(ram_list->pram_parview->pList, ppv, 0);
			}
		}
	}
	*/
}


/*
	Переход на пред.элемент по сетке меню
*/
void
LList_Prev( RamList_t* ram_list )
{
	void**	ppv;
	Element_t* elem = (Element_t*)pgm_read_word(&(ram_list->p_now->pList->pt_Prev));
	
	if (elem != NULL)
	{
		ram_list->p_now->pList = elem;
		ppv = (void**)pgm_read_word(&(ram_list->p_now->pList->ppv_RAM_Data));
		if (*ppv != NULL)
			LList_MemFree(ram_list, ppv);
		LList_MemAlloc(ram_list, ram_list->p_now->pList, ppv);
	}
}



/*
	Переход вверх по сетке меню
*/
void
LList_Up( RamList_t* ram_list )
{
	void**	ppv;
	Element_t* elem;
	
	elem = (Element_t*)pgm_read_word(&(ram_list->p_now->pList->pt_Up));
	
	if (elem != NULL)
	{
		ram_list->p_now->pList = elem;
		ppv = (void**)pgm_read_word(&(ram_list->p_now->pList->ppv_RAM_Data));
		if (*ppv != NULL){
			//PORTD ^= 1<<6;
			LList_MemFree(ram_list, ppv);
		}
		LList_MemAlloc(ram_list, ram_list->p_now->pList, ppv);
		ram_list->p_now->Level -= 1;
	}
}



/*
	Переход вниз по сетке меню
*/
void
LList_Low( RamList_t* ram_list )
{
	void**	ppv;
	Element_t* elem = (Element_t*)pgm_read_word(&(ram_list->p_now->pList->pt_Low));
	
	if (elem != NULL)
	{
		ram_list->p_now->pList = elem;
		ppv = (void**)pgm_read_word(&(ram_list->p_now->pList->ppv_RAM_Data));
		if (*ppv != NULL)
			LList_MemFree(ram_list, ppv);
		LList_MemAlloc(ram_list, ram_list->p_now->pList, ppv);
		ram_list->p_now->Level += 1;
	}
}

void
Navigation_Jump( RamList_t* ram_list, uint8_t num )
{
	if (num > 4) return;
	
	void**	ppv;
	Element_t* elem = (Element_t*)pgm_read_word(&(Jumps[num].pst));
	//Element_t* elem = (Element_t*)pgm_read_word(&(ram_list->p_now->pList));
	
	//PORTD ^= 1<<1;
	
	if (elem != NULL)
	{
		ram_list->p_now->pList = elem;
		ppv = (void**)pgm_read_word(&(ram_list->p_now->pList->ppv_RAM_Data));
		if (*ppv != NULL)
			LList_MemFree(ram_list, ppv);
		LList_MemAlloc(ram_list, ram_list->p_now->pList, ppv);
		//RAM_Type = RAM_MainRunner;	
	}
	
}


void
Jump_RunnerParamView(RamList_t* ram_list)
{
	void**	ppv;
	
	
	if ( pgm_read_byte(&(ram_list->p_ram_parview->pList->Type)) == DATA_TYPE_MAIN_3_2)
	{
		ram_list->p_now = ram_list->p_ram_parview;
		
		//ppv = ram_list->p_now->Data1.pv
		ppv = (void**)pgm_read_word(&(ram_list->p_now->pList->ppv_RAM_Data));
		if (*ppv != NULL)
			LList_MemFree(ram_list, ppv);
		LList_MemAlloc(ram_list, ram_list->p_now->pList, ppv);
	}
}


void
Menu_Step(CurrentMode_t mode)
{
	switch (mode)
	{
		case (CM_UNK):
			Navigation_Jump(p_ram_list, 0);
			break;
			
		case (STOP):
			Navigation_Jump(p_ram_list, 1);
			break;
			
		case (RUN):
			Navigation_Jump(p_ram_list, 2);
			break;
				
		case (FAULT):
			Navigation_Jump(p_ram_list, 3);
			break;
			
		case (NO485):
			Navigation_Jump(p_ram_list, 4);
			break;
			
		default:
			break;
	}
}


/*
	???
*/
void
LList_ElementFill( RamList_t* ram_list, Element_t* pin, void** ppv, uint8_t type )
{
	switch (type)
	{
		case DATA_TYPE_1:
		{
			Fill_PGM_to_RAM_Type_1(ram_list, pin, ppv);
			break;
		}
		
		case DATA_TYPE_2:
		{
			
			Fill_PGM_to_RAM_Type_2(ram_list, pin, ppv);
			break;
		}
		
		case DATA_TYPE_MAIN_3_2:
		{
			
			Fill_PGM_to_RAM_Type_Main_3_2(ram_list, pin, ppv);
			break;
		}
			
		default:
			break;
	}
}



/*
	???
*/
void
LList_MemAlloc( RamList_t* ram_list, Element_t* pin, void** ppv )
{
	uint16_t type = pgm_read_byte(&(pin->Type));
	
	
	
	switch (type)
	{

		case DATA_TYPE_1:
		{
			
			*ppv = malloc(sizeof(DataType_1_t));
			LList_ElementFill(ram_list, pin, ppv, type);
		}
		break;
		
		case DATA_TYPE_2:
		{
			*ppv = malloc(sizeof(DataType_2_t));
			LList_ElementFill(ram_list, pin, ppv, type);
			
		}
		break;
		
		case DATA_TYPE_MAIN_3_2:
		{
			*ppv = malloc(sizeof(DataType_Main_3_2_t));
			LList_ElementFill(ram_list, pin, ppv, type);
			
		}
		break;
			
		default:
			break;
	}
}


/*
	???
*/
void
LList_MemFree( RamList_t* ram_list, void** ppv)
{
	free(*ppv);
	*ppv = NULL;
	ram_list->p_now->Data1.Type = DATA_TYPE_EMPTY;
}


/*
	???
*/
void
LList_Cancel( RamList_t* ram_list )
{
	ram_list->p_now->UserEdit = false;
	Table.Unsort.CARRIAGE_TYPE_Date_1_t = 0;
	Table.Unsort.CARRIAGE_TYPE_Time_1_t = 0;
	Table.Unsort.CARRIAGE_INV_DIGITAL_INPUT = 0;
}


/*
	???
*/
void
LList_Edit( RamList_t* ram_list )
{
	ram_list->p_now->UserEdit = true;
	
	switch (ram_list->p_now->pData->Type)
	{
		case (DATA_TYPE_2):
		{
			if (((DataType_2_t*)ram_list->p_now->pData->pv)->Opt == 0)
			{
				
				switch (((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type)
				{
					case (TYPE_Date_1_t):
					{
						if (Table.Unsort.CARRIAGE_TYPE_Date_1_t >= 3)
						{
							Table.Unsort.CARRIAGE_TYPE_Date_1_t = 1;
						}
						else
						{
							if (Table.Unsort.CARRIAGE_TYPE_Date_1_t == 0)
							{
								ram_list->p_now->Msg.stDateTime.Year = (*(DateTime_t*)(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.pvData)).Year;
								ram_list->p_now->Msg.stDateTime.Month = (*(DateTime_t*)(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.pvData)).Month;
								ram_list->p_now->Msg.stDateTime.Day = (*(DateTime_t*)(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.pvData)).Day;
								
								ram_list->p_now->Msg.Tx.Page = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Page;
								ram_list->p_now->Msg.Tx.Reg = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Reg;
								ram_list->p_now->Msg.Tx.Bit = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Bit;
							}
							Table.Unsort.CARRIAGE_TYPE_Date_1_t++;
						}
						// Выход
						break;
					}
					
					case (TYPE_Time_1_t):
					{
						if (Table.Unsort.CARRIAGE_TYPE_Time_1_t >= 3)
						{
							Table.Unsort.CARRIAGE_TYPE_Time_1_t = 1;
						}
						else
						{
							if (Table.Unsort.CARRIAGE_TYPE_Time_1_t == 0)
							{
								ram_list->p_now->Msg.stDateTime.Hour = (*(DateTime_t*)(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.pvData)).Hour;
								ram_list->p_now->Msg.stDateTime.Minute = (*(DateTime_t*)(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.pvData)).Minute;
								ram_list->p_now->Msg.stDateTime.Second = (*(DateTime_t*)(((DataType_2_t*)ram_list->p_now->pData->pv)->Value.pvData)).Second;
								ram_list->p_now->Msg.Tx.Page = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Page;
								ram_list->p_now->Msg.Tx.Reg = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Reg;
								ram_list->p_now->Msg.Tx.Bit = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Bit;
							}
							Table.Unsort.CARRIAGE_TYPE_Time_1_t++;
						}
						// Выход
						break;
					}
					
					case (U16):
					case (U16nP):
					case (BOOL):
					{
						ram_list->p_now->Msg.st.Type = ((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type;
						ram_list->p_now->Msg.st.ret.u16 = (uint16_t)*((uint16_t*)((DataType_2_t*)(ram_list->p_now->pData->pv))->Value.pvData);
						ram_list->p_now->Msg.Tx.Page = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Page;
						ram_list->p_now->Msg.Tx.Reg = ((DataType_2_t*)ram_list->p_now->pData->pv)->Tx.Reg;
						// Выход
						break;
					}
					
					
					default:
					break;
				}
			}
			else if (((DataType_2_t*)ram_list->p_now->pData->pv)->Opt == 1)
			{
			}	

			
			break;
		}
		
		default:
			break;
	}
}

void
LList_CopyMessageData_U16( RamList_t* ram_list )
{
	//ram_list->p_now->Msg.st.Type = ((DataType_Main_3_2_t*)ram_list->p_now->pData->pv)->Value_0.Type;
	//ram_list->p_now->Msg.st.ret.u16 = (uint16_t)*((uint16_t*)((DataType_Main_3_2_t*)(ram_list->p_now->pData->pv))->Value.pvData);
	ram_list->p_now->Msg.Tx.Page = ((DataType_Main_3_2_t*)ram_list->p_now->pData->pv)->Tx.Page;
	ram_list->p_now->Msg.Tx.Reg = ((DataType_Main_3_2_t*)ram_list->p_now->pData->pv)->Tx.Reg;
}

void
LList_Start( RamList_t* ram_list )
{
	//ram_list->p_now->Msg.Tx.Page = MODBUS_PAGE_0;
	//ram_list->p_now->Msg.Tx.Reg = MODBUS_STARTSTOP;
	//ram_list->p_now->Msg.Tx.Bit = 0;
	//ram_list->p_now->Msg.st.ret.u16 = (uint16_t)RUN;
	if (ram_list->p_now->pData->Type == DATA_TYPE_MAIN_3_2)
	{
		LList_CopyMessageData_U16(ram_list);
		ram_list->p_now->Msg.st.ret.u16 = (uint16_t)RUN;
		Next_Send_Function = F_X10;
	}
}

void
LList_Stop( RamList_t* ram_list )
{
	if (ram_list->p_now->pData->Type == DATA_TYPE_MAIN_3_2)
	{
		ram_list->p_now->Msg.st.ret.u16 = (uint16_t)STOP;
		Next_Send_Function = F_X10;
	}
	//ram_list->p_now->Msg.Tx.Page = MODBUS_PAGE_0;
	//ram_list->p_now->Msg.Tx.Reg = MODBUS_STARTSTOP;
	//ram_list->p_now->Msg.Tx.Bit = 0;
	//ram_list->p_now->Msg.st.ret.u16 = (uint16_t)STOP;
	
}

void
LList_PlusParam( RamList_t* ram_list, ParamIncrementSpeed_t speed, uint8_t speed_divider )
{
	Retval_t ret_Init;
	Retval_t ret_Ret;
	//uint16_t Tmp = 0;
	
	switch (ram_list->p_now->pData->Type)
	{
		case (DATA_TYPE_2):
		{
			if (((DataType_2_t*)ram_list->p_now->pData->pv)->Opt == 0)
			{
				
				switch (((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type)
				{
					case (TYPE_Date_1_t):
					{
						switch (Table.Unsort.CARRIAGE_TYPE_Date_1_t)
						{
							case (1):
							{
								//(DateTime_t*)(((Data_Type_3_t*)RAM_Data.pv_Data)->Value.pv)
								if (ram_list->p_now->Msg.stDateTime.Day < 31)
									ram_list->p_now->Msg.stDateTime.Day++;
								else
									ram_list->p_now->Msg.stDateTime.Day = 1;
								break;
							}
							
							case (2):
							{
								if (ram_list->p_now->Msg.stDateTime.Month < 12)
									ram_list->p_now->Msg.stDateTime.Month++;
								else
									ram_list->p_now->Msg.stDateTime.Month = 1;
								break;
							}
							
							case (3):
							{
								if (ram_list->p_now->Msg.stDateTime.Year < 99)	//двойка добавляется драйвером
									ram_list->p_now->Msg.stDateTime.Year++;
								else
									ram_list->p_now->Msg.stDateTime.Year = 0;
								break;
							}
						}
						//Выход
						break;
					}
					
					case (TYPE_Time_1_t):
					{
						switch (Table.Unsort.CARRIAGE_TYPE_Time_1_t)
						{
							case (1):
							{
								if (ram_list->p_now->Msg.stDateTime.Hour < 23)
									ram_list->p_now->Msg.stDateTime.Hour++;
								else
									ram_list->p_now->Msg.stDateTime.Hour = 0;
								break;
							}
							
							case (2):
							{
								if (ram_list->p_now->Msg.stDateTime.Minute < 59)
									ram_list->p_now->Msg.stDateTime.Minute++;
								else
									ram_list->p_now->Msg.stDateTime.Minute = 0;
								break;
							}
							
							case (3):
							{
								if (ram_list->p_now->Msg.stDateTime.Second < 59)
									ram_list->p_now->Msg.stDateTime.Second++;
								else
									ram_list->p_now->Msg.stDateTime.Second = 0;
								break;
							}
						}
						//Выход
						break;
					}
					
					case (U16):
					case (U16nP):
					{
						ram_list->p_now->Msg.st.ret.u16 = (uint16_t)i16_ModifyVar(ram_list, ram_list->p_now->Msg.st.ret.u16, MODIFYVAR_PLUS, speed);
						//Выход
						break;
					}
					
					case (BOOL):
					{
						if (speed_divider == 0)
						{
							ret_Init = ram_list->p_now->Msg.st.ret;
							ret_Ret = Shed_Types_v2( ret_Init, ram_list->p_now->Msg.st.Type, true );
							//Msg.Value.ret = ret_Ret;
							ram_list->p_now->Msg.st.ret = ret_Ret;
						}
						//Выход
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
LList_MinusParam( RamList_t* ram_list, ParamIncrementSpeed_t speed, uint8_t speed_divider)
{
	Retval_t ret_Init;
	Retval_t ret_Ret;
	
	switch (ram_list->p_now->pData->Type)
	{
		case (DATA_TYPE_2):
		{
			if (((DataType_2_t*)ram_list->p_now->pData->pv)->Opt == 0)
			{
				switch (((DataType_2_t*)ram_list->p_now->pData->pv)->Value.Type)
				{
					case (U16):
					case (U16nP):
					{
						ram_list->p_now->Msg.st.ret.u16 = (uint16_t)i16_ModifyVar(ram_list, ram_list->p_now->Msg.st.ret.u16, MODIFYVAR_MINUS, speed);
						//Выход
						break;
					}
					
					case (BOOL):
					{
						if (speed_divider == 0)
						{
							ret_Init = ram_list->p_now->Msg.st.ret;
							ret_Ret = Shed_Types_v2( ret_Init, ram_list->p_now->Msg.st.Type, false );
							//Msg.Value.ret = ret_Ret;
							ram_list->p_now->Msg.st.ret = ret_Ret;
						}
						//Выход
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

/*
	retval:
		Retval_t
	
	params:
		initval 	- находящееся в памяти число типа Retval_t
		type 		- измененяемое значение
		direction	- пользователь нажал вверх или вниз
		
	comment:
		бегунок по нечисловым параметрам. инкрементирует или декрементирует находящееся в памяти число типа Retval_t соглано направлению перемещения с
		ограничением диапазона согласно типу
*/
Retval_t
Shed_Types_v2(Retval_t initval, ValueType_t type, bool direction)
{
	uint8_t		u8_Lenght = 0;
	Retval_t 	val;
	
	switch (type)
	{
		case (BOOL):
//		case (TYPE_Parameter_t):
//		case (TYPE_AnalogInput_Dim_t):
//		case (TYPE_Direction_t):
//		case (TYPE_CallbackMode_t):
//		case (TYPE_Channel_t):
//		case (TYPE_Chopper_t):
//		case (TYPE_ExtSerial_Stop_t):
//		case (TYPE_DefaultSetting_Type_t):
			u8_Lenght = 2;
			break;

		default:
			break;
	}
	
	if (u8_Lenght != 0)
	{
		if (u8_Lenght == 1)
			val.u16 = initval.u16;					//добавленное от 17-07-2018
		else
		{
			if (direction)
			{
				if (initval.u16 >= (u8_Lenght-1))
					val.u16 = (bool)0;
				else
					val.u16 = (bool)(initval.u16 + 1);
			}
			else
			{
				if (initval.u16 <= 0)
					val.u16 = (bool)(u8_Lenght-1);
				else
					val.u16 = (bool)(initval.u16 - 1);
			}
		}
		
		return val;
	}
	
	val.u16 = 0;
	return val;
}
/**/

bool
b_IsReadyMode(void)
{
	return true;
}

bool
b_IsModeEqualsParview(RamList_t* ram_list)
{
	if (ram_list->p_now == ram_list->p_ram_parview)
		return true;
	
	return false;
}

bool
b_IsScreen0Page(RamList_t* ram_list)
{
	if ((ram_list->p_now == ram_list->p_ram_main) & (ram_list->p_now->pData->Type == DATA_TYPE_1)){
		
		if (!strcmp((const char*)sram_0_2_LABEL, (const char*)((DataType_1_t*)ram_list->p_now->pData->pv)->Label_Up)){
			return true;
		}
	}
	return false;
	
}


int16_t
i16_ModifyVar( RamList_t* ram_list, int16_t modifyvar, enum ModifyVar type, ParamIncrementSpeed_t speed)
{
	int16_t 	i16_RetVal = 0;
	uint16_t	u16_LimitVal = 0;
	int16_t 	i16_Tmp = 0;
	int32_t 	i32_Tmp = 0;
	
	int16_t 	i16_modifiedvar = modifyvar;	//значение, если оно изначально было за пределами. Выше верхнего или ниже нижнего
	uint16_t	u16_LimitVal_Min = 0;
	uint16_t	u16_LimitVal_Max = 0;
	
	/* случай заранее неправильного значения в памяти ПЧ. Выход без лишнего инкремента или декремента*/
	(ram_list->p_now->Msg.st.Limit.Max.Type == LIMIT_U16) ?
		(u16_LimitVal_Max =		(uint16_t)	ram_list->p_now->Msg.st.Limit.Max.u.u16) :
		(u16_LimitVal_Max = 	*(uint16_t*)ram_list->p_now->Msg.st.Limit.Max.u.pu16) ;
		
	(ram_list->p_now->Msg.st.Limit.Min.Type == LIMIT_U16) ?
		(u16_LimitVal_Min =		(uint16_t)	ram_list->p_now->Msg.st.Limit.Min.u.u16) :
		(u16_LimitVal_Min = 	*(uint16_t*)ram_list->p_now->Msg.st.Limit.Min.u.pu16) ;
		
	if (i16_modifiedvar < (int16_t)u16_LimitVal_Min)
	{
		
		i16_modifiedvar = (int16_t)u16_LimitVal_Min;
		return i16_modifiedvar;
	}
	
	if (i16_modifiedvar > (int16_t)u16_LimitVal_Max)
	{
		i16_modifiedvar = (int16_t)u16_LimitVal_Max;
		return i16_modifiedvar;
	}
	
	switch (type)
	{
		case (MODIFYVAR_PLUS):
		{
			(ram_list->p_now->Msg.st.Limit.Max.Type == LIMIT_U16) ?
				(u16_LimitVal =		(uint16_t)	ram_list->p_now->Msg.st.Limit.Max.u.u16) :
				(u16_LimitVal = 	*(uint16_t*)ram_list->p_now->Msg.st.Limit.Max.u.pu16) ;
			
			if ((modifyvar + (int16_t)speed) < (int16_t)u16_LimitVal)
			{
				i16_RetVal = modifyvar + (int16_t)speed;
				
				//округление
				switch (speed)
				{
					case (INCREMENT_1):
					{
						//no need to do anything
						break;
					}
					case (INCREMENT_5):
						i16_Tmp = i16_RetVal / 5;
						i16_RetVal = i16_Tmp * 5;
						break;
					case (INCREMENT_10):
						i16_Tmp = i16_RetVal / 10;
						i16_RetVal = i16_Tmp * 10;
						break;
					case (INCREMENT_50):
						i32_Tmp = (int32_t)i16_RetVal;
						i32_Tmp /= 50;
						i32_Tmp *= 50;
						i16_RetVal = (int16_t)(i32_Tmp & 0x0000ffff);
						
						//i16_Tmp = i16_RetVal / 50;
						//i16_RetVal = i16_Tmp * 50;
						break;
					case (INCREMENT_100):
						i32_Tmp = (int32_t)i16_RetVal;
						i32_Tmp /= 100;
						i32_Tmp *= 100;
						i16_RetVal = (int16_t)(i32_Tmp & 0x0000ffff);
						
						//i16_Tmp = i16_RetVal / 100;
						//i16_RetVal = i16_Tmp * 100;
						break;
					default:
						break;
				}
			}
			else
			{
				i16_RetVal = (int16_t)u16_LimitVal;
			}
			
			break;
		}
		case (MODIFYVAR_MINUS):
		{
			(ram_list->p_now->Msg.st.Limit.Min.Type == LIMIT_U16) ?
				(u16_LimitVal =		(uint16_t)	ram_list->p_now->Msg.st.Limit.Min.u.u16) :
				(u16_LimitVal = 	*(uint16_t*)ram_list->p_now->Msg.st.Limit.Min.u.pu16) ;
				
			if ((modifyvar - (int16_t)speed) > (int16_t)u16_LimitVal)
			{
				i16_RetVal = modifyvar - (int16_t)speed;
				
				switch (speed)
				{
					case (INCREMENT_1):
					{
						//no need to do anything
						break;
					}
					case (INCREMENT_5):
						i16_Tmp = i16_RetVal / 5;
						i16_Tmp *= 5;
						
						if (i16_Tmp - i16_RetVal == 5)
							i16_RetVal += 0;
						else
							i16_RetVal = i16_Tmp;
						break;
						
					case (INCREMENT_10):
						i16_Tmp = i16_RetVal / 10;
						i16_Tmp *= 10;
						
						if (i16_Tmp - i16_RetVal == 10)
							i16_RetVal += 0;
						else
							i16_RetVal = i16_Tmp;
						break;
						
					case (INCREMENT_50):
						//i16_Tmp = i16_RetVal / 10;
						//i16_Tmp *= 10;
						
						i32_Tmp = (int32_t)i16_RetVal;
						i32_Tmp /= 50;
						i32_Tmp *= 50;
						
						
						
						if (((int16_t)(i32_Tmp & 0x0000ffff)) - i16_RetVal == 50)
							i16_RetVal += 0;
						else
							i16_RetVal = ((int16_t)(i32_Tmp & 0x0000ffff));
						break;
						
					case (INCREMENT_100):
						//i16_Tmp = i16_RetVal / 10;
						//i16_Tmp *= 10;
						
						i32_Tmp = (int32_t)i16_RetVal;
						i32_Tmp /= 100;
						i32_Tmp *= 100;
						
						if (((int16_t)(i32_Tmp & 0x0000ffff)) - i16_RetVal == 100)
							i16_RetVal += 0;
						else
							i16_RetVal = ((int16_t)(i32_Tmp & 0x0000ffff));
						break;
						
					default:
						break;
				}
			}
			else
			{
				i16_RetVal = (int16_t)u16_LimitVal;
			}

			break;
		}
	}
					
	return i16_RetVal;
}



void
v_GetLimits(uint16_t id, LimitMinMax_t * container)
{
	if (id >= LIMITS_LENGHT)
		return;
	
	container->Min.Type = ((Limit_t)Limit[id][0]).Type;
	(container->Min.Type == LIMIT_U16) ?
		(container->Min.u.u16 =		(uint16_t)	(((Limit_t)Limit[id][0]).u.u16)) :
		(container->Min.u.pu16 = 	(uint16_t*)	(((Limit_t)Limit[id][0]).u.pu16)) ;
	
	
	container->Max.Type = ((Limit_t)Limit[id][1]).Type;
	(container->Max.Type == LIMIT_U16) ?
		(container->Max.u.u16 =		(uint16_t)	(((Limit_t)Limit[id][1]).u.u16)) :
		(container->Max.u.pu16 = 	(uint16_t*)	(((Limit_t)Limit[id][1]).u.pu16)) ;
}



void
empty(void)
{
	
}

