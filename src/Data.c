#include "data.h"
#include "libc/avr/pgmspace.h"
#include "Menu.h"
#include "DataConvert.h"
#include "ModbusProtocolTable.h"

extern ConvertTable_t Table;

uint16_t var1 = 125;
uint16_t var2 = 1015;

char	sram_0_2_LABEL[]				= "CM_UNK";

extern Element_t Element1[MAIN_MENU_DIM_X][MAIN_MENU_DIM_Y];
TableJump_t Jumps[] PROGMEM =
{
	{	//0
		.pst = &Element1[0][0]
	},
	{	//1
		.pst = &Element1[0][1]
	},
	{	//2
		.pst = &Element1[0][2]
	},
	{	//3
		.pst = &Element1[0][3]
	},
	{	//4
		.pst = &Element1[0][4]
	},
	{	//5
		.pst = &Element1[0][4]
	}
};

/*
	
*/
char sLabel_PGM_Data_2_0[] PROGMEM = "";
char sLabel_PGM_Data_2_1[] PROGMEM = "";
char sLabel_PGM_Data_2_2[] PROGMEM = "";
char sLabel_PGM_Data_2_3[] PROGMEM = "Уст. даты";
char sLabel_PGM_Data_2_4[] PROGMEM = "Уст. времени";


char sLabel_PGM_Data_3_0[] PROGMEM = "Кол-во послед.";
char sLabel_PGM_Data_3_1[] PROGMEM = "Кол-во парал.";
char sLabel_PGM_Data_3_2[] PROGMEM = "Ток К.З.";
char sLabel_PGM_Data_3_3[] PROGMEM = "Напряж Х.Х.";
char sLabel_PGM_Data_3_4[] PROGMEM = "Ток МPP";
char sLabel_PGM_Data_3_5[] PROGMEM = "Напряж МPP";
char sLabel_PGM_Data_3_6[] PROGMEM = "Разрешить";


char sLabel_PGM_Data_4_0[] PROGMEM = "Тип ячейки";
char sLabel_PGM_Data_4_1[] PROGMEM = "Напряж. яч. ном";
char sLabel_PGM_Data_4_2[] PROGMEM = "Напряж. яч. зар";
char sLabel_PGM_Data_4_3[] PROGMEM = "Кол-во яч. в бат";
char sLabel_PGM_Data_4_4[] PROGMEM = "Кол-во посл. бат";
char sLabel_PGM_Data_4_5[] PROGMEM = "Емкость";


/*
char sLabel_PGM_Data_4_0[] PROGMEM = "Тип ячейки";
char sLabel_PGM_Data_4_1[] PROGMEM = "Емкость";
char sLabel_PGM_Data_4_2[] PROGMEM = "Напряж. цикл.";
char sLabel_PGM_Data_4_3[] PROGMEM = "Напряж. буф.";
char sLabel_PGM_Data_4_4[] PROGMEM = "Напряж. разряд.";
char sLabel_PGM_Data_4_5[] PROGMEM = "Ток заряда макс.";
char sLabel_PGM_Data_4_6[] PROGMEM = "Ток заряда буф.";
char sLabel_PGM_Data_4_7[] PROGMEM = "Темп.коэф.ячейки";
char sLabel_PGM_Data_4_8[] PROGMEM = "Кол-во посл. бат";
char sLabel_PGM_Data_4_9[] PROGMEM = "Кол-во яч. в бат";
char sLabel_PGM_Data_4_10[] PROGMEM = "Напряж. яч. ном";
char sLabel_PGM_Data_4_11[] PROGMEM = "Напряж. яч. зар";
*/
//char sLabel_PGM_Data_4_12[] PROGMEM = "";
//char sLabel_PGM_Data_4_13[] PROGMEM = "";
//char sLabel_PGM_Data_4_14[] PROGMEM = "";


