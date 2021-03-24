#ifndef _TYPES_H_
#define _TYPES_H_

#include "libc/stdint.h"

typedef enum
{
	false = 0,
	true = 1
}
bool;

typedef struct
{
	//Value2_t				Value;
	//Transmit_Data_t			Transmit;
	bool					Editing;
	uint16_t				Bits;
	//DateTime_t				Value_DateTime_t;
	//Time2_t					Value_Time_t;
	bool					b_FromAnotherElement;
	//EditFromAnotherElem_t	t_EditFromAnotherElem;
}
Msg_t;

#define EUNK 0


#endif