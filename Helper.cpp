#include "Helper.h"
#include "LunarData.h"
#include <stdio.h>
#include <Windows.h>

#ifndef BOOL
typedef int BOOL;
#endif //BOOL

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/*
ע�⣬���֧��������ո�Ŀ¼�¡�ũ�����.txt���еķ������¸�֧����Ƚϸ��ӣ�
���Խ���Ϊ�磨ע�⣬��������������ָ���������ݡ����������ġ�â�֡�С���
���¶����¶����������ѩ��С����12��������ļ�Ϊ��������1998��12��7��(��
ѩ)���¸�֧Ϊ���ӣ����ڴ˻����Ͻ���ǰ�ƺͺ��ơ��ո�֧��2000��1��7�գ�����
�գ�Ϊ�ο���ֻҪ����������֪���ո�֧��ʱ��֧���Ǹ����ո�֧������ģ���
�ɸ����յ���������¶�Ӧ��ϵ���ס����üף��ҡ����ñ������������죬�����ɵ�
�����졢����ɣ�ʱ��֧��Ϊ��ÿ����СʱΪһ����֧��������ǰһ���23ʱ��1ʱΪ
��ʱ��1ʱ��3ʱΪ��ʱ���������ơ�
*/

/*
�����е������㷨���õ���һ��ͨ���㷨����ʽ���£�
W = [Y-1] + [(Y-1)/4] - [(Y-1)/100] + [(Y-1)/400] + D
Y���������D����һ������һ���е�����������1��Ҳ������һ������һ�����ǵڼ��졣
�����ʽ������֤��һ���ǿ��еģ��ͱ�����֧�ֵ������������������ȷ�ġ�
*/

char *Riming[30]={"��һ","����","����","����","����","����","����","����","����","��ʮ","ʮһ","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","��ʮ","إһ","إ��","إ��","إ��","إ��","إ��","إ��","إ��","إ��","��ʮ"};
char *Yueming[12]={"����","����","����","����","����","����","����","����","����","ʮ��","����","����"};
char *Tiangan[10]={"��", "��", "��", "��", "��", "��", "��", "��", "��", "��"};
char *Dizhi[12]={"��", "��", "��", "î", "��", "��", "��", "δ", "��", "��", "��", "��"};
char *Shengxiao[12]={"��", "ţ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" };
char *Jieqi[24]={"����", "��ˮ", "����", "����", "����", "����", "����", "С��", "â��", "����", "С��", "����", "����", "����", "��¶", "���", "��¶", "˪��", "����", "Сѩ", "��ѩ", "����", "С��", "��"};
char *Xingqi[7]={"������","����һ","���ڶ�","������","������","������","������"};
char *Shujiu[9]={"һ��","����","����","�ľ�","���","����","�߾�","�˾�","�ž�"};
char *Meiyu[2]={"��÷","��÷"};
char *Sanfu[3]={"����","�з�","ĩ��"};

unsigned short DayOrdinal[13]={0,31,59,90,120,151,181,212,243,273,304,334,365};
unsigned short DayOrdinalLeap[13]={0,31,60,91,121,152,182,213,244,274,305,335,366};

//�ж����꣬��������ݣ�����ֵ��0-ƽ�꣬1-����
BOOL IsLeapYear(short sYear);

//�������������ڵ��������������꣬�£��գ���������������ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL GetDayOrdinal(short sYear, unsigned short wMonth, unsigned short wDay,int *nDays);

//���������������¡��գ��������꣬�����������£��գ�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL GetDateFromOrdinal(short sYear,short sOrdinal,unsigned short* wMonth,unsigned short* wDay);

//�����ꡢ�¡��յĺϷ��ԣ��������꣬�£��գ�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL DateCheck(short sYear,unsigned short wMonth,unsigned short wDay);

//��ȡũ������Ĺ�������������������ũ���꣬����ֵ��ũ������Ĺ�����������
short LunarGetNewYearOrdinal(short sLunarYear);

//��ȡũ���µ�������������ũ���꣬ũ���£��Ƿ�Ϊ���£�����ֵ����ũ���µ�������Ϊ0���������Ч
unsigned short LunarGetDaysofMonth(short sLunarYear,unsigned short wLunarMonth,BOOL bLeapMonth);

//չ����С�����ݱ�ĳһ��ģ���������ũ���꣬����һ��ʮһ�¿�ʼ����ǰ��ݣ���ʮ���µ�ÿ������������ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL LunarExpandDX(short sLunarYear,int iDayOfMonth[15]);

//��ȡũ��ĳһ������������������ũ���꣬����ֵ������������·ݣ�0��ʾ������
unsigned short LunarGetLeapMonth(short sLunarYear);

//��ȡũ���·���Ϣ
BOOL GetMonthInfo(unsigned short wYear,unsigned int* puData);

//����תũ���������������ꡢ�¡��գ�ũ���ꡢ�¡��գ��Ƿ�Ϊ���£�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL Gongli2Nongli(short sYear,unsigned short wMonth,unsigned short wDay,short* sLunarYear,unsigned short* wLunarMonth,unsigned short* wLunarDay,BOOL* bLeapMonth);

//ũ��ת�����������������ꡢ�¡��գ��Ƿ�Ϊ���£������ꡢ�¡��գ�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL Nongli2Gongli(short sLunarYear,unsigned short wLunarMonth,unsigned short wLunarDay,BOOL bLeapMonth,short* sYear,unsigned short* wMonth,unsigned short* wDay);

//�õ�ָ����ݵĽ�����Ϣ���׸���С��
BOOL GetJieQi(short sYear,unsigned short wMonth,unsigned short wJieQi[2]);

//�������ڣ�����-1��ʾ����������ղ���ȷ���߳�����ݷ�Χ
unsigned short GetDayOfWeek(short sYear,unsigned short wMonth,unsigned short wDay);

//����ĳ���µ������������������������0��ʾ���������
unsigned short GetDaysOfMonth(short sYear,unsigned short wMonth);

