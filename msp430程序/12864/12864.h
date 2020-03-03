#ifndef __LCD12864_H__
#define __LCD12864_H__

void lcd12864_init(void);
void lcd12864_display_string(unsigned char hang,unsigned char lie,unsigned char *p);
void lcd12864_display_TwoNum(unsigned char hang,unsigned char lie,unsigned char num);

#endif