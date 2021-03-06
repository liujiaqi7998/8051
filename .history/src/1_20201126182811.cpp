#include <reg52.h>?
#define ?uint?unsigned?int?
#define ?uchar?unsigned?char?
sbit?lcden = P2 ^ 7;
sbit?lcdrw = P2 ^ 5;
sbit?lcdrs = P2 ^ 6;
sbit?DHT11_IO = P3 ^ 7;
uint?x, y, t;
uchar?code?table[] = "0123456789";

? void?Delay1() //延时10us?
{
    ?uchar?i;
    ?i--;
    ?i--;
    ?i--;
    ?i--;
    ?i--;
    ?i--;
    ?
}
?void?Delay2(uchar?ms)?
{
    ? //?延时子程序
        uchar?i?;
    ?while (ms--)?
    {
        ?for (i?=?0?;?i < 250; i++)?;
        ?
    }
    ?
}
?void?mDelay(uchar?delay)?
{
    ?uchar?i;
    ?for (; delay > 0; delay--)?
    {
        ?for (i = 123; i > 0; i--);
        ?
    }
    ?
}
?void?delay(uint?z)?
{
    ?for (x = z; x > 0; x--)?for (y = 110; y > 0; y--);
    ?
}
?void?write_com(uchar?com)?
{
    ?
?lcdrs = 0;
    ??lcdrw = 0;
    ??P0 = com;
    ??delay(5);
    ??lcden = 1;
    ??delay(5);
    ??lcden = 0;
    ?
}
?void?init()?
{
    ???write_com(0x38);
    ????write_com(0x0c);
    ????write_com(0x06);
    ????write_com(0x01);
    ???write_com(0x80);
    ???
}
????void?write_data(uchar?dat)?
{
    ??lcdrs = 1;
    ??lcdrw = 0;
    ??P0 = dat;
    ??delay(5);
    ??lcden = 1;
    ??delay(5);
    ??lcden = 0;
    ?
}
?void?start(void) //开始信号?
{
    ??DHT11_IO = 1;
    ??Delay1();
    ??DHT11_IO = 0;
    ??Delay2(20); //>18ms??
    DHT11_IO = 1;
    ??Delay1(); //20-40us??
    Delay1();
    ??Delay1();
    ??Delay1();
    ??Delay1();
    ?
}
? uchar?receive_byte(void) //接收一个字节?
{
    ??uchar?i, temp, count, data_byte;
    ??
?for (i = 0; i < 8; i++)??
    {
        ???while (!DHT11_IO); //等待50us低电平结束???
        temp = 0;
        ???Delay1();
        Delay1();
        Delay1();
        Delay1();
        ??? if (DHT11_IO == 1) temp = 1;
        ???while (DHT11_IO);
        ???data_byte <<= 1;
        ????data_byte |= temp;
        ??
    }
    ??return?data_byte;
    ?
}
??void?receive() //接收数据?
{
    ??uchar?check, num_check, HZ, HX, WZ, WX;
    ???start(); //开始信号??
    DHT11_IO = 1;
    ??if (!DHT11_IO) //读取DHT11响应信号??
    {
        ???while (!DHT11_IO); //DHT11高电平80us是否结束???
        while (DHT11_IO)
            ;
        ????HZ?=?receive_byte();
        ???HX?=?receive_byte();
        ???WZ?=?receive_byte();
        ???WX?=?receive_byte();
        ???check?=?receive_byte();
        ???DHT11_IO = 0; //拉低延时50us????
        DHT11_IO = 1;
        ????num_check?=?HZ?+?HX?+?WZ?+?WX;
        ????if (num_check?=?check)???
        {
            ????check?=?num_check;
            ???
        }
        ??
    }
    ??write_com(0x80);
    ??write_data(table[HZ / 10]);
    ??write_data(table[HZ % 10]);
    ??write_data('.');
    ?
        ?write_data(table[HX / 10]);
    ??write_data(table[HX % 10]);
    ?????write_data('R');
    ??write_data('H');
    ?????write_data('%');
    ?
}
?void?main()?
{
    ?????init();
    ??while (1)??
    {
        ???receive();
        ??
    }
    ?
}
?