//�������ռ�������ʾ�������������ꡢ�����¡�������
unsigned short G_HolidayShow(short sYear,unsigned short wMonth,unsigned short wDay);

//ũ�����ռ�������ʾ��������ũ���ꡢũ���¡�ũ���ա�ũ������
BOOL L_HolidayShow(int sLYear,int iLMonth,int iLDay,int iLeapMonth);

//��ѯĳһ������ż������������������ꡢ��һ�궬������һ�ţ���������ĩ��
BOOL GetExtremeSeason(short sYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu);

//��ѯĳһ�����÷����÷�������������꣬��÷����÷
BOOL GetMeiYu(short sYear,unsigned short* wRuMeiOrd,unsigned short* wChuMeiOrd);

//===============================================================================

BOOL IsLeapYear(short sYear)
{
	if (sYear<1600||sYear>=6400)//ѹ���㷨�涨�˵�������䣨��ȡ��ֻ�ܵ�������������ݣ�Lunar.dll֧��-6000��20000������20000��֮�����ݣ�
	{
		return E_FAIL;
	}
	if (sYear%4==0&&sYear%100!=0||sYear%400==0)//�ж����������
	{
		return TRUE;
	}else
	{
		return FALSE;
	}
}

BOOL GetDayOrdinal(short sYear, unsigned short wMonth, unsigned short wDay,int *nDays)
{
	//�������������Ԫ��������
	int ret=0;
	if (DateCheck(sYear,wMonth,wDay)==0)//����������ڽ��м��
	{
		return 0;
	}
	ret=IsLeapYear(sYear);//�ж��Ƿ�Ϊ����
	if (ret==-1)
	{
		return 0;
	}
	if (ret==1)
	{
		*nDays=DayOrdinalLeap[wMonth-1]+wDay-1;//Ԫ��Ϊ����0����˼�1
	}else
	{
		*nDays=DayOrdinal[wMonth-1]+wDay-1;
	}
	return 1;
}

BOOL GetDateFromOrdinal(short sYear,short sOrdinal,unsigned short* wMonth,unsigned short* wDay)
{
	//������������������
	int ret=0,i=0;
	if (sOrdinal<0)
	{
		return FALSE;
	}
	ret=IsLeapYear(sYear);
	if (ret==1)
	{
		if (sOrdinal>=366)//�����˸����������
		{
			return FALSE;
		}
	}else
	{
		if (sOrdinal>=365)
		{
			return FALSE;
		}
	}
	if (ret!=-1)
	{
		//����ϣ������;
		*wMonth=0;
		for (i=0;i<12;i++)
		{
			if (ret==1)
			{
				if (sOrdinal>=DayOrdinalLeap[i]&&sOrdinal<DayOrdinalLeap[i+1])//�ҳ��·�
				{
					*wMonth=i+1;
					*wDay=sOrdinal-DayOrdinalLeap[i]+1;//��������ա�
					break;
				}
			}else
			{
				if (sOrdinal>=DayOrdinal[i]&&sOrdinal<DayOrdinal[i+1])
				{
					*wMonth=i+1;
					*wDay=sOrdinal-DayOrdinal[i]+1;
					break;
				}
			}
		}
	}else
	{
		*wDay=0;
		*wMonth=0;
		return FALSE;
	}
	return TRUE;
}

BOOL DateCheck(short sYear,unsigned short wMonth,unsigned short wDay)
{
	if (sYear<START_YEAR||sYear>=END_YEAR||wMonth>12||wMonth<1||wDay<1||wDay>31)
	{
		return 0;
	}
	if (wMonth==4||wMonth==6||wMonth==9||wMonth==11)
	{
		if (wDay==31)
		{
			return 0;
		}
	}else if (wMonth==2)
	{
		if (IsLeapYear(sYear)==0)
		{
			if (wDay>28)
			{
				return 0;
			}
		}else
		{
			if (wDay>29)
			{
				return 0;
			}
		}
	}
	return 1;
}

short LunarGetNewYearOrdinal(short sLunarYear)
{
	unsigned int uData=0;
	if (GetMonthInfo(sLunarYear,&uData)==FALSE)
	{
		return 0;
	}
	return (short)((uData>>17)&0x3F);//ȡ��ũ���������������
}

unsigned short LunarGetDaysofMonth(short sLunarYear,unsigned short wLunarMonth,BOOL bLeapMonth)
{
	int i=0;//ѭ������
	unsigned int DX_data=0;//�����С�����
	unsigned int uData=0;
	int Acc_LeapMonth=0;
	if (sLunarYear==START_YEAR-1)//ũ��������ʼ��ݵ�ǰһ��
	{
		if (cPreLeapIndex==-1)//������
		{
			if (bLeapMonth==TRUE)
			{
				return 0;
			}
			return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
		}else
		{
			Acc_LeapMonth=cPreLeapIndex+9;
			if (Acc_LeapMonth>wLunarMonth)
			{
				if (bLeapMonth==TRUE)
				{
					return 0;
				}
				return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
			}else
			{
				if ((bLeapMonth==TRUE&&wLunarMonth==Acc_LeapMonth)||wLunarMonth>Acc_LeapMonth)
				{
					return cPreMonth[wLunarMonth-8]-cPreMonth[wLunarMonth-9];
				}else
				{
					return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
				}
			}
		}
	}
	if (GetMonthInfo(sLunarYear,&uData)==FALSE)
	{
		return 0;
	}
	DX_data=(unsigned short)(uData&0x1FFF);//�����С�����
	Acc_LeapMonth=LunarGetLeapMonth(sLunarYear);//��ȡ��ʵ�����·�
	if (bLeapMonth)//ָ����ѯ�ĵ�ǰ��������
	{
		if (Acc_LeapMonth!=wLunarMonth)
		{
			return 0;//�����ڵ�����
		}
		for (i=0;i<wLunarMonth;i++)
		{
			DX_data>>=1;//����һλ������ĩβ��ʼ�Ҹ������·����ڵ�λ
		}
	}else
	{
		if (Acc_LeapMonth>0)//��������
		{
			if (wLunarMonth<=Acc_LeapMonth)//�·�������֮ǰ��������Ҫ����һλ
			{
				for (i=0;i<wLunarMonth-1;i++)
				{
					DX_data>>=1;
				}
			}else
			{
				for (i=0;i<wLunarMonth;i++)//�·�������֮��
				{
					DX_data>>=1;
				}
			}
		}else
		{
			for (i=0;i<wLunarMonth-1;i++)//������
			{
				DX_data>>=1;
			}
		}
	}
	if (DX_data&0x1)
	{
		return 30;//����
	}else
	{
		return 29;//С��
	}
}

