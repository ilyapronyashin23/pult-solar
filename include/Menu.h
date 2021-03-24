#ifndef _MENU_H_
#define _MENU_H_


#include "libc/stdint.h"
#include "Types.h"
#include "DataConvert.h"

// ARRAY[X][Y]
#define MAIN_MENU_DIM_X 11
#define MAIN_MENU_DIM_Y 15

#define DATA1_MENU_DIM 12

#define DATA2_MENU_DIM_X 9
#define DATA2_MENU_DIM_Y 15

#define DATAMAIN_MENU_DIM 5

/*
	Ячейка связного списка
*/
struct	st_Element;
typedef	struct st_Element Element_t;
struct st_Element
{
	uint16_t	Type;
	void**		ppv_RAM_Data;
	void*		pv_PGM_Data;
	Element_t*	pt_Next;
	Element_t*	pt_Prev;
	Element_t*	pt_Up;
	Element_t*	pt_Low;
};

#define LIMITS_LENGHT 44


/*
	Список всех типов
*/
typedef enum
{
	DATA_TYPE_EMPTY = 0,	//0		//не используется
	DATA_TYPE_0,			//0		//не используется
	DATA_TYPE_1,			//1		//«Установка параметров» и т.д.
	DATA_TYPE_2,			//2		//«Режим пуска» и т.д.
	DATA_TYPE_3,			//3		//«Установка Fуст» или « Введите пароль» и т.д.
	DATA_TYPE_4,			//4		//Таймер
	DATA_TYPE_5,			//5		//Авария
	DATA_TYPE_6,			//6		//не используется
	DATA_TYPE_7,			//7		//не используется
	DATA_TYPE_MAIN_0,		//8		//«Инициализация»
	DATA_TYPE_MAIN_3_0,		//9		//«Заряд» и «Ждущей режим»
	DATA_TYPE_MAIN_3_1,		//10	//Два параметра в ходе работы
	DATA_TYPE_MAIN_4,		//11	//Текущая Авария на экране
	DATA_TYPE_MAIN_3_2,		//12	//Пролистываемый список параметров
}
DataType_t;



/*
	???
*/
typedef struct
{
	void* pv;
	DataType_t Type;
}
RamData_t;



/*
	???
*/
typedef enum
{
	LEVEL_UNK = 0,
	LEVEL0,
	LEVEL1,
	LEVEL2,
	LEVEL3
}
MenuLevel_t;

typedef struct {
	Element_t*	pst;
} ParView_init_t;

typedef enum{
	RAM_MAIN,
	RAM_PARVIEW
} RamType_t;

/*
	???
*/
typedef struct
{
	Element_t* pList;
	//Element_t* pList_parview;
	MenuLevel_t Level;
	RamData_t* pData;
	RamData_t Data1;
	bool UserEdit;
	TxMsg_t Msg;
	bool Blank_Menu;
}
RamDataContainer_t;

typedef struct{
	RamType_t type;
	RamDataContainer_t* p_now;
	RamDataContainer_t* p_ram_main;
	RamDataContainer_t* p_ram_parview;
} 
RamList_t;

typedef enum
{
	INCREMENT_1 = 1,
	INCREMENT_5 = 5,
	INCREMENT_10 = 10,
	INCREMENT_50 = 50,
	INCREMENT_100 = 100
}
ParamIncrementSpeed_t;

/*
typedef enum
{
	RUNNER_MAIN,
	RUNNER_PARVIEW
}
ScreenRunnerType_t;
*/





void LList_MemFree( RamList_t* ram_list, void** ppv );
void LList_ElementFill( RamList_t* ram_list, Element_t* pin, void** ppv, uint8_t type );
void LList_MemAlloc( RamList_t* ram_list, Element_t* pin, void** ppv );

void LList_Next( RamList_t* ram_list );
void LList_Prev( RamList_t* ram_list );
void LList_Up( RamList_t* ram_list );
void LList_Low( RamList_t* ram_list );

void LList_Cancel( RamList_t* ram_list );
void LList_Edit( RamList_t* ram_list );
void LList_Start( RamList_t* ram_list );
void LList_Stop( RamList_t* ram_list );

void LList_PlusParam( RamList_t* ram_list, ParamIncrementSpeed_t speed, uint8_t speed_divider );
void LList_MinusParam( RamList_t* ram_list, ParamIncrementSpeed_t speed, uint8_t speed_divider );
int16_t i16_ModifyVar( RamList_t* ram_list, int16_t modifyvar, enum ModifyVar type, ParamIncrementSpeed_t speed );
void v_GetLimits(uint16_t id, LimitMinMax_t* container);

void Navigation_Jump( RamList_t* ram_list, uint8_t num );
void Menu_Step(CurrentMode_t mode);
Retval_t Shed_Types_v2(Retval_t initval, ValueType_t type, bool direction);
void RunnerStartPoint(Element_t* plist);
bool b_IsReadyMode(void);
void Jump_RunnerParamView(RamList_t* ram_list);
bool b_IsModeEqualsParview(RamList_t* ram_list);
bool b_IsScreen0Page(RamList_t* ram_list);

void LList_CopyMessageData_U16( RamList_t* ram_list );

#endif
