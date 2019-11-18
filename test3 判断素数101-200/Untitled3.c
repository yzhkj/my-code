#include "stdio.h"
#include "math.h"



void rabit(void);
void multi_char(void);
void cal_sushu(void);

 
int main(void)
{
//	rabit();
	cal_sushu();
	return 0;
} 

/*判断101-200之间有多少个素数，并输出所有素数及素数的个数。
程序分析：判断素数的方法：用一个数分别去除2到sqrt(这个数)，
如果能被整除,则表明此数不是素数，反之是素数。*/

#define START_NUM  101
#define END_NUM    200

void cal_sushu(void)
{
	int temp=0;
	int medium=0; 
	int count=0;
	int temp_num[100]={0};
	int count_add=0;
	for(temp=START_NUM;temp<=END_NUM;temp++)		//控制总的循环次数 
	{
		medium=(int)sqrtf(temp);
//		printf("开方数为：%d\n",medium);
		for(count=2;count<medium;count++)
		{
			if(0==(temp%count))
			{
				temp_num[count_add]=temp;
//				printf("素数为：%d\n",temp);
				count_add++;
				break; 
			}
		}
	}
	printf("101-200的素数有："); 
	for(count=0;count<count_add;count++)
	{
		printf("%d\t",temp_num[count]);
	}
	printf("\n素数的总数为：%d\n",count_add);
} 

/*古典问题：有一对兔子，从出生后第3个月起每个月都生一对兔子，小兔子长到第三个月后每个月又生一对兔子，
假如兔子都不死，问每个月的兔子总数为多少？兔子的规律为数列1,1,2,3,5,8,13,21….*/
#define Max_Mouth 48
void rabit(void)
{
	int count=0;
	long rabit_num[Max_Mouth]={1,1,2};
	long rabit_num_add[Max_Mouth]={1,0,1};
	long sum=1;
	long sum_num=4;
	for(count=3;count<Max_Mouth;count++)			//更简单的解法，将前两个的值相加赋值给第三个月 
	{
		sum=sum+rabit_num_add[count-2];
		rabit_num_add[count]=sum;
		rabit_num[count]=rabit_num[count-1]+rabit_num_add[count];
		
		printf("第 %d 个月兔子的总数：%d 增加数量为%d\n",count,rabit_num[count],sum);
		
	}
}
/*输出9*9口诀。共9行9列，i控制行，j控制列。*/
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