BOOL LunarExpandDX(short sLunarYear,int iDayOfMonth[15])
{
	int i=0,pos=0,iLeapMonth=0;//ѭ������������д��λ�ã�����
	if (sLunarYear<START_YEAR||sLunarYear>=END_YEAR)
	{
		return FALSE;
	}
	for (i=0;i<15;i++)
	{
		iDayOfMonth[i]=0;//����������
	}
	if (sLunarYear==START_YEAR)
	{
		if (cPreLeapIndex==-1)//������ʼ���֮ǰһ������
		{
			iDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];//ũ����һ��ʮһ��������
			pos++;
		}else
		{
			if (cPreLeapIndex==1)//��ʮ��
			{
				iDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
				pos++;
			}else
			{
				//��ʮһ�»���ʮ����
				iDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];
				pos++;
				iDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
				pos++;
			}
		}
		iDayOfMonth[pos]=LunarGetNewYearOrdinal(sLunarYear)-cPreMonth[2];//����ʮ����
		pos++;
	}else
	{
		iLeapMonth=LunarGetLeapMonth(sLunarYear-1);//ȡ��ǰһũ������������
		if (iLeapMonth<11)//һ����ʮ�µ�����
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,0);//ȡ��һ��ʮһ������
			pos++;
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//ȡ��һ��ʮ��������
			pos++;
		}else
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,0);//ȡ��һ��ʮһ�µ�����
			pos++;
			if (iLeapMonth==11)//��ʮһ��
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,1);//ȡ��һ����ʮһ�µ�����
				pos++;
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//ȡ��һ��ʮ��������
				pos++;
			}else if (iLeapMonth==12)
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//ȡ��һ��ʮ��������
				pos++;
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,1);//ȡ��һ����ʮ��������
				pos++;
			}
		}
	}
	iLeapMonth=LunarGetLeapMonth(sLunarYear);//��ȡ��ǰũ������������
	if (iLeapMonth==0)//������
	{
		for (i=0;i<12;i++)
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i+1,0);//ȡÿ��ũ��������
			pos++;
		}
	}else
	{
		for (i=0;i<12;i++)
		{
			if (i==iLeapMonth)
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i,1);//ȡ���µ�����
				pos++;
			}
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i+1,0);//ȡ�����µ�����
			pos++;
		}
	}
	return TRUE;
}

BOOL GetMonthInfo(unsigned short wYear,unsigned int* puData)
{
	int iStartPos=(wYear-START_YEAR)*3;
	unsigned int uData=0;
	if (wYear<START_YEAR||wYear>=END_YEAR)
	{
		return FALSE;
	}
	uData=byMonthInfo[iStartPos];
	uData<<=8;
	uData|=byMonthInfo[iStartPos+1];
	uData<<=8;
	uData|=byMonthInfo[iStartPos+2];
	if (puData)
	{
		*puData=uData;
	}
	return TRUE;
}

unsigned short LunarGetLeapMonth(short sLunarYear)
{
	unsigned int data=0;
	unsigned short wLeapMonth=0;
	if (GetMonthInfo(sLunarYear,&data)==FALSE)
	{
		return 0;
	}
	wLeapMonth=(unsigned short)((data>>13)&0x0F);
	return wLeapMonth;
}

BOOL Gongli2Nongli(short sYear,unsigned short wMonth,unsigned short wDay,short* sLunarYear,unsigned short* wLunarMonth,unsigned short* wLunarDay,BOOL* bLeapMonth)
{
	int DaysNum=0,LunarNewYear=0,i=0,remain_days=0;//����������ũ������Ĺ�������������ѭ��������ʣ������
	int DaysOfLunarMonth[15]={0};//���ũ���·�����
	int iLeapMonthPre=0,iLeapMonth=0;//ũ����һ�����£���������
	int ret=GetDayOrdinal(sYear,wMonth,wDay,&DaysNum);
	if (ret==0)
	{
		return 0;//���ڲ���ȷ
	}
	*sLunarYear=sYear;
	LunarNewYear=LunarGetNewYearOrdinal(*sLunarYear);
	LunarExpandDX(*sLunarYear,DaysOfLunarMonth);//��ȡ�·��������������һ��ʮһ�¿�ʼ�����꣨��ʮ���£���������
	iLeapMonthPre=LunarGetLeapMonth(*sLunarYear-1);
	if (iLeapMonthPre==0)
	{
		iLeapMonth=LunarGetLeapMonth(*sLunarYear);//��һ��û�����£����ѯ��������
	}
	*bLeapMonth=FALSE;
	remain_days=DaysNum-LunarNewYear;//����ũ����������
	if (iLeapMonthPre>10)
	{
		i=3;//���������ڡ�DaysOfLunarMonth���е���������һ��ʮһ�»�ʮ����������
	}else
	{
		i=2;//��һ��ʮһ�º�ʮ����������ʱ���������µ�����
	}
	if (LunarNewYear>DaysNum)//����ũ������
	{
		*sLunarYear-=1;//ũ�����1
		while(remain_days<0)
		{
			i--;//��һ���ȼ�ȥ����Ϊ��ǰi�����£���1��ʾ��һ��ʮ���£�����ʮ���£�
			remain_days+=DaysOfLunarMonth[i];//������һ��ʮ���¡�ʮһ�µ��������������£�ֱ����������0
		}
		if (iLeapMonthPre>10)//�����һ��ʮһ�»�ʮ���´�������
		{
			if (iLeapMonthPre==11)//��ʮһ��
			{
				if (i==0)//ʮһ�£���������֮ǰ��
				{
					*wLunarMonth=11+i;//ת�����·�
				}else
				{
					*wLunarMonth=10+i;
					if (*wLunarMonth==iLeapMonthPre)
					{
						*bLeapMonth=TRUE;
					}
				}
			}else if (iLeapMonthPre==12)//��ʮ����
			{
				if (i<2)//������֮ǰ
				{
					*wLunarMonth=11+i;
				}else
				{
					*wLunarMonth=10+i;
					if (*wLunarMonth==iLeapMonthPre)
					{
						*bLeapMonth=TRUE;
					}
				}
			}
		}else
		{
			*wLunarMonth=11+i;
		}
		*wLunarDay=remain_days;
	}else
	{
		while (remain_days>=DaysOfLunarMonth[i])
		{
			remain_days-=DaysOfLunarMonth[i];//Ѱ��ũ����
			i++;//�����¸���
		}
		if (iLeapMonthPre>10)
		{
			*wLunarMonth=i-2;
		}else
		{
			if (iLeapMonth>0)
			{
				if (i-2<iLeapMonth)
				{
					*wLunarMonth=i-1;
				}else
				{
					*wLunarMonth=i-2;
					if (*wLunarMonth==iLeapMonth)
					{
						*bLeapMonth=TRUE;
					}
				}
			}else
			{
				*wLunarMonth=i-1;
			}
		}
		*wLunarDay=remain_days;
	}
	*wLunarDay+=1;//����ת��������
	return TRUE;
}

