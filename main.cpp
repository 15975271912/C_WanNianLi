/************************************************************************/
/* 
提供了公、农历互转，星期、节气、数九、入梅、出梅、伏日查询。
代码仅供参考。
*/
/************************************************************************/
#include <stdio.h>
#include "Helper.h"


int main(void)
{
	int nChoise=0;
	while (1)
	{
		ShowMenu();
		scanf("%d",&nChoise);
		printf("\n");
		switch (nChoise)
		{
		case 1:
			RL();
			break;
		case 2:
			GL2NL();
			break;
		case 3:
			NL2GL();
			break;
		case 4:
			JQ();
			break;
		default:
			break;
		}
	}
	return 0;
}