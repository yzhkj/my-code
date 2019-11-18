#include "stdio.h"


#define Max_Mouth 50

void rabit(void);

int main(void)
{
	rabit();
	return 0;
} 
void rabit(void)
{
	int count=0;
	long rabit_num[Max_Mouth]={1,1,2};
	long rabit_num_add[Max_Mouth]={1,0,1};
	long sum=1;
	long sum_num=4;
	for(count=3;count<Max_Mouth;count++)
	{
		sum=sum+rabit_num_add[count-2];
		rabit_num_add[count]=sum;
		rabit_num[count]=rabit_num[count-1]+rabit_num_add[count];
		
		printf("第 %d 个月兔子的总数：%d 增加数量为%d\n",count,rabit_num[count],sum);
		
	}
}
void multi_char(void)
{
	int i=0,j=0;
	int result=0;
	int count=0;
	for(i=1;i<10;i++)
	{
		count=i-1;
		while
		(count>0)
		{
			printf("\t");
			count--;
		}
		for(j=i;j<10;j++)
		{
			printf("%d\t",i*j);
		}
		printf("\n");
	}	
}