BOOL Nongli2Gongli(short sLunarYear,unsigned short wLunarMonth,unsigned short wLunarDay,BOOL bLeapMonth,short* sYear,unsigned short* wMonth,unsigned short* wDay)
{
 	int DaysOfLunarMonth[15]={0};//���ũ���·�����
 	int iLeapMonthPre=0,iLeapMonth=0;//ũ��������
 	int LunarNewYear=0,i=0,remain_days=0;//����������ũ������Ĺ�������������ѭ��������ʣ������
 	int iDaysofYear=0;
 	if (sLunarYear<START_YEAR||sLunarYear>=END_YEAR||wLunarMonth<1||wLunarMonth>12||wLunarDay<1||wLunarDay>30)
 	{
 		return FALSE;//�ꡢ�¡��ռ��
 	}
 	if (bLeapMonth)
 	{
 		if (LunarGetLeapMonth(sLunarYear)!=wLunarMonth)
 		{
 			return FALSE;//���¼��
 		}
 	}
 	if (wLunarDay>LunarGetDaysofMonth(sLunarYear,wLunarMonth,bLeapMonth))
 	{
 		return FALSE;//��С�¼��
 	}
 	LunarExpandDX(sLunarYear,DaysOfLunarMonth);//��С�±�ũ��ÿ��������
 	LunarNewYear=LunarGetNewYearOrdinal(sLunarYear);//�ҵ����³�һ�Ĺ�����������
 	iLeapMonth=LunarGetLeapMonth(sLunarYear);//�ҳ�ũ���������
 	remain_days+=LunarNewYear;//�������³�һ������
 	if (iLeapMonthPre>10)
 	{
 		i=3;//���������ڡ�DaysOfLunarMonth���е���������һ��ʮһ�»�ʮ����������
 	}else
 	{
 		i=2;//��һ��ʮһ�º�ʮ����������ʱ���������µ�����
 	}
 	if (iLeapMonth==0)
 	{
 		if (iLeapMonthPre>10)
 		{
 			for (;i<wLunarMonth+2;i++)
 			{
 				remain_days+=DaysOfLunarMonth[i];//���������ۼ�
 			}
 		}else
 		{
 			for (;i<wLunarMonth+1;i++)
 			{
 				remain_days+=DaysOfLunarMonth[i];//���������ۼ�
 			}
 		}
 	}else
 	{
 		if (wLunarMonth<iLeapMonth||(bLeapMonth==FALSE&&wLunarMonth==iLeapMonth))//������֮ǰ
 		{
 			for (;i<wLunarMonth+1;i++)
 			{
 				remain_days+=DaysOfLunarMonth[i];
 			}
 		}else
 		{
 			for (;i<wLunarMonth+2;i++)
 			{
 				remain_days+=DaysOfLunarMonth[i];
 			}
 		}
 	}
 	remain_days+=wLunarDay-1;//��1����Ϊ����ת������
 	GetDayOrdinal(sLunarYear,12,31,&iDaysofYear);//��ȡ������������
 	iDaysofYear++;//������ת������
 	*sYear=sLunarYear;
 	if ((remain_days+1)>iDaysofYear)
 	{
 		remain_days-=iDaysofYear;
 		*sYear+=1;//��һ��
 	}
 	GetDateFromOrdinal(*sYear,remain_days,wMonth,wDay);
	return TRUE;
}

BOOL GetJieQi(short sYear,unsigned short wMonth,unsigned short wJieQi[2])
{
	int index=0;//��Ӧÿ�������׸����������ֽڵ�����
	unsigned short wXiaoHanOrder=0;//С����������
	unsigned short wJQData=0;//��������
	unsigned short wCurJQData=0;//��ǰ����Ľ�������
	unsigned short wDays=0;//��ǰ�����������С��������
	int i=0;
	int iRem=0;
	if (sYear<START_YEAR||sYear>=END_YEAR||wMonth>12||wMonth<1)
	{
		return FALSE;
	}
	index=(sYear-START_YEAR)*3;//��Ӧÿ�������׸����������ֽڵ�����
	wJQData=wSTSource[bySTIndex[index]];
	wXiaoHanOrder=(unsigned short)((wJQData>>14)+3);//����3��תΪС������������
	wCurJQData=(wJQData>>12)&0x03;//��ǰ����Ľ�������һ��������������Ϣ
	if (wMonth==1)
	{
		wJieQi[0]=wXiaoHanOrder+1;//��1ת������
		wJieQi[1]=wCurJQData+14+wXiaoHanOrder+1;//�󺮣�С���������������Ͼ���С��������
		return TRUE;
	}
	wDays=wCurJQData+14;//����С������������ǰΪ�󺮾���С��������
	wDays+=wXiaoHanOrder;//����С����תΪ��������
	for (i=1;i<wMonth;i++)
	{
		iRem=i%4;
		wCurJQData=(wJQData>>(18-((iRem+1)<<2)))&0x03;
		wDays+=wCurJQData+14;
		wCurJQData=(wJQData>>(16-((iRem+1)<<2)))&0x03;
		wDays+=wCurJQData+14;
		if (iRem==3)
		{
			wJQData=wSTSource[bySTIndex[index+(i+1)/4]];
		}
	}
	GetDateFromOrdinal(sYear,wDays,&wMonth,&wJieQi[1]);//wMonth�еĵڶ�������
	GetDateFromOrdinal(sYear,wDays-wCurJQData-14,&wMonth,&wJieQi[0]);//��һ������
	return TRUE;
}