char sLabel_PGM_Data_5_0[] PROGMEM = "Поиск ТММ";
char sLabel_PGM_Data_5_1[] PROGMEM = "Тип стабилизации";
char sLabel_PGM_Data_5_2[] PROGMEM = "Период сканирования";
char sLabel_PGM_Data_5_3[] PROGMEM = "Парал. включение";

char sLabel_PGM_Data_6_0[] PROGMEM = "Разрешить";
char sLabel_PGM_Data_6_1[] PROGMEM = "Выход.напряжение";

char sLabel_PGM_Data_8_0[] PROGMEM = "Розетка P2";
char sLabel_PGM_Data_8_1[] PROGMEM = "Розетка P3";

/*
	
*/

char s_NULL[] PROGMEM	= "";
PGM_P spgm_NULL[] PROGMEM =
{
	s_NULL
};

char s_UNK[] PROGMEM	= "?";
PGM_P spgm_UNK[] PROGMEM =
{
	s_UNK
};

char s_1_0_LABEL_1[] PROGMEM = "Выбор";
char s_1_0_LABEL_2[] PROGMEM = "режима";

char s_2_0_LABEL_1[] PROGMEM = "ШИМ Инвертор";
char s_2_1_LABEL_1[] PROGMEM = "ШИМ MPPT1";
char s_2_2_LABEL_1[] PROGMEM = "ШИМ MPPT2";

char s_3_1_LABEL_1[] PROGMEM = "tempBattery";
char s_3_2_LABEL_1[] PROGMEM = "tempCooler";
char s_3_3_LABEL_1[] PROGMEM = "voltageLoad";
char s_3_4_LABEL_1[] PROGMEM = "currentBattery";
char s_3_5_LABEL_1[] PROGMEM = "tempTransformer";
char s_3_6_LABEL_1[] PROGMEM = "VoltageBattery";
char s_3_7_LABEL_1[] PROGMEM = "currentBridge";
char s_3_8_LABEL_1[] PROGMEM = "currentLoad";
char s_3_9_LABEL_1[] PROGMEM = "currentMPPT2";
char s_3_10_LABEL_1[] PROGMEM = "voltageMPPT2";
char s_3_11_LABEL_1[] PROGMEM = "voltageMPPT1";
char s_3_12_LABEL_1[] PROGMEM = "currentMPPT1";
char s_3_13_LABEL_1[] PROGMEM = "RegTemp0";
char s_3_14_LABEL_1[] PROGMEM = "RegTemp1";
char s_3_15_LABEL_1[] PROGMEM = "RegTemp2";

char s_2_3_LABEL_1[] PROGMEM = "Инвертор";
char s_2_4_LABEL_1[] PROGMEM = "MPPT1";
char s_2_5_LABEL_1[] PROGMEM = "MPPT2";

char s_PERCENTAGE[] PROGMEM = "Задание";
char s_val[] PROGMEM = "Знач.";
char s_val2[] PROGMEM = "U вых.";
char s_val3[] PROGMEM = "I вых.";
char s_val1[] PROGMEM = "ШИМ Инв.";

char s_LCDMain_P_in[] PROGMEM = "P вход.";
char s_LCDMain_P_out[] PROGMEM = "P нагр.";
char s_LCDMain_pi_icharge[] PROGMEM = "ПИ-рег";
char s_LCDMain_icharge_mode[] PROGMEM = "Режим зар.";
char s_LCDMain_debug3[] PROGMEM = "debug 3";

char s_Data_0_Label_0_Up[] PROGMEM = "CM_UNK";
char s_Data_0_Label_0_Low[] PROGMEM = "Инициал.";

char s_Data_0_Label_1_Up[] PROGMEM = "STOP";
char s_Data_0_Label_1_Low[] PROGMEM = "Останов";

char s_Data_0_Label_2_Up[] PROGMEM = "RUN";
char s_Data_0_Label_2_Low[] PROGMEM = "Работа";

char s_Data_0_Label_3_Up[] PROGMEM = "FAULT";
char s_Data_0_Label_3_Low[] PROGMEM = "авария";

