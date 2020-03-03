#include "math.h"


void ResolveNumBit(u16 num,u16* array,u8* len)
{
	u8 i=0;
	u16 n=num;
	u16* a=array;
	do
	{
			
		a[i]=n%10;
				
		n=n/10;
				
		i++;
		
	}while(n>0);

	*len=i;
	
}


