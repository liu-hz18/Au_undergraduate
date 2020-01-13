#include<stdio.h>
#include<math.h>
int main()
{
	int time1,time2;
	int t1,t2,t,day,hrs,mins;
	scanf_s("%d%d",&time1,&time2);
    t1=24*60*(time1/10000)+60*(time1%10000-time1%100)/100+(time1%100);
	t2=24*60*(time2/10000)+60*(time2%10000-time2%100)/100+(time2%100);
	t=t2-t1;
	day=t/(24*60);
	hrs=t/60-day*24;
	mins=t-day*60*24-hrs*60;
	printf("The time is %dday %dhrs %dmins\n",day,hrs,mins);
}