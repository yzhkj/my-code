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

/*�ж�101-200֮���ж��ٸ���������������������������ĸ�����
����������ж������ķ�������һ�����ֱ�ȥ��2��sqrt(�����)��
����ܱ�����,���������������������֮��������*/

#define START_NUM  101
#define END_NUM    200

void cal_sushu(void)
{
	int temp=0;
	int medium=0; 
	int count=0;
	int temp_num[100]={0};
	int count_add=0;
	for(temp=START_NUM;temp<=END_NUM;temp++)		//�����ܵ�ѭ������ 
	{
		medium=(int)sqrtf(temp);
//		printf("������Ϊ��%d\n",medium);
		for(count=2;count<medium;count++)
		{
			if(0==(temp%count))
			{
				temp_num[count_add]=temp;
//				printf("����Ϊ��%d\n",temp);
				count_add++;
				break; 
			}
		}
	}
	printf("101-200�������У�"); 
	for(count=0;count<count_add;count++)
	{
		printf("%d\t",temp_num[count]);
	}
	printf("\n����������Ϊ��%d\n",count_add);
} 

/*�ŵ����⣺��һ�����ӣ��ӳ������3������ÿ���¶���һ�����ӣ�С���ӳ����������º�ÿ��������һ�����ӣ�
�������Ӷ���������ÿ���µ���������Ϊ���٣����ӵĹ���Ϊ����1,1,2,3,5,8,13,21��.*/
#define Max_Mouth 48
void rabit(void)
{
	int count=0;
	long rabit_num[Max_Mouth]={1,1,2};
	long rabit_num_add[Max_Mouth]={1,0,1};
	long sum=1;
	long sum_num=4;
	for(count=3;count<Max_Mouth;count++)			//���򵥵Ľⷨ����ǰ������ֵ��Ӹ�ֵ���������� 
	{
		sum=sum+rabit_num_add[count-2];
		rabit_num_add[count]=sum;
		rabit_num[count]=rabit_num[count-1]+rabit_num_add[count];
		
		printf("�� %d �������ӵ�������%d ��������Ϊ%d\n",count,rabit_num[count],sum);
		
	}
}
/*���9*9�ھ�����9��9�У�i�����У�j�����С�*/
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
