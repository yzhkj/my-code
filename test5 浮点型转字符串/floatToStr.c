#include "stdio.h"
#include "string.h"

#define true 	1
#define false 	0

int ftos(float num,char *s,int n)
{
	int temp;
	float t=num;
	int pn=0;
	int flag_s=true;
	int flag_z=false;
	int i=0;	
	for(i=n;i>0;i--)
	{ 
		t=t*10;
	} 
	printf("%f\n",t);
	temp=t;
	printf("%d\n",temp);
	if(temp<0)
	{
		 temp=-temp;
		 t=-num;
		 flag_s=false;
	}
	if(temp==0)
	{	
		 if(n>0)
		 {
			for( pn=0;pn<n;pn++)
			{
			 	*(s+pn)='0';
			}
			*(s+pn)='\.';
			++pn;
		 }
		 *(s+pn)='0';
		 ++pn;
		 if(!flag_s)
		 {		
			 *(s+pn)='\-';
			++pn;
		 }
		 *(s+pn)='\0';	
	}
	else
	{
		while(temp>0)
		{
		 	if(pn==n && n>0)
			 {
			
				*(s+pn)='\.';
				++pn;
			 }
			 else
			 {
				 *(s+pn)=(temp%10)+'0';
				temp=temp/10;
				++pn;
			 }
		}
		while(pn<n)
		{
			*(s+pn)='0';
			 ++pn;
		}
		if(pn==n)
		 {	
			*(s+pn)='\.';
			++pn;
			if(flag_s)
			{
				*(s+pn)='0';
				  ++pn;
			}
		 }
		 if(!flag_s)
		 {
			if(t<1.0)
			{
				*(s+pn)='\.';
				++pn;
				*(s+pn)='0';
				 ++pn;
			}
			 *(s+pn)='\-';
			 ++pn;
		 }
		*(s+pn)='\0';
	}
//	int i(0),j(pn-1);
	int j=pn-1;
	i=0;
	while(i<j)
	{
		int temp=*(s+i);
		 *(s+i)=*(s+j);
		*(s+j)=temp;
		++i;
		j--;
	}
 	return true;
}


int main()
{
	 char s[20];
	 float num=123.456;
	 int n=3;
	 scanf("%f",&num);
	 scanf("%d",&n);
	 printf("float num is %f\n",num);
	 if(ftos(num,s,n))
	 {
	  	printf("after convert is %s\n",s);
	 }
	 return 0;
}
//--------------------- 
//作者：zhuzhiqi11 
//来源：CSDN 
//原文：https://blog.csdn.net/zhuzhiqi11/article/details/40158975 
//版权声明：本文为博主原创文章，转载请附上博文链接！