char s_Data_0_Label_4_Up[] PROGMEM = "NO485";
char s_Data_0_Label_4_Low[] PROGMEM = "нет связи";


char s_Data_2_Label_1_Up[] PROGMEM = "Управление";
char s_Data_2_Label_1_Low[] PROGMEM = "инвертором";

char s_Data_2_Label_2_Up[] PROGMEM = "Измерения";
char s_Data_2_Label_2_Low[] PROGMEM = "с датчиков";

char s_Data_1_Label_3_Up[] PROGMEM = "Установка";
char s_Data_1_Label_3_Low[] PROGMEM = "даты/времени";

char s_Data_1_Label_4_Up[] PROGMEM = "Контроллер";
char s_Data_1_Label_4_Low[] PROGMEM = "заряда MPPT";

char s_Data_1_Label_5_Up[] PROGMEM = "Параметры";
char s_Data_1_Label_5_Low[] PROGMEM = "аккумулятора";

char s_Data_1_Label_6_Up[] PROGMEM = "Конроллер";
char s_Data_1_Label_6_Low[] PROGMEM = "заряда";

char s_Data_1_Label_7_Up[] PROGMEM = "Параметры";
char s_Data_1_Label_7_Low[] PROGMEM = "инвертора";

char s_Data_1_Label_8_Up[] PROGMEM = "Канал 1";
char s_Data_1_Label_8_Low[] PROGMEM = " ";

char s_Data_1_Label_9_Up[] PROGMEM = "Канал 2";
char s_Data_1_Label_9_Low[] PROGMEM = " ";

char s_Data_1_Label_10_Up[] PROGMEM = "Нет связи";
char s_Data_1_Label_10_Low[] PROGMEM = "по RS-485";

char s_Data_1_Label_11_Up[] PROGMEM = "Настройка";
char s_Data_1_Label_11_Low[] PROGMEM = "выходов";

char s_Data_3_Label_0[] PROGMEM = "Данные типа 3";
char s_Data_3_ParamLabel_0[] PROGMEM = "Параметр";

PGM_Data_1_t PGM_Data_1[DATA1_MENU_DIM] PROGMEM = 
{
	{	//0
		.p_Label_Up = s_Data_0_Label_0_Up,
		.p_Label_Low = s_Data_0_Label_0_Low,
	},
	{	//1
		.p_Label_Up = s_Data_2_Label_1_Up,
		.p_Label_Low = s_Data_2_Label_1_Low,
	},
	{	//2
		.p_Label_Up = s_Data_2_Label_2_Up,
		.p_Label_Low = s_Data_2_Label_2_Low,
	},
	{	//3
		.p_Label_Up = s_Data_1_Label_3_Up,
		.p_Label_Low = s_Data_1_Label_3_Low,
	},
	{	//4
		.p_Label_Up = s_Data_1_Label_4_Up,
		.p_Label_Low = s_Data_1_Label_4_Low,
	},
	{	//5
		.p_Label_Up = s_Data_1_Label_5_Up,
		.p_Label_Low = s_Data_1_Label_5_Low,
	},
	{	//6
		.p_Label_Up = s_Data_1_Label_6_Up,
		.p_Label_Low = s_Data_1_Label_6_Low,
	},
	{	//7
		.p_Label_Up = s_Data_1_Label_7_Up,
		.p_Label_Low = s_Data_1_Label_7_Low,
	},
	{	//8
		.p_Label_Up = s_Data_1_Label_8_Up,
		.p_Label_Low = s_Data_1_Label_8_Low,
	},
	{	//9
		.p_Label_Up = s_Data_1_Label_9_Up,
		.p_Label_Low = s_Data_1_Label_9_Low,
	},
	{	//10
		.p_Label_Up = s_Data_1_Label_10_Up,
		.p_Label_Low = s_Data_1_Label_10_Low,
	},
	{	//11
		.p_Label_Up = s_Data_1_Label_11_Up,
		.p_Label_Low = s_Data_1_Label_11_Low,
	}
};


