#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
int an,bn,fa=1,fb=1;
/*��an,bn,k��Ϊȫ�ֱ���,an��¼��һ���߾��������λ��,bn��¼�ڶ����߾��������λ��,k��¼��������λ��*/
char b1[250],b2[250];/*��¼��Ҫ����������߾�������*/
void 
input(int a1[],int a2[])
 
{
    /*����inputΪ���뺯��,������¼����������ĸ߾�������,�������׵�ַΪ����.��ʵ�ַ��������߾�������*/
    int i,ai=1,bi=1;
    scanf("%s%s",b1,b2);/*���������߾�������*/
    an=
strlen(b1);/*an��¼b1��λ��*/
    bn=strlen(b2);/*bn��¼b2��λ��*/
    if(b1[0]==45){an--;fa=-1;ai=0;}/*�ж�����ķ���*/
    if(b2[0]==45){bn--;fb=-1;bi=0;}
    for(i=0;i<an;i++,ai++){a1[i]=b1[an-ai]-'0';
printf("%d",a1[i]);}
    /*���ַ�������b1תΪ����������,ͬ���������¼*/
    for(i=0;i<bn;i++,bi++)a2[i]=b2[bn-bi]-'0';/*ͬ��*/
    return;
}
 
void subtraction(int a[],int b[],int q);
void addition(int a[],int b[],int q)/*�߾��ȼӷ�����*/
{
    int i,c[251]={0},k;
    if(fa*fb>0||q)
    {
        if(an>bn)
            k=an;
        else 
            k=bn;/*��k��¼�������Сλ��*/
        for(i=0;i<k;i++)
        {
            c[i]=a[i]+b[i]+c[i];
            c[i+1]=(int)c[i]/10;
            c[i]=(int)c[i]%10;
        }/*
�߾��ȼӷ��������*/
        if(c[k])k++;/*�ж��������λ��*/
        if(fa<0&&q||fa<0)
printf("-");
        for(i=k-1;i>=0;i--)printf("%d",c[i]);/*������*/
        return;
    }
    else 
        subtraction(a,b,1);
    return;
}
void subtraction(int a[],int b[],int q)/*
�߾��ȼ�������*/
{
    int i,f=0,c[251]={0},k;
    if(fa*fb>0||q)
    {
        if(an>bn)
            k=an;
        else/*��k��¼��������λ��*/
        {
            k=bn;
            for(i=k;a[i]<=b[i]&&i>=0;i--)
                if(a[i]<b[i])f=1;/*f��¼�������*/
        }
        if(!f)/*�߾��ȼ����������*/
            for(i=0;i<k;i++)
            {
                if(a[i]<b[i])
                {a[i+1]--;
                a[i]+=10;
                }
                c[i]=a[i]-b[i];
            }
        else/*��a<bʱ�Ĵ���*/
            for(i=0;i<k;i++)
            {
                if(b[i]<a[i])
                {b[i+1]--;
                b[i]+=10;
                }
                c[i]=b[i]-a[i];
            }
 
            while(!c[k-1]&&k>1)k--;/*�ж��������λ��*/
            if(q&&(fa>0&&f||fa<0&&!f)||fa>0&&(fb>0&&!f||f&&!q))
printf("-");/*���fΪ�����������*/
            for(i=k-1;i>=0;i--)printf("%d",c[i]);
            return;
    }
    else 
        addition(a,b,1);
}
void multiplication(int a[],int b[])/*
�߾��ȳ˷�����*/
{
    int i,j,c[501]={0},k;
    k=an+bn-1;/*��k��¼��������λ��*/
    for(i=0;i<an;i++)/*�߾��ȳ˷��������*/
        for(j=0;j<bn;j++)
        {
            c[i+j]=a[i]*b[j]+c[i+j];
            c[i+j+1]=c[i+j]/10+c[i+j+1];
            c[i+j]=c[i+j]%10;
        }
        while(!c[k])k--;/*�ж��������λ��*/
        if(fa*fb<0)
printf("-");
        for(i=k;i>=0;i--)printf("%d",c[i]);/*������*/
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