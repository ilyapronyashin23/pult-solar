#include "ISR.h"
#include "DisplayFormatter.h"
#include "Keyboard.h"
#include "Menu.h"

#include "inttypes.h"
#include "avr/io.h"
#include "compat/ina90.h"
#include "Modbus.h"
#include "util/delay.h"

uint8_t	Cnt = 0;
extern EXTIPush_t ButtonCodes[6];
//extern RamDataContainer_t RamData;
//extern RamDataContainer_t* pRam[2];
extern st_Master_t dev;
extern RamList_t* p_ram_list;

bool var0 = false;

ISR
(TIMER1_OVF_vect)
{
	
	if (Cnt == 4)	//4 или 12 для связи с компом
	{
		Cnt = 0;
		
		
		

		//if (p_ram_list->p_now->Msg.Tx.Reg == MODBUS_STARTSTOP)
			
		
		//_delay_ms(5);
		
		/*
		var0 ^= (bool)1;
		
		if (var0){
			p_ram_list->p_now = p_ram_list->p_ram_main;
		}
		else{
			p_ram_list->p_now = p_ram_list->p_ram_parview;
		}
		*/
		
		GetButtonCodes(ButtonCodes);
		DoAction(p_ram_list, ButtonCodes);
		
		Update_Screen(p_ram_list);
		
		dev.Modbus.WAIT_SLAVE_ANSWER = false;
		Send_Switch(p_ram_list);
	}
	else Cnt++;
}
/**/

ISR
(TIMER0_COMP_vect)
{
	dev.pv_Timer_Compare(&dev);
}

ISR
(TIMER2_OVF_vect)
{
	//SOUND_Duration();
}

ISR
(TIMER2_COMP_vect)
{
	//SOUND_Tone();
}

ISR
(USART1_RX_vect)
{
	uint8_t data = (uint8_t)UDR1;
	dev.pv_Receive(&dev, data);
}