PGM_Data_2_t
PGM_Data_2[DATA2_MENU_DIM_X][DATA2_MENU_DIM_Y] PROGMEM = 
{
	{//0
		{	//0,0
			.Label = s_3_1_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16nP,
				.Units = UNITS_TEMP,
				.pvData = &(Table.Page0.RegTSTB),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_TSTB,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,1
			.Label = s_3_2_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16nP,
				.Units = UNITS_TEMP,
				.pvData = &(Table.Page0.RegTRAD),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_TRAD,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,2
			.Label = s_3_3_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16nP,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg220VN),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_220VN,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,3
			.Label = s_3_4_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				.Type = S16,
				//.Type = S16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.RegISTBN),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_ISTBN,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,4
			.Label = s_3_5_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16nP,
				.Units = UNITS_TEMP,
				.pvData = &(Table.Page0.RegTTR),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_TTR,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,5
			.Label = s_3_6_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16,
				.Type = S16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.RegSTBN),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_STBN,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,6
			.Label = s_3_7_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.RegIINVN),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_IINVN,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,7
			.Label = s_3_8_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.RegI220N),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_I220N,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,8
			.Label = s_3_9_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.RegIO2N),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_IO2N,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,9
			.Label = s_3_10_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.RegSB2N),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_SB2N,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,10
			.Label = s_3_11_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16nP,
				.Type = S16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.RegSB1N),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_SB1N,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,11
			.Label = s_3_12_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				//.Type = U16,
				.Type = S16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.RegIO1N),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_ADC_IO1N,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,12
			.Label = s_3_13_LABEL_1,
			.ParamLabel = s_val1,
			.Value = 
			{
				.Type = S16nP,
				//.Type = S16nP,
				.Units = UNITS_PERCENT,
				.pvData = &(Table.Page0.RegTemp0),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_DEBUG_TEMP0,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,13
			.Label = s_3_14_LABEL_1,
			.ParamLabel = s_val1,
			.Value = 
			{
				.Type = S16nP,
				//.Type = S16nP,
				.Units = UNITS_PERCENT,
				.pvData = &(Table.Page0.RegTemp1),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_DEBUG_TEMP1,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{	//0,15
			.Label = s_3_15_LABEL_1,
			.ParamLabel = s_val,
			.Value = 
			{
				.Type = S16nP,
				//.Type = S16nP,
				.Units = UNITS_PERCENT,
				.pvData = &(Table.Page0.RegTemp2),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_DEBUG_TEMP2,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
	},
	{//1
		{//1,0
			.Label = s_2_0_LABEL_1,
			.ParamLabel = s_PERCENTAGE,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg0),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_0,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{//1,1
			.Label = s_2_1_LABEL_1,
			.ParamLabel = s_PERCENTAGE,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg1),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_1,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{//1,2
			.Label = s_2_2_LABEL_1,
			.ParamLabel = s_PERCENTAGE,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg2),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_2,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{//1,3
			.Label = s_2_3_LABEL_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg3),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_INVERTER,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{//1,4
			.Label = s_2_4_LABEL_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg4),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_MPPT1,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{//1,5
			.Label = s_2_5_LABEL_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg5),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_MPPT2,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{//1,6
		},
		{//1,7
		},
		{//1,8
		},
		{//1,9
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
	{//2
		{	//2,0
			.Label = sLabel_PGM_Data_2_3,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = TYPE_Date_1_t,
				.Units = UNITS_NULL,
				.pvData = &(Table.DateTime),
			},
			{
				.Page = 0,
				.Reg = 3,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{	//2,1
			.Label = sLabel_PGM_Data_2_4,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = TYPE_Time_1_t,
				.Units = UNITS_NULL,
				.pvData = &(Table.DateTime),
			},
			{
				.Page = 0,
				.Reg = 1,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
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
		{//2,13
		},
		{//2,14
		}
	},
	{//3 ПАНЕЛИ СОЛН. канал 1
		{//3,0
			.Label = sLabel_PGM_Data_3_0,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH1_NUM_SERIAL),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH1_NUM_SERIAL,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//3,1
			.Label = sLabel_PGM_Data_3_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH1_NUM_PARAL),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH1_NUM_PARAL,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//3,2
			.Label = sLabel_PGM_Data_3_2,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH1_I_KZ),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH1_I_KZ,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//3,3
			.Label = sLabel_PGM_Data_3_3,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH1_U_XX),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH1_U_XX,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//3,4
			.Label = sLabel_PGM_Data_3_4,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH1_I_MPP),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH1_I_MPP,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//3,5
			.Label = sLabel_PGM_Data_3_5,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH1_U_MPP),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH1_U_MPP,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//3,6
			.Label = sLabel_PGM_Data_3_6,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg4),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_MPPT1,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//3,7
			
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
		{//2,13
		},
		{//2,14
		}
	},
	{//4 АККУМУЛЯТОР
		{//4,0
			.Label = sLabel_PGM_Data_4_0,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = TYPE_BAT,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_BAT_CELL_TYPE),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_BAT_CELL_TYPE,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//4,1
			.Label = sLabel_PGM_Data_4_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg_BAT_CELL_U_NOM),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_BAT_CELL_U_NOM,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//4,2
			.Label = sLabel_PGM_Data_4_2,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg_BAT_CELL_U_FCH),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_BAT_CELL_U_FCH,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//4,3
			.Label = sLabel_PGM_Data_4_3,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_BAT_CELL_NUM_IN_BAT),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_BAT_CELL_NUM_IN_BAT,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//4,4
			.Label = sLabel_PGM_Data_4_4,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_BAT_NUM_SER_BAT),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_BAT_NUM_SER_BAT,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//4,5
			.Label = sLabel_PGM_Data_4_5,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_CAP_Ah,
				.pvData = &(Table.Page0.Reg_BAT_CAPACITY),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_BAT_CAPACITY,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//4,6
		},
		{//4,7
		},
		{//4,8
		},
		{//4,9
		},
		{//4,10
		},
		{//4,11
		},
		{//4,12
		},
		{//4,13
		},
		{//4,14
		}
	},
	{//5 КОНТР.ЗАРЯДА общий для обоих каналов 1,2
		{	//5,0
			.Label = sLabel_PGM_Data_5_0,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg32),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_MPPT_TMM,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{	//5,1
			.Label = sLabel_PGM_Data_5_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg33),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_MPPT_TYPE_STAB,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{	//5,2
			.Label = sLabel_PGM_Data_5_2,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg34),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_MPPT_SCAN_PER,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{	//5,3
			.Label = sLabel_PGM_Data_5_3,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg35),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_MPPT_PARAL,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//5,4
		},
		{//5,5
		},
		{//5,6
		},
		{//5,7
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
		{//4,13
		},
		{//4,14
		}
	},
	{//6 ИНВЕРТОР
		{//6,0
			.Label = sLabel_PGM_Data_6_0,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg3),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_INVERTER,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0,
		},
		{//6,1
			.Label = sLabel_PGM_Data_6_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg_INVERTER_UOUT_SET),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_INVERTER_UOUT_SET,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//6,2
		},
		{//6,3
		},
		{//6,4
		},
		{//6,5
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
	{//7 ПАНЕЛИ СОЛН. канал 2
		{//7,0
			.Label = sLabel_PGM_Data_3_0,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH2_NUM_SERIAL),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH2_NUM_SERIAL,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//7,1
			.Label = sLabel_PGM_Data_3_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16nP,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH2_NUM_PARAL),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH2_NUM_PARAL,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//7,2
			.Label = sLabel_PGM_Data_3_2,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH2_I_KZ),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH2_I_KZ,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//7,3
			.Label = sLabel_PGM_Data_3_3,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH2_U_XX),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH2_U_XX,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//7,4
			.Label = sLabel_PGM_Data_3_4,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_AMPER,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH2_I_MPP),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH2_I_MPP,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//7,5
			.Label = sLabel_PGM_Data_3_5,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = U16,
				.Units = UNITS_VOLT,
				.pvData = &(Table.Page0.Reg_SOLBAT_CH2_U_MPP),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_SOLBAT_CH2_U_MPP,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//7,6
			.Label = sLabel_PGM_Data_3_6,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg5),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_REG_MPPT2,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
			
		},
		{//7,7
		},
		{//7,8
		},
		{//7,9
		},
		{//7,10
		},
		{//7,11
		},
		{//7,12
		},
		{//7,13
		},
		{//7,14
		}
	},
	{//8 ВЫБОР РЕЛЕ
		{//8,0
			.Label = sLabel_PGM_Data_8_0,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_RELAY_P2),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_RELAY_P2,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
		},
		{//8,1
			.Label = sLabel_PGM_Data_8_1,
			.ParamLabel = s_NULL,
			.Value = 
			{
				.Type = BOOL,
				.Units = UNITS_NULL,
				.pvData = &(Table.Page0.Reg_RELAY_P3),
			},
			{
				.Page = MODBUS_PAGE_0,
				.Reg = MODBUS_RELAY_P3,
				.Bit = 0,
			},
			.Opt = 0,
			.Flag = 0
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
		{//8,13
		},
		{//8,13
		},
		{//8,13
		},
		{//8,13
		},
		{//8,13
		},
		{//8,13
		},
		{//8,13
		},
		{//8,14
		}
	},
};

