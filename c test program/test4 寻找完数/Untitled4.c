#include "stdio.h"
#include "math.h"

typedef struct	factor_st	    //���������ṹ����� 
{
//	int Factor_Num[20]={0}; 	//�������� 
	int Factor_Num[20]; 	//�������� 
	int counter;				//�������������� 
	int Factor_Sum;			//������� 
}factor; 

void rabit(void);
void multi_char(void);
void cal_sushu(void);
void Find_Complelet_Num(void);
factor* Find_Factor_Num(int Num);

 
int main(void)
{
//	rabit();
//	cal_sushu();
//	Find_Complelet_Num();
	int temp=0;
	factor* factor_point=NULL;
	factor_point=Find_Factor_Num(10);
	for(temp=0;temp<factor_point->counter;temp++)
	{
		printf("%d\t",factor_point->Factor_Num[temp]);
	}
	return 0;
}

/*һ�������ǡ�õ�����������֮�ͣ�������ͳ�Ϊ����������
����6=1��2��3.����ҳ�1000���ڵ�����������*/ 

#define Max_Num 1000 

void Find_Complelet_Num(void)
{
 	int Num=0;
 	int i=0;
 	int count=0;
 	int Num_reserve[100]={0};
 	factor* factor_point=NULL;
 	for(Num=1;Num<=Max_Num;count++)
 	{
 		factor_point=Find_Factor_Num(Num);
 		if(Num==factor_point->Factor_Sum+1)
 		{
 			Num_reserve[count++]=Num;
		}
	}
	printf("�����У�"); 
	for(i=0;i<count;i++)
	{ 
		printf("%d\t",Num_reserve[i]);
	}
	printf("\n�����ܼ���:%d\n",count);
}




factor* Find_Factor_Num(int Num)
{
	factor factor1;
	factor* factor_p=&factor1;
	int medium=0,count=0;
	medium=(int)sqrtf(Num);
//	printf("������Ϊ��%d\n",medium);
	for(count=2;count<=medium;count++)
	{
		if(0==(Num%count))
		{
			factor_p->Factor_Num[factor_p->counter]=count;
			factor_p->counter++;
			factor_p->Factor_Sum=factor_p->Factor_Sum+count;
			
			break; 
		}
	}
	return factor_p;	 
	
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
