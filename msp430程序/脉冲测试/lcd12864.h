#ifndef __LCD12864_H__
#define __LCD12864_H__

#define SetOut_RS                       (P6DIR |= BIT3)
#define RS_Out_1                        (P6OUT |= BIT3)
#define RS_Out_0                        (P6OUT &= ~BIT3)

#define SetOut_RW                       (P6DIR |= BIT4)
#define RW_Out_1                        (P6OUT |= BIT4)
#define RW_Out_0                        (P6OUT &= ~BIT4)

#define SetOut_EN                       (P6DIR |= BIT5)
#define EN_Out_1                        (P6OUT |= BIT5)
#define EN_Out_0                        (P6OUT &= ~BIT5)


#define SetOut_cs                       (P6DIR |= BIT6)
#define cs_Out_1                        (P6OUT |= BIT6)
#define cs_Out_0                        (P6OUT &= ~BIT6)

#define SETOUT_DIR1                       (P3DIR |= BIT0)
#define DIR1_OUT_1                        (P3OUT |= BIT0)
#define DIR1_OUT_0                        (P3OUT &= ~BIT0)

#define SETOUT_EN1                        (P3DIR |= BIT1)
#define EN1_OUT_1                        (P3OUT |= BIT1)
#define EN1_OUT_0                        (P3OUT &= ~BIT1)

#define SETOUT_DIR2                       (P3DIR |= BIT3)
#define DIR2_OUT_1                        (P3OUT |= BIT3)
#define DIR2_OUT_0                        (P3OUT &= ~BIT3)

#define SETOUT_EN2                        (P3DIR |= BIT2)
#define EN2_OUT_1                        (P3OUT |= BIT2)
#define EN2_OUT_0                        (P3OUT &= ~BIT2)

void lcd12864_init(void);
void lcd12864_display_string(unsigned char hang,unsigned char lie,unsigned char *p);
void lcd12864_display_TwoNum(unsigned char hang,unsigned char lie,unsigned char num);

#endif