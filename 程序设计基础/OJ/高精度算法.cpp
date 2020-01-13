#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
int an,bn,fa=1,fb=1;
/*把an,bn,k设为全局变量,an纪录第一个高精度数组的位数,bn纪录第二个高精度数组的位数,k纪录输出结果的位数*/
char b1[250],b2[250];/*纪录需要计算的两个高精度数据*/
void 
input(int a1[],int a2[])
 
{
    /*函数input为输入函数,用来纪录两个待计算的高精度数据,以数组首地址为参数.以实现返回两个高精度数据*/
    int i,ai=1,bi=1;
    scanf("%s%s",b1,b2);/*输入两个高精度数据*/
    an=
strlen(b1);/*an纪录b1的位数*/
    bn=strlen(b2);/*bn纪录b2的位数*/
    if(b1[0]==45){an--;fa=-1;ai=0;}/*判断数组的符号*/
    if(b2[0]==45){bn--;fb=-1;bi=0;}
    for(i=0;i<an;i++,ai++){a1[i]=b1[an-ai]-'0';
printf("%d",a1[i]);}
    /*把字符形数据b1转为整数形数据,同样用数组纪录*/
    for(i=0;i<bn;i++,bi++)a2[i]=b2[bn-bi]-'0';/*同上*/
    return;
}
 
void subtraction(int a[],int b[],int q);
void addition(int a[],int b[],int q)/*高精度加法运算*/
{
    int i,c[251]={0},k;
    if(fa*fb>0||q)
    {
        if(an>bn)
            k=an;
        else 
            k=bn;/*用k纪录结果的最小位数*/
        for(i=0;i<k;i++)
        {
            c[i]=a[i]+b[i]+c[i];
            c[i+1]=(int)c[i]/10;
            c[i]=(int)c[i]%10;
        }/*
高精度加法运算过程*/
        if(c[k])k++;/*判断最后结果的位数*/
        if(fa<0&&q||fa<0)
printf("-");
        for(i=k-1;i>=0;i--)printf("%d",c[i]);/*输出结果*/
        return;
    }
    else 
        subtraction(a,b,1);
    return;
}
void subtraction(int a[],int b[],int q)/*
高精度减法运算*/
{
    int i,f=0,c[251]={0},k;
    if(fa*fb>0||q)
    {
        if(an>bn)
            k=an;
        else/*用k纪录结果的最大位数*/
        {
            k=bn;
            for(i=k;a[i]<=b[i]&&i>=0;i--)
                if(a[i]<b[i])f=1;/*f纪录结果符号*/
        }
        if(!f)/*高精度减法运算过程*/
            for(i=0;i<k;i++)
            {
                if(a[i]<b[i])
                {a[i+1]--;
                a[i]+=10;
                }
                c[i]=a[i]-b[i];
            }
        else/*当a<b时的处理*/
            for(i=0;i<k;i++)
            {
                if(b[i]<a[i])
                {b[i+1]--;
                b[i]+=10;
                }
                c[i]=b[i]-a[i];
            }
 
            while(!c[k-1]&&k>1)k--;/*判断最后结果的位数*/
            if(q&&(fa>0&&f||fa<0&&!f)||fa>0&&(fb>0&&!f||f&&!q))
printf("-");/*如果f为真是输出负号*/
            for(i=k-1;i>=0;i--)printf("%d",c[i]);
            return;
    }
    else 
        addition(a,b,1);
}
void multiplication(int a[],int b[])/*
高精度乘法运算*/
{
    int i,j,c[501]={0},k;
    k=an+bn-1;/*用k纪录结果的最大位数*/
    for(i=0;i<an;i++)/*高精度乘法运算过程*/
        for(j=0;j<bn;j++)
        {
            c[i+j]=a[i]*b[j]+c[i+j];
            c[i+j+1]=c[i+j]/10+c[i+j+1];
            c[i+j]=c[i+j]%10;
        }
        while(!c[k])k--;/*判断最后结果的位数*/
        if(fa*fb<0)
printf("-");
        for(i=k;i>=0;i--)printf("%d",c[i]);/*输出结果*/
}
int main()
{
    int a[250]={0},b[250]={0};
    input(a,b);
    printf("\n%s+%s=",b1,b2);
    addition(a,b,0);
    printf("\n%s-%s=",b1,b2);
    subtraction(a,b,0);
    printf("\n%s*%s=",b1,b2);
    multiplication(a,b);
    system("pause");
    return 0;
}