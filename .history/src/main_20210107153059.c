#include "qi51arduino.h"
#include "lcd12864.h"
#include "SR04.h"

uchar code IC_DAT[] = {
    "这是小奇测试程序可以实现全屏显示可以显示标点符号，。！（）"};

void setup()
{
    int_lcd_12864();
    lcd_12864_text(IC_DAT);
    SR04_Init();
}

void loop()
{
    uchar temp[8];
    uint longl;
    while (pin21 == 1)
        ;
    lcd_12864_write_com(0x00);
    longl = SR04_GetOnce();
    temp[0] = '0' + longl / 10000000;
    temp[1] = '0' + (longl / 1000000) % 10;
    temp[2] = '0' + (longl / 100000) % 10;
    temp[3] = '0' + (longl / 10000) % 10;
    temp[4] = '0' + (longl / 1000) % 10;
    temp[5] = '0' + (longl / 100) % 10;
    temp[6] = '0' + (longl / 10) % 10;
    temp[7] = '0' + longl % 10;
    lcd_12864_len_text(1, temp);
}