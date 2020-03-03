#include <stdio.h>
#include <stdlib.h>

#define sum(x)   (x)+(x)
#define empty              //空宏定义也是可以的
#define sqr(x)	(temp=x,temp*=temp) 

#define x_temp  3
#define y_temp  x_temp*2
#undef  x_temp
#define x_temp  2
int z_temp=y_temp;  


int tribonacci(int n)
{
	if( n <= 0){
		return 0;
	}else if( n < 3){
		return 1;
	}else{
		//return (tribonacci(n-3)+tribonacci(n-2)+tribonacci(n-1));
		return 2*tribonacci(n-1) - tribonacci(n-4);
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void) 
{
	int x=5;
	do{
		
		printf("\n please type a tribonacci num:");
		scanf("%d",&x);
		printf("\n the tribonacci num is:%d",tribonacci(x));		
		
	}while(x > 0);

	return 0;
}