unsigned short GetDayOfWeek(short sYear,unsigned short wMonth,unsigned short wDay)
{
	unsigned int DayofWeek=0;
	int uDayOrd=0;
	if (GetDayOrdinal(sYear,wMonth,wDay,&uDayOrd)==0)
	{
		return 0;
	}
	uDayOrd++;//һ���еĵڼ��죬��ΪGetDayOrdinal���õ��������������Ҫ��һ
	sYear--;
	DayofWeek=(sYear+sYear/4-sYear/100+sYear/400+uDayOrd)%7;//���ֻ�������ڵ�ͨ�ù�ʽ
	return DayofWeek;
}

unsigned short GetDaysOfMonth(short sYear,unsigned short wMonth)
{
	int days1=0,days2=0;
	int ret=0;
	if (wMonth==12)
	{
		return 31;//����Ϊ�˼�㣬�ж�12�¾�ֱ�ӷ���
	}
	ret=GetDayOrdinal(sYear,wMonth,1,&days1);//����1�������ڵ�����
	if (ret==0)
	{
		return ret; 
	}
	wMonth++;
	ret=GetDayOrdinal(sYear,wMonth,1,&days2);//�¸���1�յ���������
	if (ret==0)
	{
		return ret; 
	}
	ret=days2-days1;//�¸���1�յ�����������1�յ�����
	return ret;
}

BOOL GetExtremeSeason(short sYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu)
{
	unsigned short wjq[2]={0};
	int ET_index=sYear-START_YEAR;//���š�÷�꼰�������������
	if (sYear<START_YEAR||sYear>=END_YEAR)
	{
		return FALSE;
	}
	if (sYear==START_YEAR)
	{
		*sYijiu=cPreDongzhiOrder;
	}else
	{
		GetJieQi(sYear-1,12,wjq);
		*sYijiu=wjq[1]-32;
	}
	*wChuFu=((wExtermSeason[ET_index]&0x3E)>>1)+180;
	*wMoFu=(*wChuFu)+((wExtermSeason[ET_index]&0x01)==1?30:20);
	return TRUE;
}

BOOL GetMeiYu(short sYear,unsigned short* wRuMeiOrd,unsigned short* wChuMeiOrd)
{
	int ET_index=sYear-START_YEAR;//���š�÷�꼰�������������
	if (sYear<START_YEAR||sYear>=END_YEAR)
	{
		return FALSE;
	}
	*wRuMeiOrd=((wExtermSeason[ET_index]&0xF800)>>11)+150;
	*wChuMeiOrd=((wExtermSeason[ET_index]&0x07C0)>>6)+180;
	return TRUE;
}

