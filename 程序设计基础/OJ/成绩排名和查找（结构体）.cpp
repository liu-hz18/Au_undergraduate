#include<stdio.h>
#include<string.h>
struct student{
	char num[12];
	char name[22];
	char stuclass[10];
	double score1;
	double score2;
	double aver;
	int rank;
};
void input(student*stu,int*count){
	int i=0;
	while(1){
		scanf_s("%s",stu[i].num,12);
		if(strcmp(stu[i].num,"end")==0){getchar();break;}
		scanf_s("%s%s",stu[i].name,22,stu[i].stuclass,10);
		scanf_s("%lf",&(stu[i].score1));
		scanf_s("%lf",&(stu[i].score2));//浮点数不能同时输入，另外注意加 取址符 &
		stu[i].aver=(stu[i].score1+stu[i].score2)/2;
		i++;
		getchar();
	}
	*count=i;
}
//交换两个数组元素应该传地址，然后在子函数中对它解地址才能交换！！！
void swap(student*stu1,student*stu2){
	student tmp;
	tmp=*stu1;
	*stu1=*stu2;
	*stu2=tmp;
}
void rank(student*stu,int total){
	int i,j;
	for(i=total-1;i>=0;i--){
		for(j=0;j<i;j++){
			if(stu[j].aver<(stu)[j+1].aver||((stu)[j].aver==(stu)[j+1].aver&&(stu)[j].score1<(stu)[j+1].score1)||((stu)[j].aver==(stu)[j+1].aver&&(stu)[j].score1==(stu)[j+1].score1&&(stu)[j].score2<(stu)[j+1].score2))
				swap(&stu[j],&stu[j+1]);
		}
	}
	(stu)[0].rank=1;
	for(i=0;i<total-1;i++){
		if((stu)[i].aver==(stu)[i+1].aver&&(stu)[i].score1==(stu)[i+1].score1&&(stu)[i].score2==(stu)[i+1].score2)
			(stu)[i+1].rank=(stu)[i].rank;
		else (stu)[i+1].rank=i+2;
	}
}
void print(student*stu,int total){
	int i;
	printf("排名   学号    姓名    班级     平均成绩     成绩1     成绩2\n");
	for(i=0;i<total;i++){
		printf("%d %s %s %s %f %f %f\n",stu[i].rank,stu[i].num,stu[i].name,stu[i].stuclass,stu[i].aver,stu[i].score1,stu[i].score2);
	}
}
void search(student*stu,int total)
{
	int flag=-1;char num[12];
	while(1){
		printf("please input the num you want to search:");
		gets_s(num);
		if(strcmp(num,"end")==0)break;
		flag=-1;
		for(int i=0;i<total;i++){
			if(strcmp(num,stu[i].num)==0){
				flag=i;
				printf("%d %s %s %s %f %f %f\n",stu[i].rank,stu[i].num,stu[i].name,stu[i].stuclass,stu[i].aver,stu[i].score1,stu[i].score2);
				break;
			}
		}
		if(flag==-1)printf("Error!\n");
	}
}
int main()
{
	student stu[25],*p=stu;
	int count;
	input(stu,&count);	
	rank(stu,count);
	print(stu,count);
	search(stu,count);
	return 0;
}
