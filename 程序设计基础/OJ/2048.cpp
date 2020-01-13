//Created by Lenovo at 2018/11/29 21:22
//CopyRight@LiuHongzun at Tsinghua University.Beijing.
//2048 Game.

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
void init();
void draw();
void play();
void add_number();
void to_up();
void to_down();
void to_left();
void to_right();
int judge();

int a[4][4];
int empty;
int count=0;

int main()
{
	system("color F0");
	printf("***********************************\n");
	printf("              2048              \n");
	printf("Press w/s/a/d or W/S/A/D to control\n");
	printf("      Press q/Q to quit game\n");
	printf("***********************************\n");
	printf("Press any key to enjoy!\n");
	_getch();
	system("cls");
	init();
	draw();
	while(1)
	{
		if(judge())
		{
			count++;
			play();
		}
		else if(judge()==0)
		{
			count++;
			printf("\n**************************\n You such a Loser!Game Over!\n\n");
			break;
		}
		else if(judge()==2)
		{
			printf("\n**************************\n Good Guy!You WIN!!!\n\n");
			break;
		}
	}
	return 0;
}

void init()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			a[i][j]=0;
	srand(time(NULL));
	i=rand()%4;//除3取余，生成0到3之间随机数
	j=rand()%4;
	a[i][j]=2;
	empty=15;
}

void draw()
{
	int i,j;
	printf("***********************************\n");
	printf("              2048              \n");
	printf("Press w/s/a/d or W/S/A/D to control\n");
	printf("      Press q/Q to quit game\n");
	printf("***********************************\n");
	for(i=0;i<4;i++)printf(" ____");
	putchar(10);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			printf("|    ");
		printf("|\n");
		for(j=0;j<4;j++)
		{
			if(a[i][j]==0)printf("|    ");
			else printf("|%4d",a[i][j]);
		}
		printf("|\n");
		for(j=0;j<4;j++)
			printf("|____");
		printf("|\n");
	}
	printf("\t\t\t\t\t操作次数：%d",count);
}

void play()
{
	int ch;
	ch=_getch();
	switch(ch)
	{
	case'w':case'W':
		to_up();
		system("cls");
		add_number();
		draw();
		break;
	case's':case'S':
		to_down();
		system("cls");
		add_number();
		draw();
		break;
	case'a':case'A':
		to_left();
		system("cls");
		add_number();
		draw();
		break;
	case'd':case'D':
		to_right();
		system("cls");
		add_number();
		draw();
		break;
	case'q':case'Q':
		exit(0);
		break;
	default:
		printf("\nWrong input!please press w/s/a/d or W/S/A/D\n");
		break;
	}
}
void to_up()//先合并再整体上移
{
	int x,y,i;
	for(y=0;y<4;y++)//合并相同元素
	{
		for(x=0;x<4;x++)
		{
			if(a[x][y]==0);
			else//找到一个不为零的元素
			{
				for(i=x+1;i<4;i++)
					if(a[i][y]==0);
					else if(a[x][y]==a[i][y])//找到该元素下面的一个不为零的元素
					{
						a[x][y]+=a[i][y];
						a[i][y]=0;
						empty++;
						x=i;
						break;
					}
					else{
						break;
					}
			}
		}
	}
	for(y=0;y<4;y++)//将元素上移
		for(x=0;x<4;x++)
		{
			if(a[x][y]==0);
			else
				for(i=x;(i>0)&&(a[i-1][y]==0);i--)//上面一位为0就上移
				{
					a[i-1][y]=a[i][y];
					a[i][y]=0;
				}
		}
}

void to_down()
{
	int x,y,i;
	for(y=0;y<4;y++)
	{
		for(x=3;x>=0;x--)
		{
			if(a[x][y]==0);
			else
			{
				for(i=x-1;i>=0;i--)
					if(a[i][y]==0);
					else if(a[x][y]==a[i][y])
					{
						a[x][y]+=a[i][y];
						a[i][y]=0;
						empty++;
						x=i;
						break;
					}
					else{
						break;
					}
			}
		}
	}
	for(y=0;y<4;y++)
		for(x=3;x>=0;x--)
		{
			if(a[x][y]==0);
			else
				for(i=x;(i<3)&&(a[i+1][y]==0);i++)
				{
					a[i+1][y]=a[i][y];
					a[i][y]=0;
				}
		}
}

void to_left()
{
	int x,y,i;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			if(a[x][y]==0);
			else
			{
				for(i=y+1;i<4;i++)
					if(a[x][i]==0);
					else if(a[x][y]==a[x][i])
					{
						a[x][y]+=a[x][i];
						a[x][i]=0;
						empty++;
						y=i;
						break;
					}
					else{
						break;
					}
			}
		}
	}
	for(x=0;x<4;x++)
		for(y=0;y<4;y++)
		{
			if(a[x][y]==0);
			else
				for(i=y;(i>0)&&(a[x][i-1]==0);i--)
				{
					a[x][i-1]=a[x][i];
					a[x][i]=0;
				}
		}
}
void to_right()
{
	int x,y,i;
	for(x=0;x<4;x++)
	{
		for(y=3;y>=0;y--)
		{
			if(a[x][y]==0);
			else
			{
				for(i=y-1;i>=0;i--)
					if(a[x][i]==0);
					else if(a[x][y]==a[x][i])
					{
						a[x][y]+=a[x][i];
						a[x][i]=0;
						empty++;
						y=i;
						break;
					}
					else{
						break;
					}
			}
		}
	}
	for(x=0;x<4;x++)
		for(y=3;y>=0;y--)
		{
			if(a[x][y]==0);
			else
				for(i=y;(i<3)&&(a[x][i+1]==0);i++)
				{
					a[x][i+1]=a[x][i];
					a[x][i]=0;
				}
		}
}

void add_number()
{
	int number;
	int x,y;
	if(empty>0)//仍存在空格
	{
		do{
			x=rand()%4;
			y=rand()%4;
		}while(a[x][y]!=0);//当所在元素为不为零的时候一直生成x,y,否则跳出循环进行赋值
		number=rand()%2;//number只能取0和1，也就对应实际情况的2和4
		if(number==1)
		{
			a[x][y]=2;
			empty--;
		}
		if(number==0)
		{
			a[x][y]=4;
			empty--;
		}
	}
}
int judge()
{
	int flag=0;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			if(a[i][j]==0)
			{
				flag=1;
				break;
			}
			if(a[i][j]==2048)
			{
				flag=2;
				break;
			}
		}
	return flag;
}
