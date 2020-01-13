//判断日期差
#include<stdio.h>
struct time{
	int year;
	int month;
	int day;
}date[2];
int JudgeLeapYear(int year)//判断闰年
{
	if((year%4==0&&year%100!=0)||(year%400==0))return 1;
	return 0;
}
int JudgeCorrect(time date)//判断输入日期是否合理
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
int TimeDifference(time date1,time date2)//核心函数，求两个日期的差值
{
	int day[2]={date1.day,date2.day};
	int result=0;
	int monthdate[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	time tmp;
	//判断第一个日期是否小于第二个日期，否则交换两个日期
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
		//先分别计算两个日期是该年的第几天
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
		//此处在for循环的初始定义中，第一个int就会定义后面所有的变量直到遇到分号，
		//因此在这里对result赋值，由于int i的存在，会把result自动转换成局部变量，
		//result在该代码块指向完后会消失！因此应在for之前就对result进行操作
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
		printf("please input date%d:(格式为year month day)",i+1);
		scanf_s("%d%d%d",&date[i].year,&date[i].month,&date[i].day);
		if(!JudgeCorrect(date[i])){
			printf("Error!please input the correct date!\n");
			i--;
		}
	}
	printf("\n%d/%d/%d 和 %d/%d/%d 的时间差为：%d 天\n",date[0].year,date[0].month,date[0].day,date[1].year,date[1].month,date[1].day,TimeDifference(date[0],date[1]));
	return 0;
}
