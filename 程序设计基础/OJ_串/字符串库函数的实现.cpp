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
void Delete(char *s,int loc,int n);//loc 删除的起始地点，n 删除的个数 ;
char**getWords(char *str, int *n);
int *find(char *s);
void insert(char *s,char *t,int n);



int my_strlen(char*s){
	int i;
	for(i=0;s[i]!='\0';i++);
	return i;
}

//复制t给s
char*my_strcpy(char*s,char*t)
{
	int i;
	for(i=0;*(t+i)!='\0';i++)
		*(s+i)=*(t+i);
	*(s+i)='\0';
	return(s);
}

//复制t的前n个字符给t
char*my_strncpy(char*s,char*t,int n)
{
	int i,len1,len2;
	len1=my_strlen(s);
	len2=my_strlen(t);
	if(len2<n)n=len2;//对于n超过t的长度的处理
	for(i=0;i<n&&*(t+i)!='\0';i++)
		*(s+i)=*(t+i);
	if(len1<n)*(s+n)='\0';
	return(s);
}

//连接t的前n个字符到s后
char*my_strncat(char*s,char*t,int n)
{
	int i,len1,len2;
	len1=my_strlen(s);
	len2=my_strlen(t);
	if(len2<n)n=len2;//对于n超过t的长度的处理
	for(i=0;i<n&&*(t+i)!='\0';i++)
		*(s+len1+i)=*(t+i);
    *(s+len1+n)='\0';
	return(s);
}

//比较s和t两个字符串
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

//比较s和t的前n个字符
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

//字符串在指定位置插入
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
		printf("在str1后插入str2):\n");
	}
	else if(m<0)
	{
		for(i=0;b[i]!='\0';i++)
			c[i]=b[i];
		for(i=0;a[i]!='\0';i++)
			c[len2+i]=a[i];
		c[len2+i]='\0';
		printf("在str1前连接str2):\n");
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
		printf("在str1的第%d位插入str2):\n",m);
	}
	return c;
}

//返回字符串中子串的位置
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

//字符串替换，（迭代）把所有的stra替换为strb
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

void Delete(char *s,int loc,int n)//loc 删除的起始地点，n 删除的个数 
{
	char temp[20];
	/*way1: strncpy(temp1,s,loc);temp1[loc]='\0';//strncpy需要补充\0 
			strcpy(temp2,s+loc+n);
			strcat(temp1,temp2);
			strcpy(s,temp1);*/
	my_strcpy(temp,s+loc+n);//way2;
	my_strcpy(s+loc,temp);
}

//单词拆分，分词函数，对str 进行分词并返回，单词个数通过n 返回
char**getWords(char *str, int *n)
{
	char **keys = (char **)malloc(sizeof(char*) * 100); //假设单词个数不超过100
	int i = 0, j, k=0;
	while(str[i] != '\0')
	{
		if(str[i] != ' ')
		{
			*(keys+k) = (char *)malloc(sizeof(char) * 40); //假设每个单词长度不超40
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

//找到一个字符串中连续出现三个及以上字符的位置和数量，如123332，a[2]=3,其他都是-1; 
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

//insert函数（i love apples+round +3=i love round apples）
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
