#ifndef _CONVERTTOSERIAL_H_
#define _CONVERTTOSERIAL_H_

#include "libc/stdint.h"
#include "Types.h"
#include "DataConvert.h"
#include "Menu.h"

void ConvSerial_Write( RamList_t* ram_list, uint8_t * buf, uint8_t * len);
void ConvToSerial_Time( RamList_t* ram_list, uint8_t * buf, uint8_t* len);
void ConvToSerial_Date( RamList_t* ram_list, uint8_t * buf, uint8_t* len);

#endif