BOOL ShowCalendar(short sYear,unsigned short wMonth)
{
	//Ҫ��ʾһ���µ������������¼���Ҫ�㣺
	//1.����1�յ�����
	//2.���µ�������
	//3.����1�ն�Ӧ��ũ���Լ�ũ���´�С����ʱ������Ҫ֪���¸����������¸��µĴ�С
	int iDayofweek_1st=0;//����1������
	short sNYear=0;
	unsigned short wNMonth=0,wNDay=0;//ũ���ꡢ�¡���
	BOOL bNLeapMonth=FALSE;//���±�־
	int iDaysofmonth=0;//������������
	int iNDaysofmonth=0;//ũ����������
	int iPos=0,iGDayIdx=1,iNDayIdx=0,iNindex=1;//���λ�á������գ�ũ���գ�ũ�����������ͬ��iDaysofmonth��
	int iFillFlag=0;//����־��0Ϊ����������䣬1Ϊũ��������䣬2Ϊ������䣬3Ϊũ�����
	iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��1�յ�����
	if (iDayofweek_1st==-1)
	{
		return FALSE;//������������
	}
	iDaysofmonth=GetDaysOfMonth(sYear,wMonth);//�õ�����������
	Gongli2Nongli(sYear,wMonth,1,&sNYear,&wNMonth,&wNDay,&bNLeapMonth);//�õ�����1�յ�ũ��
	iNDaysofmonth=LunarGetDaysofMonth(sNYear,wNMonth,bNLeapMonth);//�õ�ũ����������
	iNDayIdx=wNDay;//ȡ��ũ����
	if (iNDaysofmonth==0)
	{
		return FALSE;
	}
	printf("\t\t%d��%d�� ũ�� ",sYear,wMonth);
	if (bNLeapMonth==1)
	{
		printf("��");
	}
	if (iNDaysofmonth==29)
	{
		printf("%s��С��\n\n",Yueming[wNMonth-1]);
	}else if (iNDaysofmonth==30)
	{
		printf("%s����\n\n",Yueming[wNMonth-1]);
	}
	for (iPos=0;iPos<7;iPos++)
	{
		printf("%s\t",Xingqi[iPos]);
	}
	printf("\n_______________________________________________________\n\n");
	iPos=0;
	while (iNindex<=iDaysofmonth)
	{
		if (iFillFlag==0||iFillFlag==2)
		{
			if (iFillFlag==0)
			{
				while(iPos<iDayofweek_1st)//ֱ�����������
				{
					printf("\t");
					iPos++;//λ������
				}
			}
			if (G_HolidayShow(sYear,wMonth,iGDayIdx)==0)
			{
				printf("  %2d\t",iGDayIdx);//���ũ��
			}
			iPos++;
			iGDayIdx++;
			if (iGDayIdx>iDaysofmonth)
			{
				printf("\n");
				iPos=0;//λ�����»ص���ʼ
				iFillFlag=3;
			}else
			{
				if (iPos==7)//���Ҫ������
				{
					printf("\n");
					iPos=0;//λ�����»ص���ʼ
					if (iFillFlag==0)
					{
						iFillFlag=1;//�л���ũ���������
					}else
					{
						iFillFlag=3;
					}
				}
			}
		}else if (iFillFlag==1||iFillFlag==3)
		{
			if (iFillFlag==1)
			{
				while(iPos<iDayofweek_1st)//ֱ�����������
				{
					printf("\t");
					iPos++;//λ������
				}
			}
			
			if (iNDayIdx<=iNDaysofmonth)
			{
				if (L_HolidayShow(sNYear,wNMonth,iNDayIdx,bNLeapMonth)==0)
				{
					if (iNDayIdx==1)
					{
						printf(" %s",Yueming[wNMonth-1]);//��������Ϊũ������
						if (iNDaysofmonth==30)
						{
							printf("��\t");
						}else
						{
							printf("С\t");
						}
					}else
					{
						printf(" %s\t",Riming[iNDayIdx-1]);//û�н��ա��������������ʱ�����ũ������
					}
				}
			}else
			{
				Gongli2Nongli(sYear,wMonth,iNindex,&sNYear,&wNMonth,&wNDay,&bNLeapMonth);//���ũ����һ����
				iNDaysofmonth=LunarGetDaysofMonth(sNYear,wNMonth,bNLeapMonth);//���µõ�ũ����������
				iNDayIdx=wNDay;
				if (L_HolidayShow(sNYear,wNMonth,iNDayIdx,bNLeapMonth)==0)
				{
					//û�н��ա��������������ʱ�����ũ������
					if (bNLeapMonth==1)
					{
						printf("��");
					}
					printf("%s",Yueming[wNMonth-1]);
					if (iNDaysofmonth==29)
					{
						printf("С");
					}else if (iNDaysofmonth==30)
					{
						printf("��");
					}
					if (bNLeapMonth==0)
					{
						printf("\t");
					}
				}
			}
			iPos++;
			iNDayIdx++;//ũ��������
			iNindex++;//ũ���������������
			if (iPos==7)
			{
				if (!(iGDayIdx>=iDaysofmonth&&(iDaysofmonth+iDayofweek_1st)%7==0))
				{
					printf("\n\n");
				}
				iPos=0;
				iFillFlag=2;
			}
		}
	}
	printf("\n_______________________________________________________\n\n");
	return TRUE;
}

