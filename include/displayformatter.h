#ifndef _DISPLAYFORMATTTER_H_
#define _DISPLAYFORMATTTER_H_

#include "Menu.h"
#include "weh1602_driver.h"
#include "DataConvert.h"

#define LEVEL1_STRING_LENGHT 16
#define PARAMETER_BLINKING	5
#define PARAMETER_BLINKDIV	(uint8_t)1
#define MAIN_STRING_LENGHT 16







/*
	???
*/
typedef	enum
{
	UNITS_NULL = 0,
	UNITS_TIME,
	UNITS_FREQ,
	UNITS_AMPER,
	UNITS_VOLT,
	UNITS_TEMP,
	UNITS_WATT,
	UNITS_KWATT,
	UNITS_PERCENT,
	UNITS_CAP_Ah,
}
UnitName_t;

typedef enum
{
	MPP_DIS = 0,
	MPP_NORM,
	MPP_STAB,
	MPP_KZ
} MPP_t;

typedef enum
{
	BAT_LEAD_ACID = 1,
	BAT_GEL_AGM,
	BAT_LIION_37,
	BAT_LIION_39
} BatType_t;


/*
	???
*/
typedef struct
{
	void* pvData;
	ValueType_t	Type;
	UnitName_t Units;
}
Value_t;





/*
	Контейнер с содержимым для элемента с типом DATA_TYPE_1
*/
typedef	struct
{
	char Label_Up[BUF_LENGHT];
	char Label_Low[BUF_LENGHT];
	//Flags_t et_Flags;
}
DataType_1_t;



/*
	Контейнер с содержимым для элемента с типом DATA_TYPE_2
*/
typedef	struct
{
	char Label[BUF_LENGHT];
	char ParamLabel[BUF_LENGHT];
	Value_t Value;
	TxData_t Tx;
	uint8_t Opt;
	uint16_t Flag;
	//UnitName_t Units;
	//Flags_t et_Flags;
}
DataType_2_t;

/*
	Контейнер с содержимым для элемента с типом DATA_TYPE_MAIN_3_2
*/
typedef	struct
{
	char ParamLabel_0[BUF_LENGHT];
	char ParamLabel_1[BUF_LENGHT];
	Value_t Value_0;
	Value_t Value_1;
	TxData_t Tx;
	uint8_t Opt;
	uint16_t Flag;
	//UnitName_t Units;
	//Flags_t et_Flags;
}
DataType_Main_3_2_t;



void Refresh( Element_t* pin );

void Update_Screen(RamList_t* ram_list);

void LCDSend_MainScreen( RamDataContainer_t* ramdata );
void LCDSend_1( RamDataContainer_t* ramdata );
void LCDSend_2( RamDataContainer_t* ramdata );
void v_LCDStatus( RamDataContainer_t* ramdata );

void GetCenteredString(char* instr, char* dist);
uint8_t GetCenteredValue(uint8_t UnusedArea);

void Fill_PGM_to_RAM_Type_1( RamList_t* ram_list, Element_t* pin, void** ppv );
void Fill_PGM_to_RAM_Type_2( RamList_t* ram_list, Element_t* pin, void** ppv );
void Fill_PGM_to_RAM_Type_Main_3_2( RamList_t* ram_list, Element_t* pin, void** ppv );

void VST( RamDataContainer_t* ramdata, char* pbuf, uint8_t num_of_value);
void Round(uint16_t in, uint16_t* out1, uint16_t* out2);

void Parse_UnitName(UnitName_t code, char* pbuf);
void PARSE_TYPE_Date_t(DateTime_t* code, uint8_t mode, char* pbuf);
void PARSE_TYPE_Time_t(DateTime_t* code, uint8_t mode, char* pbuf);
void PARSE_TYPE_ICHARGE_MODE(uint16_t code, char* pbuf);

void Main_Printf( RamDataContainer_t* ramdata );
void PARSE_TYPE_bool(uint16_t code, char* pbuf);

bool RoundS16(int16_t in, uint16_t* out1, uint16_t* out2);
void PARSE_TYPE_MPP(uint16_t code, char* pbuf);

#endif
