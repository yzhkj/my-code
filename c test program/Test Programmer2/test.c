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


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int temp;
int main(void) 
{
	int x=5;
	char res;
	res=sqr(x++);
	printf("%d\n",res);
	printf("sum(x)\n");
	printf("%d\n",sum(x));
	printf("%d\n",z_temp); 
	return 0;
}


