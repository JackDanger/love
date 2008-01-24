#include "balance.h"

#include <stdio.h>

namespace love
{

	balance_entry balance_data[LOVE_BALANCE_SIZE] = 
	{
		{0, 0, "Image"}, 
		{0, 0, "Font"}, 
		{0, 0, "Sound"}, 
		{0, 0, "Music"},
		{0, 0, "File"}, 
		{0, 0, "Resource"}, 
		{0, 0, "Animation"}
	};

	void balance_inc(int type)
	{
		if(type < 0 && type >= LOVE_BALANCE_SIZE)
			return;
		balance_data[type].current++;
		balance_data[type].max++;
	}

	void balance_dec(int type)
	{
		if(type < 0 && type >= LOVE_BALANCE_SIZE)
			return;
		balance_data[type].current--;
	}

	void balance_print()
	{
		int overall = 0;
		printf("\nBALANCE: \n------------------------------------------\n");
		for(int i = 0;i<LOVE_BALANCE_SIZE;i++)
		{
			printf("%s %i (%i) %s\n", balance_data[i].name, balance_data[i].current, balance_data[i].max, balance_data[i].current == 0 ? "[OK]" : "[FAIL]");
			overall += balance_data[i].current;
		}
		printf("\n----------------\nVERDICT: %s\n----------------", overall == 0 ? "[OK]" : "[MASSIVE FAIL]");
	}

} // love

