#include "qi51arduino.h"
#include "lcd12864.h"
#include "DS1302.h"

uchar temp[3];

unsigned char code IC_DAT[] = {
    "����С����Գ������ʵ��ȫ����ʾ������ʾ�����ţ���������"};

void setup()
{
        int_lcd_12864();
        lcd_12864_text(IC_DAT);
}

void loop()
{
        while (pin21 == 1)
                ;
        lcd_12864_write_com(0x00);
        
}