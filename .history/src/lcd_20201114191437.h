#ifndef _INC_LCD
#define _INC_LCD
#define uchar unsigned char
#define uint unsigned int
#endif

sbit LCD_RS = P2 ^ 7; //命令/数据
sbit LCD_RW = P2 ^ 6; //读取/写入
sbit LCD_EN = P2 ^ 5; //使能

void lcd_commode(uchar commode);
void lcd_data(uchar commode);
void delay(unsigned int wait_time);

/*
lcd发送指令
常用命令
0x01 清屏
00111000 (0x38) 设置1602
0|0|0|0|1|D|C|B D=开启显示 C=开启光标 B=光标闪烁
0|0|0|0|0|1|N|S N=执行读写后加1/0减1 S=整屏幕左移
设置数据指针位置  0x80 + 0-27 / 40-67
*/
void lcd_commode(uchar commode)
{
    LCD_RS = 0;   //设置模式为：发送命令
    P0 = commode; //准备数据包
    delay(5);     //稍微延时一下
    LCD_EN = 0;   //发送数据！
    delay(5);     //稍微延时一下
    LCD_EN = 1;   //发送完成，变回正常模式
}
//lcd发送数据
void lcd_data(uchar commode)
{
    LCD_RS = 1;   //设置模式为：发送命令
    P0 = commode; //准备数据包
    delay(5);     //稍微延时一下
    LCD_EN = 0;   //发送数据！
    delay(5);     //稍微延时一下
    LCD_EN = 1;   //发送完成，变回正常模式
}

//显示字符串
void lcd_str(uchar print_date[])
{
    int num = 0;
    for (num = 0; num < 32; num++)
    {
        if (print_date[num] == '\0')
        {
            break;
        }
        lcd_data(print_date[num]);
    }
}