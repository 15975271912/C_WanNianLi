/************************************************************************/
/* 
�ṩ�˹���ũ����ת�����ڡ����������š���÷����÷�����ղ�ѯ��
��������ο���
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