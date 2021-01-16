#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit lcden = P3 ^ 4; //?��??lcd??????
sbit lcdrs = P3 ^ 5; //?��??lcd?????��????????
sbit lcdwr = P3 ^ 6; //?��??lcd??????????
sbit lcdrd = P3 ^ 7; //?��????????????
sbit DQ = P2 ^ 2;    //?��??DS18B20????????????
uchar high, low;
char a, d2, d1, d0;
float f_temp;
uint i, j, temp;
uchar code line1[] = {"???��??��????????��"};
uchar code line2[] = "?��?��??????";
uchar code line3[] = "00.0??";
//-------------------?????????��????-------------------------
void delay_ms(uint z) //???��z????
{
    uint x, y;
    for (x = z; x > 0; x--)
        for (y = 115; y > 0; y--)
            ;
}
//------------lcd??????????-------------
void wr_cmd(uchar cmd)
{
    lcden = 0;
    lcdrs = 0;
    P0 = cmd;
    delay_ms(1);
    lcden = 1;
    delay_ms(1);
    lcden = 0;
}
//-----------lcd??????????-----------
void wr_dat(uchar dat)
{
    lcden = 0;
    lcdrs = 1;
    P0 = dat;
    delay_ms(1);
    lcden = 1;
    delay_ms(1);
    lcden = 0;
}

//-----------------------???��??????��?????????--------------------------
void face_dis()
{
    wr_cmd(0x30); //??????????8???????����???????����
    wr_cmd(0x0c); //????????????????????����
    wr_cmd(0x01); //lcd????
    wr_cmd(0x02); //??����?��????
    wr_cmd(0x80);
    for (a = 0; a < 16; a++) //??????????????
    {
        wr_dat(line1[a]);
    }

    wr_cmd(0x90);            //?��??????????????
    for (a = 0; a < 10; a++) //??????????????
    {
        wr_dat(line2[a]);
    }
    wr_cmd(0x8c);           //?��??????????????
    for (a = 0; a < 6; a++) //??????????????
    {
        wr_dat(line3[a]);
    }
}
//------------------------???��????????????????-------------------------------
void dat_dis()
{
    wr_cmd(0x8c); //????????
    wr_dat(0x30 + d2);
    wr_dat(0x30 + d1);
    wr_dat(0x2e); //?????��.?��??
    wr_dat(0x30 + d0);
}
//-----------------------------??????????------------------------------------
void init()
{
    delay_ms(20); //???????��???????????��
    lcdrd = 1;    //???��lcd???????��????????
    lcdwr = 0;    //?��?????????��????lcd???��?????????��?????��????????????????��??????��???????��?��??
    face_dis();   //???????��????
}
//-----------------------??????��?????????????--------------------
void init_temp()
{
    DQ = 0; //????��??????��?��????????
    i = 80;
    while (i > 0)
        i--; //???��480~960us
    DQ = 1;  //????��???
    i = 4;
    while (i > 0)
        i--; //???��15~60us
    while (DQ)
        ; //?????��?��????????
    i = 70;
    while (i > 0)
        i--; //???��????480us
}
//------------------??????��?????????-------------------------------
void wr_temp(uchar dat) //??1??��???
{
    bit testb;
    for (j = 8; j > 0; j--)
    {
        testb = dat & 0x01;
        dat = dat >> 1;
        if (testb) //??1
        {
            DQ = 0; //????��??????��?��???��????
            i++;    //???��?��??1us
            DQ = 1; //????��???
            i = 8;
            while (i > 0)
                i--; //???��????60us????DS18B20???��
        }
        else //??0
        {
            DQ = 0; //????��??????��?��???��????
            i = 8;
            while (i > 0)
                i--; //��???????60us????DS18B20???��
            DQ = 1;  //????��???
            i++;
            i++;
        }
    }
}
//------------------??????��?????????-------------------------------
uchar rd_temp() //??1??��???
{
    bit b; //?��????��?????????1??��???
    uchar i_b;
    uchar rdbyte;
    for (j = 8; j > 0; j--)
    {
        DQ = 0; //????��??????��?��???��??
        i++;    //???��?��??1us
        DQ = 1; //??��?��???
        i++;
        i++;    //?????��?��????��?????��?
        b = DQ; //????????
        i = 8;
        while (i > 0)
            i--; //???��????60us
        i_b = b;
        rdbyte = (i_b << 7) | (rdbyte >> 1); //????????????????����??7??????��???????????��???rdbyte????1??
    }
    return rdbyte;
}
//----------------------????????????---------------------------
void get_temp()
{
    init_temp();      //??????????????????????????
    wr_temp(0xcc);    //????ROM
    wr_temp(0x44);    //????????��???
    delay_ms(1000);   //????????��????��??
    init_temp();      //??DS18B20????
    wr_temp(0xcc);    //????ROM
    wr_temp(0xbe);    //???????��
    low = rd_temp();  //??????8??
    high = rd_temp(); //??????8??
    temp = high;
    temp <<= 8;
    temp = temp | low;        //??????????8??????8??????
    f_temp = temp * 0.0625;   //???????????��????12?? ��?��?????0.0625??
    temp = f_temp * 10 + 0.5; //???��????��????????��????
    d2 = temp / 100;          //??????????????
    d1 = temp % 100 / 10;     //??????????????
    d0 = temp % 10;           //????????????��???
}
//-----------------?��????------------------------
void main()
{
    init(); //lcd??????
    while (1)
    {
        get_temp(); //????????
        dat_dis();  //????????
    }
}