#ifndef		_KEYBOARD_H_
#define		_KEYBOARD_H_

//#include 	"DSP2833x_Device.h"
//#include 	"DSP2833x_Examples.h"
#include "Types.h"
#include "stdint.h"
#include "Menu.h"

/*
#define		SB1()					((GpioDataRegs.GPCDAT.bit.GPIO87 == 1) ? (false) : (true))
#define		SB2()					((GpioDataRegs.GPADAT.bit.GPIO28 == 1) ? (false) : (true))
#define		SB3()					((GpioDataRegs.GPADAT.bit.GPIO30 == 1) ? (false) : (true))
#define		SB4()					((GpioDataRegs.GPADAT.bit.GPIO31 == 1) ? (false) : (true))
#define		SB5()					((GpioDataRegs.GPBDAT.bit.GPIO32 == 1) ? (false) : (true))
#define		SB6()					((GpioDataRegs.GPBDAT.bit.GPIO34 == 1) ? (false) : (true))
*/
#define		PARAMETER_MENUSCROLL	2
#define		DELAY_COUNT				100

enum e_EXTIPush
{
	NoEXTI = 0, 
	But1 = 1, 
	But2 = 2,
	But3 = 3, 
	But4 = 4,
	But5 = 5, 
	But6 = 6,
	But1_Long,
	But2_Long,
	
	But3_Long,
	But3_Long_x5Speed,
	But3_Long_x10Speed,
	But3_Long_x50Speed,
	But3_Long_x100Speed,
	
	But4_Long,
	But4_Long_x5Speed,
	But4_Long_x10Speed,
	But4_Long_x50Speed,
	But4_Long_x100Speed,
	
	But5_Long,
	But6_Long,
	But1_Long_First,
	But2_Long_First,
	But3_Long_First,
	But4_Long_First,
	But5_Long_First,
	But6_Long_First,
	
	But1Long_But5,
	But1Long_But4,
	But1Long_But3,
	But1Long_But6,
	
	But1Long_But4Long,
	But1Long_But3Long
};

typedef		enum	e_EXTIPush		EXTIPush_t;

void DoAction( RamList_t* ram_list, EXTIPush_t* pt_ButtonCodes);
void GetButtonCodes(EXTIPush_t* pt_ButtonCodes_Container);

#endif