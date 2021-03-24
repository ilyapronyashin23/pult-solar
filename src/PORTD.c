
if(p_ram_list->p_now->Level == LEVEL0)
			PORTD ^= 1<<7;
		else
			PORTD &= ~(1<<7);
		
		if(p_ram_list->p_now->Level == LEVEL1)
			PORTD ^= 1<<6;
		else
			PORTD &= ~(1<<6);
		
		if(p_ram_list->p_now->Level == LEVEL2)
			PORTD ^= 1<<5;
		else
			PORTD &= ~(1<<5);
		
		if(p_ram_list->p_now->Level == LEVEL3)
			PORTD ^= 1<<0;
		else
			PORTD &= ~(1<<0);
		
		if (p_ram_list->p_now == p_ram_list->p_ram_main)
			PORTD ^= 1<<1;
		else
			PORTD &= ~(1<<1);