PGM_Data_Main_3_2_t
PGM_Data_Main_3_2[DATAMAIN_MENU_DIM] PROGMEM = 
{
	{	//0,0
		.ParamLabel_0 = s_LCDMain_P_in,
		.ParamLabel_1 = s_val2,
		.Value_0 = {
			//.Type = U16nP,
			.Type = S16nP,
			.Units = UNITS_WATT,
			.pvData = &(Table.Page0.Reg_PowMPPT_Out),
		},
		.Value_1 = {
			//.Type = U16nP,
			.Type = S16nP,
			.Units = UNITS_NULL,
			.pvData = &(Table.Page0.Reg220VN),
		},
		.Tx = {
			.Page = MODBUS_PAGE_0,
			.Reg = MODBUS_STARTSTOP,
			.Bit = 0
		},
		.Opt = 0,
		.Flag = 0,
	},
	{	//0,1
		.ParamLabel_0 = s_LCDMain_P_out,
		.ParamLabel_1 = s_val3,
		.Value_0 = {
			//.Type = U16nP,
			.Type = S16nP,
			.Units = UNITS_WATT,
			.pvData = &(Table.Page0.Reg_PowInverter_Out),
		},
		.Value_1 = {
			//.Type = U16nP,
			.Type = S16nP,
			.Units = UNITS_NULL,
			.pvData = &(Table.Page0.RegSB1N),
		},
		.Tx = {
			.Page = MODBUS_PAGE_0,
			.Reg = MODBUS_STARTSTOP,
			.Bit = 0
		},
		.Opt = 0,
		.Flag = 0,
	},
	{	//0,2
		.ParamLabel_0 = s_LCDMain_pi_icharge,
		.ParamLabel_1 = s_val3,
		.Value_0 = {
			.Type = S16nP,
			.Units = UNITS_PERCENT,
			.pvData = &(Table.Page0.RegTemp1),
		},
		.Value_1 = {
			.Type = S16nP,
			.Units = UNITS_NULL,
			.pvData = &(Table.Page0.RegSB1N),
		},
		.Tx = {
			.Page = MODBUS_PAGE_0,
			.Reg = MODBUS_STARTSTOP,
			.Bit = 0
		},
		.Opt = 0,
		.Flag = 0,
	},
	{	//0,3
		.ParamLabel_0 = s_LCDMain_icharge_mode,
		.ParamLabel_1 = s_val3,
		.Value_0 = {
			.Type = TYPE_ICHARGE_MODE,
			.Units = UNITS_NULL,
			.pvData = &(Table.Page0.Reg_SOLBAT_CH1_MODE),
		},
		.Value_1 = {
			.Type = S16nP,
			.Units = UNITS_NULL,
			.pvData = &(Table.Page0.RegSB1N),
		},
		.Tx = {
			.Page = MODBUS_PAGE_0,
			.Reg = MODBUS_STARTSTOP,
			.Bit = 0
		},
		.Opt = 0,
		.Flag = 0,
	},
	{	//0,4
		.ParamLabel_0 = s_LCDMain_debug3,
		.ParamLabel_1 = s_val3,
		.Value_0 = {
			.Type = TYPE_MPP,
			.Units = UNITS_NULL,
			.pvData = &(Table.Page0.RegTemp3),
		},
		.Value_1 = {
			.Type = S16nP,
			.Units = UNITS_NULL,
			.pvData = &(Table.Page0.RegSB1N),
		},
		.Tx = {
			.Page = MODBUS_PAGE_0,
			.Reg = MODBUS_STARTSTOP,
			.Bit = 0
		},
		.Opt = 0,
		.Flag = 0,
	}
};