unsigned short G_HolidayShow(short sYear,unsigned short wMonth,unsigned short wDay)
{
	unsigned short wJQ_date[2]={0};//�������
	int iDayOrdial=0;//���ڵ���������
	int ET_index=sYear-START_YEAR;//���š�÷�꼰�������������
	int iDayofweek_1st=0;//��������
	int iDongzhi=0;//����
	unsigned short wrumei=0,wchumei=0,wchufu=0,wmofu=0;
	short sshujiu=0;
	int i=0;
	if (GetJieQi(sYear,wMonth,wJQ_date)==1)
	{
		if (wJQ_date[0]==wDay)
		{
			printf(" %s\t",Jieqi[((wMonth<<1)+20)%24]);//���µ�һ������
			return 1;
		}else if (wJQ_date[1]==wDay)
		{
			printf(" %s\t",Jieqi[((wMonth<<1)+21)%24]);//���µڶ�������
			return 1;
		}
	}
	GetDayOrdinal(sYear,12,wJQ_date[1],&iDongzhi);//ת������������
	if (GetDayOrdinal(sYear,wMonth,wDay,&iDayOrdial))
	{
		/*if (iDayOrdial==wExtermSeason[ET_index+5])
		{
			printf_s("[%s]\t",Shujiu[0]);//һ�ţ�������������Ҫ�ж��ˣ����涬���Ѿ���������ˣ�
			return 1;
		}else */
		GetExtremeSeason(sYear,&sshujiu,&wchufu,&wmofu);
		GetMeiYu(sYear,&wrumei,&wchumei);
		if (iDayOrdial==iDongzhi+9)
		{
			printf("[%s]\t",Shujiu[1]);//����
			return 2;
		}
		if (iDayOrdial>=(sshujiu+9)&&iDayOrdial<sshujiu+81)
		{
			for (i=0;i<8;i++)
			{
				if (iDayOrdial==sshujiu+(i+1)*9)
				{
					printf("[%s]\t",Shujiu[i+1]);//�������ž�
					return 1;
				}
			}
		}else if (iDayOrdial==wrumei)
		{
			printf("[%s]\t",Meiyu[0]);//��÷
			return 1;
		}else if (iDayOrdial==wchumei)
		{
			printf("[%s]\t",Meiyu[1]);//��÷
			return 1;
		}else if (iDayOrdial==wchufu)
		{
			printf("[%s]\t",Sanfu[0]);//����
			return 1;
		}else if (iDayOrdial==wchufu+10)
		{
			printf("[%s]\t",Sanfu[1]);//�з�
			return 1;
		}else if (iDayOrdial==wmofu)
		{	printf("[%s]\t",Sanfu[2]);//ĩ��
			return 1;
		}
	}
	if (wMonth==1)
	{
		if (wDay==1)
		{
			printf(" Ԫ��\t");
			return 1;
		}
	}else if (wMonth==2)
	{
		if (wDay==14)
		{
			printf("���˽�\t");
			return 1;
		}
	}else if (wMonth==3)
	{
		switch (wDay)
		{
		case 5:
			if (sYear>=1963)
			{
				printf("ѧ�׷���");
				return 1;
			}
			break;
		case 8:
			if (sYear>=1900)
			{
				printf("��Ů��\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1928)
			{
				printf("ֲ����\t");
				return 1;
			}
			break;
		case 15:
			if (sYear>=1983)
			{
				printf("��Ȩ��\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==4)
	{
		if (wDay==1)
		{
			printf("���˽�\t");
			return 1;
		}
	}else if (wMonth==5)
	{
		if (sYear>=1872)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��������
			if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==2)//5�µڶ�������ĸ�׽�
			{
				printf("ĸ�׽�\t");
				return 1;
			}
		}
		switch (wDay)
		{
		case 1:
			if (sYear>=1890)
			{
				printf("�Ͷ���\t");
				return 1;
			}
			break;
		case 4:
			if (sYear>=1919)
			{
				printf("�����\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1912)
			{
				printf("��ʿ��\t");
				return 1;
			}
			break;
		case 31:
			if (sYear>=1989)
			{
				printf("������\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==6)
	{
		if (sYear>=1910)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��������
			if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==3)//6�µ��������ո��׽�
			{
				printf("���׽�\t");
				return 1;
			}
		}
		switch (wDay)
		{
		case 1:
			if (sYear>1949)
			{
				printf("��ͯ��\t");
				return 1;
			}
			break;
		case 5:
			if (sYear>=1972)
			{
				printf("������\t");
				return 1;
			}
			break;
		case 26:
			if (sYear>=1987)
			{
				printf("������\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==7)
	{
		switch (wDay)
		{
		case 1:
			if (sYear>=1921)
			{
				printf("�й�����");
				return 1;
			}
			break;
		case 7:
			if (sYear>=1937)
			{
				printf("��ս����");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==8)
	{
		if (wDay==1)
		{
			if (sYear>=1933)
			{
				printf("������\t");
				return 1;
			}
		}
	}else if (wMonth==9)
	{
		switch (wDay)
		{
		case 3:
			if (sYear>=1945)
			{
				printf("��սʤ��");
				return 1;
			}
			break;
		case 10:
			if (sYear>=1985)
			{
				printf("��ʦ��\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==10)
	{
		if (wDay==1)
		{
			if (sYear>=1949)
			{
				printf(" ����\t");
				return 1;
			}
		}
	}else if (wMonth==11)
	{
		if (sYear>=1941)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��������
			if ((wDay+iDayofweek_1st-1)%7==4&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==4?7:0))/7)==4)//11�µ��ĸ����ĸж���
			{
				printf("�ж���\t");
				return 1;
			}
		}
		if (wDay==1)
		{
			printf("��ʥ��\t");
			return 1;
		}
	}else if (wMonth==12)
	{
		switch (wDay)
		{
		case 10:
			if (sYear>=1948)
			{
				printf("��Ȩ��\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1936)
			{
				printf("�����±�");
				return 1;
			}
			break;
		case 24:
			printf("ƽ��ҹ\t");
			return 1;
		case 25:
			printf("ʥ����\t");
			return 1;
		default:
			break;
		}
	}
	return 0;
}

BOOL L_HolidayShow(int sLYear,int iLMonth,int iLDay,int iLeapMonth)
{
	int LeapMonth=LunarGetLeapMonth(sLYear);//ȡ����ũ������
	int DayofLM_12=0;//ũ��ʮ���µ�������
	if (iLeapMonth==0)
	{
		if (iLMonth==1)
		{
			switch (iLDay)
			{
			case 1:
				printf(" ����\t");
				return TRUE;
			case 15:
				printf("Ԫ����\t");
				return TRUE;
			default:
				break;
			}
		}else if (iLMonth==2)
		{
			if (iLDay==2)
			{
				printf("������\t");
				return TRUE;
			}
		}else if (iLMonth==5)
		{
			if (iLDay==5)
			{
				printf("�����\t");
				return TRUE;
			}
		}else if (iLMonth==7)
		{
			if (iLDay==7)
			{
				printf(" ��Ϧ\t");
				return TRUE;
			}else if (iLDay==15)
			{
				printf("��Ԫ��\t");
				return TRUE;
			}
		}else if (iLMonth==8)
		{
			if (iLDay==15)
			{
				printf("�����\t");
				return TRUE;
			}
		}else if (iLMonth==9)
		{
			if (iLDay==9)
			{
				printf("������\t");
				return TRUE;
			}
		}else if (iLMonth==10)
		{
			if (iLDay==1)
			{
				printf("�����\t");
				return TRUE;
			}else if (iLDay==15)
			{
				printf("��Ԫ��\t");
				return TRUE;
			}
		}else if (iLMonth==12)
		{
			if (LeapMonth!=12)
			{
				DayofLM_12=LunarGetDaysofMonth(sLYear,12,0);//����ʮ����
				if (iLDay==8)
				{
					printf("���˽�\t");
					return TRUE;
				}else if (iLDay==23)
				{
					printf(" С��\t");
					return TRUE;
				}else if (iLDay==DayofLM_12)//ũ��ʮ���µ����һ���ǳ�Ϧ
				{
					printf(" ��Ϧ\t");
					return TRUE;
				}
			}
		}
	}else
	{
		if (iLeapMonth==LeapMonth)
		{
			if (iLeapMonth==12)
			{
				DayofLM_12=LunarGetDaysofMonth(sLYear,12,1);//��ʮ����
				if (iLDay==8)
				{
					printf("���˽�\t");
					return TRUE;
				}else if (iLDay==23)
				{
					printf(" С��\t");
					return TRUE;
				}else if (iLDay==DayofLM_12)//ũ��ʮ���µ����һ���ǳ�Ϧ
				{
					printf(" ��Ϧ\t");
					return TRUE;
				}
			}
		}
	}
	return FALSE;//û�н��յ�
}

void ShowMenu()
{
	printf("**************************************\n");
	printf("*                                    *\n");
	printf("*             ��������ѯ             *\n");
	printf("*                                    *\n");
	printf("*    %d����%d�꣨����%d�꣩    *\n",START_YEAR,END_YEAR,END_YEAR);
	printf("*                                    *\n");
	printf("**************************************\n");
	printf("\n\n");
	printf("��1. ������ʾ\n��2. ����תũ��\n��3. ũ��ת����\n��4. ������ѯ\n\n\n");
	printf("��ѡ��");
}

void GL2NL()
{
	unsigned short wMonth=0,wDay=0,iLMonth=0,iLDay=0,iDayofweek=0;
	short sYear=0,sLYear=0;
	BOOL bLLeapMonth=FALSE;
	int ret=0;
	system("cls");
	printf("��2. ����תũ��\n\n");
	do 
	{
		printf("�����빫�����ڣ��� �� �գ�>");
		scanf("%d %d %d",&sYear,&wMonth,&wDay);
		iDayofweek=GetDayOfWeek(sYear,wMonth,wDay);
		ret=Gongli2Nongli(sYear,wMonth,wDay,&sLYear,&iLMonth,&iLDay,&bLLeapMonth);
		if (ret==0)
		{
			printf("\n������������");
		}
	} while (ret==0);
	if (bLLeapMonth)
	{
		printf("%d��%d��%d��תΪũ��Ϊ��%s%s��%s���� ��%s %s",sYear,wMonth,wDay,Tiangan[(sLYear - 4)%10],Dizhi[(sLYear - 4)%12],Shengxiao[(sLYear - 4)%12],Yueming[iLMonth-1],Riming[iLDay-1]);
	}else
	{
		printf("%d��%d��%d��תΪũ��Ϊ��%s%s��%s���� %s %s",sYear,wMonth,wDay,Tiangan[(sLYear - 4)%10],Dizhi[(sLYear - 4)%12],Shengxiao[(sLYear - 4)%12],Yueming[iLMonth-1],Riming[iLDay-1]);
	}
	printf("  %s\n\n",Xingqi[iDayofweek]);
	system("pause");
	system("cls");
}

void NL2GL()
{
	unsigned int wMonth=0,wDay=0,iLMonth=0,iLDay=0,iDayofweek=0;
	int sYear=0,sLYear=0;
	BOOL bLLeapMonth=FALSE;
	int ret=0;
	system("cls");
	printf("��3. ũ��ת����\n\n");
	do 
	{
		printf("������ũ�������Լ��Ƿ����£�������1��ʾ����������0��ʾ����\n�� �� �� �Ƿ����£�>");
		scanf("%d %d %d %d",&sLYear,&iLMonth,&iLDay,&bLLeapMonth);
		ret=Nongli2Gongli(sLYear,iLMonth,iLDay,bLLeapMonth,(short *)&sYear,(unsigned short *)&wMonth,(unsigned short *)&wDay);
		if (ret==0)
		{
			printf("\n������������");
		}
	} while (ret==0);
	if (bLLeapMonth)
	{
		printf("ũ�� %d�� ��%s %s תΪ����Ϊ %d��%d��%d��\n\n",sLYear,Yueming[iLMonth-1],Riming[iLDay-1],sYear,wMonth,wDay);
	}else
	{
		printf("ũ�� %d�� %s %s תΪ����Ϊ %d��%d��%d��\n\n",sLYear,Yueming[iLMonth-1],Riming[iLDay-1],sYear,wMonth,wDay);
	}
	system("pause");
	system("cls");
}

void RL()
{
	int iYear=0;
	int iMonth=0;
	BOOL ret=FALSE;
	system("cls");
	printf("��1. ������ʾ\n\n");
	do 
	{
		printf("�������ꡢ�£�Year Month>");
		scanf("%d %d",&iYear,&iMonth);
		ret=ShowCalendar(iYear,iMonth);
		ret=TRUE;
		if (ret==FALSE)
		{
			printf("\n������������");
		}
	} while (ret==FALSE);
	system("pause");
	system("cls");
}

void JQ()
{
	int i=0,ret=0;
	short sYear=0,sLYear=0;
	int iYear=0,iIndex=0;
	unsigned short wMonth=0,wLMonth=0,wDay=0,wLDay=0;
	BOOL bLeapMonth=FALSE;
	unsigned short JQ_date[3]={0};
	system("cls");
	printf("��4. ������ѯ\n\n");
	for (i=0;i<24;i++)
	{
		printf("% 2d. %s\t",i+1,Jieqi[i]);
		if (i%4==3)
		{
			printf("\n");
		}
	}
	printf("����������Լ�Ҫ��ѯ�Ľ�����ţ�Year Index>");
	scanf("%d %d",&iYear,&iIndex);
	wMonth=((iIndex+1)/2)%12+1;//ת�����·�
	sYear=(short)(iYear);
	do 
	{
		ret=GetJieQi(sYear,wMonth,JQ_date);//ȡָ���·ݽ���������������
		if (ret==0)
		{
			printf("���������������������Լ�Ҫ��ѯ�Ľ�����ţ�Year Index>");
			scanf("%d %d",&iYear,&iIndex);
			wMonth=((iIndex+1)/2)%12+1;
			sYear=(short)(iYear);
		}
	} while (ret==0);
	if ((iIndex%2)==1)
	{
		wDay=(int)JQ_date[0];//��һ������
	}else
	{
		wDay=(int)JQ_date[1];//�ڶ�������
	}
	if (Gongli2Nongli(sYear,wMonth,wDay,&sLYear,&wLMonth,&wLDay,&bLeapMonth)==0)//ת��ũ��
	{
		printf("��ѯũ��ʧ��\n");
	}else
	{
		printf("%d�� %s ʱ��Ϊ %d��%d�գ�ũ�� ",sYear,Jieqi[iIndex-1],wMonth,wDay);
		if (bLeapMonth==TRUE)//���������
		{
			printf("��");
		}
		printf("%d�� %s %s\n\n",sLYear,Yueming[wLMonth-1],Riming[wLDay-1]);
	}
	system("pause");
	system("cls");
}