#ifndef _DATA_H_
#define _DATA_H_

#include "stdint.h"
#include "DisplayFormatter.h"
#include "Menu.h"

typedef struct
{
	Element_t* pst;
}
TableJump_t;

/*
	???
*/
typedef struct
{
	char* p_Label_Up;
	char* p_Label_Low;
	//uint16_t u16_Flags;
}
PGM_Data_1_t;


typedef struct
{
	char* Label;
	char* ParamLabel;
	Value_t Value;
	TxData_t Tx;
	uint8_t Opt;
	uint16_t Flag;
}
PGM_Data_2_t;

typedef struct
{
	char* ParamLabel_0;
	char* ParamLabel_1;
	Value_t Value_0;
	Value_t Value_1;
	TxData_t Tx;
	uint8_t Opt;
	uint16_t Flag;
}
PGM_Data_Main_3_2_t;


#endif