#ifndef _DATACONVERT_H_
#define _DATACONVERT_H_

#include "Types.h"
#include "stdint.h"
//#include "DisplayForma"

typedef	union
{
	uint16_t u16;
	uint16_t* pu16;
	int16_t s16;
	/*
	bool				bool16;
	Pulse_t				pulse16;
	Pulse_t				pickup16;
	Direction_t			direction16;
	Mode_t				mode16;
	Breaking_t			breaking16;
	AnalogOutput_Mode_t	analogoutput16;
	CallbackMode_t		callback16;
	Channel_t			channel16;
	Chopper_t			chopper16;
	uint8_t				u8;
	int16_t				s16;
	float32_t			f32;
	Fault_Label_t		fault16;
	Fault_Param_Label_t	paramfault16;
	
	*/
}
Retval_t;

/*
	???
*/
typedef enum
{
	EMPTY = 0,
	U8 = 1,
	S16,
	U16,
	BOOL,
	TYPE_Date_1_t, //DD-MM-YYYY
	TYPE_Date_2_t, //DD-MM-YYYY HH-MM
	TYPE_Time_1_t,
	TYPE_Time_2_t,
	U16nP,
	S16nP,
	S16PP,
	TYPE_ICHARGE_MODE,
	TYPE_MPP,
	TYPE_BAT
/*	
	TYPE_bool,
	TYPE_Pulse_t,
	TYPE_Direction_t,
	TYPE_Mode_t,
	TYPE_Breaking_t,
	TYPE_AnalogOutput_Mode_t,
	TYPE_CallbackMode_t,
	TYPE_bool_1,
	TYPE_Time_HH_MM,
	TYPE_Channel_t,
	TYPE_Chopper_t,
	TYPE_PSW,					//15
	TYPE_FAULT_LABEL,
	TYPE_FAULT_PARAM_LABEL,
	U16,
	TYPE_Digital_IO_t,
	TYPE_Parameter_t,
	TYPE_AnalogInput_Dim_t,
	
	TYPE_ExtSerial_Speed_t,
	TYPE_ExtSerial_Parity_t,
	TYPE_ExtSerial_Stop_t,
	TYPE_DefaultSetting_NomCurrent_t,
	TYPE_DefaultSetting_Type_t,
	TYPE_NomPower_t,
*/
}
ValueType_t;

typedef enum
{
	LIMIT_UNK = 0,
	LIMIT_PU16,
	LIMIT_U16
}
LimitType_t;

typedef enum
{
	MPPT_CHARGESTAGE_UNK = 0,
	MPPT_CHARGESTAGE_DISABLED,
	MPPT_CHARGESTAGE_START,		
	MPPT_CHARGESTAGE_MPPT,		//3
	MPPT_CHARGESTAGE_DCVOLTAGE	//4
}
MpptChargeStage_t;



typedef struct
{
	uint16_t	Year;
	uint16_t	Month;
	uint16_t	Day;
	uint16_t	Hour;
	uint16_t	Minute;
	uint16_t	Second;
}
DateTime_t;

typedef enum
{
	CM_UNK = 0,
	RUN =1,
	STOP=2,
	FAULT=3,
	NO485=4,
	MAINSCREEN=5
}
CurrentMode_t;

typedef struct
{
	uint16_t Reg0;
	uint16_t Reg1;
	uint16_t Reg2;
	CurrentMode_t Mode;
	uint16_t Reg3;
	uint16_t Reg4;
	uint16_t Reg5;
	
	int16_t Reg_SOLBAT_CH1_U_MPP;
	int16_t Reg_SOLBAT_CH1_U_XX;
	int16_t Reg_SOLBAT_CH1_NUM_SERIAL;
	int16_t Reg_SOLBAT_CH1_NUM_PARAL;
	int16_t Reg_SOLBAT_CH1_I_KZ;
	int16_t Reg_SOLBAT_CH1_I_MPP;
	int16_t Reg_SOLBAT_CH1_MODE;
	
	int16_t RegTSTB;
	int16_t RegTRAD;
	int16_t Reg220VN;
	int16_t RegISTBN;
	int16_t RegTTR;
	int16_t RegSTBN;
	int16_t RegIINVN;
	int16_t RegI220N;
	int16_t RegIO2N;
	int16_t RegSB2N;
	int16_t RegSB1N;
	int16_t RegIO1N;
	
	int16_t RegTemp0;
	int16_t RegTemp1;
	int16_t RegTemp2;
	
	int16_t Reg_INVERTER_UOUT_SET;
	int16_t RegTemp3;
	int16_t Reg_RELAY_P2;
	int16_t Reg_RELAY_P3;
	
	int16_t Reg_SOLBAT_CH2_U_MPP;
	int16_t Reg_SOLBAT_CH2_U_XX;
	int16_t Reg_SOLBAT_CH2_NUM_SERIAL;
	int16_t Reg_SOLBAT_CH2_NUM_PARAL;
	int16_t Reg_SOLBAT_CH2_I_KZ;
	int16_t Reg_SOLBAT_CH2_I_MPP;
	int16_t Reg_SOLBAT_CH2_MODE;
	
	int16_t Reg_BAT_CELL_TYPE;
	int16_t Reg_BAT_CELL_U_NOM;
	int16_t Reg_BAT_CELL_U_FCH;
	int16_t Reg_BAT_CELL_NUM_IN_BAT;
	int16_t Reg_BAT_NUM_SER_BAT;
	int16_t Reg_BAT_CAPACITY;
	
	
	// Õ≈Œ¡–¿¡Œ“¿ÕÕ€≈
		
	int16_t Reg32;
	int16_t Reg33;
	int16_t Reg34;
	int16_t Reg35;
	
	uint16_t Reg_PowMPPT_Out;
	uint16_t Reg_PowInverter_Out;
	//int16_t RegUoutSet;
	//int16_t RegIchargeMode;
}
Page0_t;

