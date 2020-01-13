//�ж����ڲ�
#include<stdio.h>
struct time{
	int year;
	int month;
	int day;
}date[2];
int JudgeLeapYear(int year)//�ж�����
{
	if((year%4==0&&year%100!=0)||(year%400==0))return 1;
	return 0;
}
int JudgeCorrect(time date)//�ж����������Ƿ����
{
	if(date.month<1||date.month>12||date.day<1)return 0;
	else{
		switch(date.month){
			case 1:case 3:case 5:case 7:case 8:case 10:case 12:{
				if(date.day>31)return 0;
				break;
			}
			case 2:{
				if((JudgeLeapYear(date.year)&&date.day>29)||((!JudgeLeapYear(date.year))&&date.day>28))
					return 0;
				break;
			}
			default:{
				if(date.day>30)return 0;
					break;
			}
		}
	}
	return 1;
}
int TimeDifference(time date1,time date2)//���ĺ��������������ڵĲ�ֵ
{
	int day[2]={date1.day,date2.day};
	int result=0;
	int monthdate[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	time tmp;
	//�жϵ�һ�������Ƿ�С�ڵڶ������ڣ����򽻻���������
	if(date1.year>date2.year||(date1.year==date2.year&&date1.month>date2.month)||(date1.year==date2.year&&date1.month==date2.month&&date1.day>date2.day))
	{
		tmp=date1;
		date1=date2;
		date2=tmp;
	}
	if(date1.year==date2.year){
		for(int i=date1.month;i<date2.month;i++)
		{
			if(i==2&&JudgeLeapYear(date1.year))result++;
			result+=monthdate[i];
		}
		result+=date2.day-date1.day;
	}
	else{
		//�ȷֱ�������������Ǹ���ĵڼ���
		for(int i=1;i<date1.month;i++)
		{
			if(i==2&&JudgeLeapYear(date1.year))day[0]++;
			day[0]+=monthdate[i];
		}
		for(int i=1;i<date2.month;i++)
		{
			if(i==2&&JudgeLeapYear(date2.year))day[1]++;
			day[1]+=monthdate[i];
		}
		result=day[1]-day[0];
		//�˴���forѭ���ĳ�ʼ�����У���һ��int�ͻᶨ��������еı���ֱ�������ֺţ�
		//����������result��ֵ������int i�Ĵ��ڣ����result�Զ�ת���ɾֲ�������
		//result�ڸô����ָ��������ʧ�����Ӧ��for֮ǰ�Ͷ�result���в���
		for(int i=date1.year;i<date2.year;i++)
		{
			if(JudgeLeapYear(i))result++;
			result+=365;
		}
	}
	return result;
}
int main()
{
	for(int i=0;i<2;i++){
		printf("please input date%d:(��ʽΪyear month day)",i+1);
		scanf_s("%d%d%d",&date[i].year,&date[i].month,&date[i].day);
		if(!JudgeCorrect(date[i])){
			printf("Error!please input the correct date!\n");
			i--;
		}
	}
	printf("\n%d/%d/%d �� %d/%d/%d ��ʱ���Ϊ��%d ��\n",date[0].year,date[0].month,date[0].day,date[1].year,date[1].month,date[1].day,TimeDifference(date[0],date[1]));
	return 0;
}
