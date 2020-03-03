#include "msp430f149.h"
#define   Num_of_Results   32

//unsigned char table[10]="0123456789";
static unsigned int results[Num_of_Results];    //保存ADC转换结果的数组// is not used for anything.
static unsigned int results1[Num_of_Results];

static unsigned int ADC12A0;
static unsigned int ADC12A1;
static unsigned int ADC12A2;
void adc12_init();
void Trans_val(int Hex_Val);