char s_UnitName_t_TIME[] PROGMEM	= "сек";
char s_UnitName_t_FREQ[] PROGMEM	= " Гц";
char s_UnitName_t_AMPER[] PROGMEM = " А";
char s_UnitName_t_VOLT[] PROGMEM	= " В";
char s_UnitName_t_TEMP[] PROGMEM	= " C";
//char	s_UnitName_t_TEMP[] PROGMEM	= {6,'C',0};
char s_UnitName_t_POWER[] PROGMEM = " Вт";
char s_UnitName_t_kPOWER[] PROGMEM = " кВт";
char s_UnitName_t_Percent[] PROGMEM = " %";
char s_UnitName_t_Capacity_Ah[] PROGMEM = " А/ч";
PGM_P spgm_UnitName_t[] PROGMEM =
{
	s_UnitName_t_TIME,
	s_UnitName_t_FREQ,
	s_UnitName_t_AMPER,
	s_UnitName_t_VOLT,
	s_UnitName_t_TEMP,
	s_UnitName_t_POWER,
	s_UnitName_t_kPOWER,
	s_UnitName_t_Percent,
	s_UnitName_t_Capacity_Ah
};

char	s_bool_TRUE[]							PROGMEM = "вкл.";
char	s_bool_FALSE[]							PROGMEM = "выкл.";
PGM_P spgm_bool[] PROGMEM =
{
	s_bool_TRUE,
	s_bool_FALSE
};

