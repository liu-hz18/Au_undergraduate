//plane fees calculation

#include<stdio.h>
#include<math.h>
int main()
{
	char s,n,h;float w,m;
	float f1(float x);float f2(float y);float f3(float z);
	printf("请输入国别（C/F)，是否残疾(N/U)，仓位代码:");
	scanf_s("%c",&n);scanf_s("%c",&h);scanf_s("%c",&s);
	printf("请输入行李重量：");
	scanf_s("%f",&w);
	if(s>'Z') s-=32;if(n>'Z') n-=32;if(h>'Z') h-=32;//实现大小写兼容
	if(s=='F'||s=='A')
	  {
		m=f1(w);   
	    if(n=='F')m*=2;if(h=='U')m*=0.5;
	    printf("补缴超重款项：%.2f元\n",m);
	  }
	  else if(s=='C'||s=='D')
	  {
		  m=f2(w);    
	      if(n=='F')m*=2;if(h=='U')m*=0.5;
	      printf("补缴超重款项：%.2f元\n",m);
	  }
	    else
	  {
		 m=f3(w);
         if(n=='F')m*=2;if(h=='U')m*=0.5;
	     if(s=='B')m/=0.9;if(s=='H')m/=0.85;if(s=='K')m/=0.8;if(s=='L')m/=0.75;
	     if(s=='M')m/=0.7;if(s=='N')m/=0.65;if(s=='Q')m/=0.6;if(s=='T')m/=0.55;
	     if(s=='X')m/=0.5;if(s=='U')m/=0.45;if(s=='E')m/=0.4;if(s=='W')m/=0.35;
	     if(s=='R')m/=0.3;if(s=='O')m/=0.25;
	     printf("补缴超重款项：%.2f元\n",m);
	  }

return 0;
}

float f1(float x)
{
	float m;
	if(x<=30)m=0;
	 else if(x<=35)m=(x-30)*4;
	 else if(x<=40)m=5*4+(x-35)*5;
	 else if(x<=50)m=5*4+5*5+(x-40)*7;
	 else m=5*4+5*5+10*7+(x-50)*12;
	 return m;
}

float f2(float y)
{
	float m;
	if(y<=25)m=0;
	else if(y<=30)m=(y-25)*5;
	else if(y<=35)m=5*5+(y-30)*6;
	else if(y<=45)m=5*5+5*6+(y-35)*8;
	else m=5*5+5*6+10*8+(y-45)*13;
	return m;
}

float f3(float z)
{
	float m;
	if(z<=20)m=0;
	else if(z<=25)m=(z-20)*6;
	else if(z<=30)m=5*5+(z-25)*7;
	else if(z<=40)m=5*5+5*6+(z-30)*9;
	else m=5*5+5*6+10*8+(z-40)*14;
	return m;
}
