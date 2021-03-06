#include "qi51arduino.h"
#include "lcd12864.h"
#include "DS1302.h"

sbit IRIN = P3 ^ 2;

uchar code gImage_huatu[1030] = { 0X00,0X01,0X80,0X00,0X40,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0X80,0X0C,0X06,0X00,0X00,0X00,0X70,0X07,0XFF,0XFC,0X00,0X00,
0X00,0X00,0X0C,0X03,0X00,0X0F,0XBF,0X7F,0X00,0X80,0X70,0X0F,0XFF,0XFC,0X00,0X00,
0X00,0X00,0X0F,0X87,0XFF,0X1F,0XBE,0XFF,0X01,0XDF,0XFF,0X0F,0XEE,0X0C,0X00,0X00,
0X00,0X00,0X07,0XE7,0XFF,0X01,0X30,0XE3,0X03,0X9F,0XFF,0X0E,0X0E,0X0C,0X00,0X00,
0X00,0X00,0X01,0XE6,0X03,0X00,0X30,0XE7,0X07,0X00,0X60,0X0E,0X0C,0X0C,0X00,0X00,
0X00,0X00,0X00,0XEE,0X07,0X1E,0X30,0XE7,0X0F,0X8F,0XF8,0X0E,0X0C,0X0C,0X00,0X00,
0X00,0X00,0X00,0XCC,0X67,0X1F,0X30,0XE7,0X1D,0X9F,0XFF,0X0E,0XFF,0XEC,0X00,0X00,
0X00,0X00,0X19,0XCC,0X76,0X07,0XB0,0XE7,0X09,0X9D,0XFF,0X0E,0XFF,0XEC,0X00,0X00,
0X00,0X00,0X1D,0XDC,0XE6,0X03,0XB0,0XE6,0X01,0X9C,0X67,0X0E,0X0C,0X2C,0X00,0X00,
0X00,0X00,0X0F,0X80,0XE6,0X03,0XB8,0XE6,0X01,0X8C,0X66,0X0E,0X0C,0X0C,0X00,0X00,
0X00,0X00,0X07,0X81,0XCE,0X03,0X3E,0XE6,0X01,0X8F,0XFE,0X0E,0X0C,0X0C,0X00,0X00,
0X00,0X00,0X07,0X01,0XC2,0X03,0X3F,0XEE,0X01,0X8F,0XFC,0X0E,0X0D,0XEC,0X00,0X00,
0X00,0X00,0X07,0X83,0X80,0X03,0X3E,0XEE,0X01,0X80,0X60,0X0F,0XFF,0XEC,0X00,0X00,
0X00,0X00,0X07,0X83,0XC0,0X03,0X1C,0XFE,0X03,0X9C,0XE0,0X0F,0XFF,0XCC,0X00,0X00,
0X00,0X00,0X07,0XC7,0XE0,0X03,0X08,0X60,0X03,0X9F,0XC0,0X0F,0X8C,0X0C,0X00,0X00,
0X00,0X00,0X0E,0XE6,0X78,0X03,0XE0,0X00,0X03,0X8F,0XE0,0X0E,0X0C,0X0E,0X00,0X00,
0X00,0X00,0X0C,0X6E,0X3C,0X07,0XFF,0X80,0X03,0X8F,0XF8,0X0E,0X0C,0X0E,0X00,0X00,
0X00,0X00,0X1C,0X4C,0X1E,0X0E,0X7F,0XFE,0X03,0X9E,0X7F,0X0C,0X0C,0X1E,0X00,0X00,
0X00,0X00,0X18,0X1C,0X0F,0X1C,0X01,0XFC,0X03,0XBC,0X0F,0X1C,0X0C,0X3C,0X00,0X00,
0X00,0X00,0X18,0X18,0X07,0X08,0X00,0X0C,0X03,0X90,0X02,0X38,0X04,0X18,0X00,0X00,
0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X08,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X60,0X00,0XC0,0X18,0X00,0X10,0X10,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X00,0X80,0X0D,0XFE,0X18,0X10,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X1F,0XFE,0X08,0X02,0X10,0X10,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X00,0X80,0X00,0X82,0X3D,0XFF,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X06,0X4C,0X03,0XF0,0X20,0X02,0X41,0X11,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X04,0X44,0X1C,0X1C,0X2F,0XFA,0X41,0X11,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X04,0X44,0X00,0X01,0X20,0X82,0X5D,0X11,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X08,0X42,0X3F,0XFE,0X20,0X82,0X11,0X11,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X08,0X42,0X00,0X09,0X27,0XF2,0X11,0X11,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X41,0X0F,0XC8,0X24,0X92,0X7D,0XFF,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X30,0X41,0X88,0X48,0X24,0X92,0X11,0X11,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X08,0X48,0X24,0X92,0X14,0X10,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X0F,0XC8,0X24,0XA2,0X14,0X10,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X01,0XC0,0X08,0X08,0X20,0X82,0X18,0X10,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X38,0X20,0X8C,0X30,0X10,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};


uchar code IC_DAT[] = {
    ""};

void IrInit()
{
    IT0 = 1;  //下降沿触发
    EX0 = 1;  //打开中断0允许
    EA = 1;   //打开总中断
    IRIN = 1; //初始化端口
}

void setup()
{
    IrInit();
    LCD_fulldisplay_picture_2(gImage_huatu);
}

void loop()
{
}

void ReadIr() interrupt 0
{
    uchar j, k;
    uint err;
    Time = 0;
    delaywhile(700); //7ms
    if (IRIN == 0)   //确认是否真的接收到正确的信号
    {
        err = 1000; //1000*10us=10ms,超过说明接收到错误的信号
        /*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/
        while ((IRIN == 0) && (err > 0)) //等待前面9ms的低电平过去
        {
            delaywhile(1);
            err--;
        }
        if (IRIN == 1) //如果正确等到9ms低电平
        {
            err = 500;
            while ((IRIN == 1) && (err > 0)) //等待4.5ms的起始高电平过去
            {
                delaywhile(1);
                err--;
            }
            for (k = 0; k < 4; k++) //共有4组数据
            {
                for (j = 0; j < 8; j++) //接收一组数据
                {
                    err = 60;
                    while ((IRIN == 0) && (err > 0)) //等待信号前面的560us低电平过去
                    {
                        delaywhile(1);
                        err--;
                    }
                    err = 500;
                    while ((IRIN == 1) && (err > 0)) //计算高电平的时间长度。
                    {
                        delaywhile(10); //0.1ms
                        Time++;
                        err--;
                        if (Time > 30)
                        {
                            return;
                        }
                    }
                    IrValue[k] >>= 1; //k表示第几组数据
                    if (Time >= 8)    //如果高电平出现大于565us，那么是1
                    {
                        IrValue[k] |= 0x80;
                    }
                    Time = 0; //用完时间要重新赋值
                }
            }
        }
        if (IrValue[2] != ~IrValue[3])
        {
            return;
        }
    }
}