char	s_ICHARGE_MODE_MPPT[]					PROGMEM = "MPPT";
char	s_ICHARGE_MODE_UCONST[]					PROGMEM = "=U";
char	s_ICHARGE_MODE_disable[]				PROGMEM = "OFF";
PGM_P spgm_ICHARGE_MODE[] PROGMEM =
{
	s_ICHARGE_MODE_MPPT,
	s_ICHARGE_MODE_UCONST,
	s_ICHARGE_MODE_disable
};

char s_MPP_DIS[] PROGMEM = "MPP_DIS";
char s_MPP_NORM[] PROGMEM = "MPP_NORM";
char s_MPP_STAB[] PROGMEM = "MPP_STAB";
char s_MPP_KZ[] PROGMEM = "MPP_KZ";
PGM_P spgm_MPP[] PROGMEM =
{
	s_MPP_DIS,
	s_MPP_NORM,
	s_MPP_STAB,
	s_MPP_KZ
};

char s_BAT_LEAD_ACID[] PROGMEM = "LEAD_ACID";
char s_BAT_GEL_AGM[] PROGMEM = "GEL_AGM";
char s_BAT_LIION_37[] PROGMEM = "LIION_37";
char s_BAT_LIION_39[] PROGMEM = "LIION_39";
PGM_P spgm_BAT[] PROGMEM =
{
	s_BAT_LEAD_ACID,
	s_BAT_GEL_AGM,
	s_BAT_LIION_37,
	s_BAT_LIION_39
};
