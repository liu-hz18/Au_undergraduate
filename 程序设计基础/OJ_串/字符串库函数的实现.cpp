#include<stdio.h>
#include<malloc.h>

int my_strlen(char*s);
char*my_strcpy(char*s,char*t);
char*my_strncpy(char*s,char*t,int n);
char*my_strncat(char*s,char*t,int n);
int my_strcmp(char*s,char*t);
int my_strncmp(char*s,char*t,int n);
char*my_strins(char a[],char b[],int m);
int my_strstr(char*str,char*stra);
char*my_strreplace(char*str,char*stra,char*strb);
void Delete(char *s,int loc,int n);//loc ɾ������ʼ�ص㣬n ɾ���ĸ��� ;
char**getWords(char *str, int *n);
int *find(char *s);
void insert(char *s,char *t,int n);



int my_strlen(char*s){
	int i;
	for(i=0;s[i]!='\0';i++);
	return i;
}

//����t��s
char*my_strcpy(char*s,char*t)
{
	int i;
	for(i=0;*(t+i)!='\0';i++)
		*(s+i)=*(t+i);
	*(s+i)='\0';
	return(s);
}

//����t��ǰn���ַ���t
char*my_strncpy(char*s,char*t,int n)
{
	int i,len1,len2;
	len1=my_strlen(s);
	len2=my_strlen(t);
	if(len2<n)n=len2;//����n����t�ĳ��ȵĴ���
	for(i=0;i<n&&*(t+i)!='\0';i++)
		*(s+i)=*(t+i);
	if(len1<n)*(s+n)='\0';
	return(s);
}

//����t��ǰn���ַ���s��
char*my_strncat(char*s,char*t,int n)
{
	int i,len1,len2;
	len1=my_strlen(s);
	len2=my_strlen(t);
	if(len2<n)n=len2;//����n����t�ĳ��ȵĴ���
	for(i=0;i<n&&*(t+i)!='\0';i++)
		*(s+len1+i)=*(t+i);
    *(s+len1+n)='\0';
	return(s);
}

//�Ƚ�s��t�����ַ���
int my_strcmp(char*s,char*t)
{
	int m,i=1;
	while(*s==*t)
	{
		if(*s=='\0'||*t=='\0')return 0;
		s++;t++;i++;
	}
	m=*s-*t;
	if(m>0)m=1;
	else m=-1;
	return m;
}

//�Ƚ�s��t��ǰn���ַ�
int my_strncmp(char*s,char*t,int n)
{
	int m,i=1;
	while(*s==*t)
	{
		if(i==n||*s=='\0'||*t=='\0')return 0;
		s++;t++;i++;
	}
	m=*s-*t;
	if(m>0)m=1;
	else m=-1;
	return m;
}

//�ַ�����ָ��λ�ò���
char*my_strins(char a[],char b[],int m)
{
	char *c;
	c=(char*)malloc(100*sizeof(char));
	int len1=my_strlen(a),len2=my_strlen(b);
	int i;
	if(m>len1)
	{
		for(i=0;a[i]!='\0';i++)
			c[i]=a[i];
		for(i=0;b[i]!='\0';i++)
			c[len1+i]=b[i];
		c[len1+i]='\0';
		printf("��str1�����str2):\n");
	}
	else if(m<0)
	{
		for(i=0;b[i]!='\0';i++)
			c[i]=b[i];
		for(i=0;a[i]!='\0';i++)
			c[len2+i]=a[i];
		c[len2+i]='\0';
		printf("��str1ǰ����str2):\n");
	}
	else if(m>=0&&m<=len1)
	{
		for(i=0;i<m;i++)
			c[i]=a[i];
		for(i=m;b[i-m]!='\0';i++)
			c[i]=b[i-m];
		for(i=m;a[i]!='\0';i++)
			c[len2+i]=a[i];
		c[len2+i]='\0';
		printf("��str1�ĵ�%dλ����str2):\n",m);
	}
	return c;
}

//�����ַ������Ӵ���λ��
int my_strstr(char*str,char*stra){
	int loc=-1,i,j,k=0;
	for(i=0;str[i]!='\0';i++){
		if(str[i]==stra[0]){
			k=0;loc=i;
			for(j=i;stra[k]!='\0';j++){
				if(str[j]!=stra[k++])loc=-1;
			}
			if(stra[k]=='\0')break;
		}
	}
	return loc;
}

//�ַ����滻���������������е�stra�滻Ϊstrb
char*my_strreplace(char*str,char*stra,char*strb){
	int i,k,loc,lenb=my_strlen(strb),lena=my_strlen(stra),len=my_strlen(str);
	while((loc=my_strstr(str,stra))!=-1){
		k=0;
		for(i=len;i>=loc+lena-1;i--){
			str[i+lenb-lena]=str[i];
		}
		for(i=loc;i<loc+lenb;i++){
			str[i]=strb[k++];
		}
	}
	str[len+lenb-lena+1]='\0';
	return str;
}

void Delete(char *s,int loc,int n)//loc ɾ������ʼ�ص㣬n ɾ���ĸ��� 
{
	char temp[20];
	/*way1: strncpy(temp1,s,loc);temp1[loc]='\0';//strncpy��Ҫ����\0 
			strcpy(temp2,s+loc+n);
			strcat(temp1,temp2);
			strcpy(s,temp1);*/
	my_strcpy(temp,s+loc+n);//way2;
	my_strcpy(s+loc,temp);
}

//���ʲ�֣��ִʺ�������str ���зִʲ����أ����ʸ���ͨ��n ����
char**getWords(char *str, int *n)
{
	char **keys = (char **)malloc(sizeof(char*) * 100); //���赥�ʸ���������100
	int i = 0, j, k=0;
	while(str[i] != '\0')
	{
		if(str[i] != ' ')
		{
			*(keys+k) = (char *)malloc(sizeof(char) * 40); //����ÿ�����ʳ��Ȳ���40
			j = 0;
			while(str[i] != ' ' && str[i] != '\0')
			{
				keys[k][j] = str[i];
				j++;
				i++;
			}
			keys[k][j] = '\0';
			k++;
		}
		else
			i++;
	}
	*n = k;
	return keys;
}

//�ҵ�һ���ַ������������������������ַ���λ�ú���������123332��a[2]=3,��������-1; 
int *find(char *s)
{
	int i,*a,count,loc,len=my_strlen(s);
	a=(int *)malloc(len*sizeof(int));
	char t;
	for(i=0;i<len;i++)
		a[i]=-1;
	for(i=0;i<len;)
	{
		if (s[i]==s[i+1] && s[i+1]==s[i+2])
		{
			count=3;t=s[i];loc=i;i=i+3;
			while(s[i]==t)
			{
				count++;i++;
			}
			a[loc]=count;
		}
		else
			i++;
	}
	return a;
}

//insert������i love apples+round +3=i love round apples��
void insert(char *s,char *t,int n) 
{
	int i,len1=my_strlen(s),len2=my_strlen(t);
	char temp[100];
	for(i=n;i<len1;i++)
		if (s[i]==' ')
			break;
	if (i!=len1)
	{
		my_strcpy(temp,s+i+1);
		my_strcpy(s+i+1,t);
		my_strcpy(s+i+1+len2,temp);
	}
	else
		my_strcpy(s+i,t);
}

int main(){
	char s[10]="123456",t[10]="123";
	printf("%d\n",my_strlen(s));
	/*puts(my_strcpy(s,t));*/
	printf("%d\n",my_strcmp(s,t));
	printf("%d",my_strstr(s,t));
	puts(my_strins(s,t,3));
	return 0;
}