typedef struct
{
	uint16_t Value3;
	uint16_t Value4;
}
Page1_t;

typedef enum
{
	PSW_Step_Enter,
	PSW_Step_New,
	PSW_Step_RptNew
}
PASS_Step_t;

typedef struct
{
	uint16_t	NEW_PASSWORD;
	uint16_t	ENTER_PASSWORD;
	uint16_t	ENTER_DIGIT[5];
	uint8_t		ENTER_DIGIT_1;
	uint8_t		ENTER_DIGIT_2;
	uint8_t		ENTER_DIGIT_3;
	uint8_t		ENTER_DIGIT_4;
	uint16_t	RPT_PASSWORD;
	uint8_t		CARRIAGE_DIGIT;
	PASS_Step_t	t_PASSWORD_STEP;
	
	bool		b_PAGE;
	bool		b_Timer_EditMode_Carriage_CrossVars;
	uint8_t		u8_Timer_EditMode_Carriage_Time;
	
	uint8_t		CARRIAGE_INV_DIGITAL_INPUT;
	uint8_t		CARRIAGE_INV_DIGITAL_OUTPUT;
	
	uint8_t		CARRIAGE_TYPE_Date_1_t;
	uint8_t		CARRIAGE_TYPE_Time_1_t;
	
	
}
UnsortedVars_t;

typedef struct
{
	Page0_t Page0;
	Page1_t Page1;
	DateTime_t DateTime;
	UnsortedVars_t Unsort;
}
ConvertTable_t;

typedef struct
{
	LimitType_t Type;
	Retval_t u;
}
Limit_t;

typedef struct
{
	Limit_t	Min;
	Limit_t	Max;
}
LimitMinMax_t;

typedef struct
{
	uint8_t Page;
	uint8_t Reg;
	uint16_t Bit;
}
TxData_t;

typedef struct
{
	ValueType_t	Type;
	Retval_t ret;
	LimitMinMax_t Limit;
}
Value2_t;

typedef enum	
{
	BTN_STOP,
	ENT_PASSWORD,
	EDIT_AN_ELEM_DATESET,
	EDIT_AN_ELEM_TIMESET,
	EDIT_AN_ELEM_NOMCURRENT,
	EDIT_AN_ELEM_DEFSETTINGS
}
EditFromAnotherElemType_t;

typedef struct	
{
	bool Active;
	EditFromAnotherElemType_t Type;
}
EditFromAnotherElem_t;

typedef struct
{
	Value2_t st;
	TxData_t Tx;
	//bool					Editing;
	//uint16_t				Bits;
	DateTime_t stDateTime;
	//Time2_t					Value_Time_t;
	//bool b_FromAnotherElement;
	EditFromAnotherElem_t EditFromAnElem;
}
TxMsg_t;

enum ModifyVar
{
	MODIFYVAR_PLUS,
	MODIFYVAR_MINUS
};

typedef struct					//‰ÓÔÛÒÚËÏ, Ò˜ÂÚ ‚ Â„ËÒÚ‡ı
{
	uint8_t	Page_Num;
	uint8_t	Page_Cnt;
	uint8_t	Page_Cnt_Max;
	uint8_t	Carriage_Num;
	uint8_t	Carriage_Num_Last;
}
ReqPage_t;

typedef struct	
{
	ReqPage_t* pPage;
	uint8_t PageCnt;
	uint8_t PageCnt_Max;
	
	uint16_t Focus_Page;
	uint16_t Focus_Carriage;
	uint16_t Focus_StartPosition;
	uint16_t Focus_Lenght;
}
Control_t;

uint16_t 
FillMsg(uint8_t* pin, uint8_t len);

void 
Convert_Init(void);

void 
User_Callback(bool val);

void 
Convert(uint8_t* pin);

void 
Convert_Page_0(uint8_t* pin, uint8_t car);

void 
Convert_Page_1(uint8_t* pin, uint8_t car);

uint16_t 
BCD_to_DEC(uint16_t in, uint8_t tetra);

uint16_t
DEC_to_BCD(uint16_t in, uint8_t param);

#endif