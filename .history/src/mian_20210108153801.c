#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit lcden = P3 ^ 4; //¶¨ÒålcdÊ¹ÄÜ¶Ë
sbit lcdrs = P3 ^ 5; //¶¨ÒålcdÊý¾ÝÃüÁîÑ¡Ôñ¶Ë
sbit lcdwr = P3 ^ 6; //¶¨Òålcd¶ÁÐ´Ñ¡Ôñ¶Ë
sbit lcdrd = P3 ^ 7; //¶¨Òå²¢´®Ñ¡Ôñ¶Ë
sbit DQ = P2 ^ 2;    //¶¨ÒåDS18B20Êý¾ÝÏßÒý½Å¶Ë
uchar high, low;
char a, d2, d1, d0;
float f_temp;
uint i, j, temp;
uchar code line1[] = {"µç¹¤µç×Ó´´ÐÂÐ­»á"};
uchar code line2[] = "µ±Ç°ÎÂ¶È£º";
uchar code line3[] = "00.0¶È";
//-------------------ºÁÃë¼¶ÑÓÊ±º¯Êý-------------------------
void delay_ms(uint z) //ÑÓÊ±zºÁÃë
{
    uint x, y;
    for (x = z; x > 0; x--)
        for (y = 115; y > 0; y--)
            ;
}
//------------lcdÐ´Ö¸Áîº¯Êý-------------
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
//-----------lcdÐ´Êý¾Ýº¯Êý-----------
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

//-----------------------ÓÃ»§½çÃæÎÄ×ÖÏÔÊ¾º¯Êý--------------------------
void face_dis()
{
    wr_cmd(0x30); //Ñ¡Ôñ¹¦ÄÜ£º8Î»Êý¾Ý»ù±¾Ö¸Áî²Ù×÷
    wr_cmd(0x0c); //ÕûÌåÏÔÊ¾¿ª£¬²»ÏÔÊ¾¹â±ê
    wr_cmd(0x01); //lcdÇåÆÁ
    wr_cmd(0x02); //ÓÎ±ê¹éÔ­µã
    wr_cmd(0x80);
    for (a = 0; a < 16; a++) //Ð´ÈëµÚ¶þÐÐÊý¾Ý
    {
        wr_dat(line1[a]);
    }

    wr_cmd(0x90);            //ÉèÖÃµÚ¶þÐÐÆðÊ¼Î»
    for (a = 0; a < 10; a++) //Ð´ÈëµÚ¶þÐÐÊý¾Ý
    {
        wr_dat(line2[a]);
    }
    wr_cmd(0x8c);           //ÉèÖÃµÚÈýÐÐÆðÊ¼Î»
    for (a = 0; a < 6; a++) //Ð´ÈëµÚÈýÐÐÊý¾Ý
    {
        wr_dat(line3[a]);
    }
}
//------------------------ÓÃ»§½çÃæÊý¾ÝÏÔÊ¾º¯Êý-------------------------------
void dat_dis()
{
    wr_cmd(0x8c); //ÏÔÊ¾ÎÂ¶È
    wr_dat(0x30 + d2);
    wr_dat(0x30 + d1);
    wr_dat(0x2e); //Ð´Èë¡°.¡±ºÅ
    wr_dat(0x30 + d0);
}
//-----------------------------³õÊ¼»¯º¯Êý------------------------------------
void init()
{
    delay_ms(20); //µÈ´ýÒº¾§ÊäÈëµçÔ´ÎÈ¶¨
    lcdrd = 1;    //Ñ¡¶¨lcdÓëµ¥Æ¬»ú²¢ÐÐÁ¬½Ó
    lcdwr = 0;    //ÒòÎªÎÒÃÇ²»ÐèÒª´ÓlcdÄ£¿é¶ÁÊý¾Ý£¬ËùÒÔ¿ÉÖ±½Ó½«´Ë¶Ë¿ÚÇåÁã£¬±ãÓÚÖ®ºóÀûÓÃ¾ØÕó¼üÅÌ
    face_dis();   //ÏÔÊ¾ÓÃ»§½çÃæ
}
//-----------------------»ñÎÂ²¿·Ö£º³õÊ¼»¯º¯Êý--------------------
void init_temp()
{
    DQ = 0; //À­µÍ×ÜÏß£¬²úÉú¸´Î»ÐÅºÅ
    i = 80;
    while (i > 0)
        i--; //ÑÓÊ±480~960us
    DQ = 1;  //À­¸ß×ÜÏß
    i = 4;
    while (i > 0)
        i--; //ÑÓÊ±15~60us
    while (DQ)
        ; //µÈ´ý²úÉúÓ¦´ðÂö³å
    i = 70;
    while (i > 0)
        i--; //ÑÓÊ±ÖÁÉÙ480us
}
//------------------»ñÎÂ²¿·Ö£ºÐ´º¯Êý-------------------------------
void wr_temp(uchar dat) //Ð´1¸ö×Ö½Ú
{
    bit testb;
    for (j = 8; j > 0; j--)
    {
        testb = dat & 0x01;
        dat = dat >> 1;
        if (testb) //Ð´1
        {
            DQ = 0; //À­µÍ×ÜÏß£¬²úÉúÐ´Ê±¼äÏ¶
            i++;    //ÑÓÊ±´óÓÚ1us
            DQ = 1; //À­¸ß×ÜÏß
            i = 8;
            while (i > 0)
                i--; //ÑÓÊ±ÖÁÉÙ60us£¬¹©DS18B20²ÉÑù
        }
        else //Ð´0
        {
            DQ = 0; //À­µÍ×ÜÏß£¬²úÉúÐ´Ê±¼äÏ¶
            i = 8;
            while (i > 0)
                i--; //±£³ÖÖÁÉÙ60us£¬¹©DS18B20²ÉÑù
            DQ = 1;  //À­¸ß×ÜÏß
            i++;
            i++;
        }
    }
}
//------------------»ñÎÂ²¿·Ö£º¶Áº¯Êý-------------------------------
uchar rd_temp() //¶Á1¸ö×Ö½Ú
{
    bit b; //¶¨Òå´æ·Å½ÓÊÕµ½µÄ1¸ö×Ö½Ú
    uchar i_b;
    uchar rdbyte;
    for (j = 8; j > 0; j--)
    {
        DQ = 0; //À­µÍ×ÜÏß£¬²úÉú¶ÁÊ±Ï¶
        i++;    //ÑÓÊ±´óÓÚ1us
        DQ = 1; //ÊÍ·Å×ÜÏß
        i++;
        i++;    //¸øÒ»¶¨Ê±¼äÈÃ×ÜÏßÊÍ·Å
        b = DQ; //¶ÁÈ¡Êý¾Ý
        i = 8;
        while (i > 0)
            i--; //ÑÓÊ±ÖÁÉÙ60us
        i_b = b;
        rdbyte = (i_b << 7) | (rdbyte >> 1); //½«¶ÁÈ¡µ½µÃÒ»Î»Öµ×óÒÆ7Î»£¬´æ·Å¶ÁÈ¡µÄÊý¾Ý±äÁ¿rdbyteÓÒÒÆ1Î»
    }
    return rdbyte;
}
//----------------------ÎÂ¶È»ñÈ¡º¯Êý---------------------------
void get_temp()
{
    init_temp();      //³õÊ¼»¯£¬¸´Î»²¢»ñÈ¡Ó¦´ðÐÅºÅ
    wr_temp(0xcc);    //Ìø¹ýROM
    wr_temp(0x44);    //¿ªÊ¼ÎÂ¶È×ª»»
    delay_ms(1000);   //µÈ´ýÎÂ¶È×ª»»Íê³É
    init_temp();      //½«DS18B20¸´Î»
    wr_temp(0xcc);    //Ìø¹ýROM
    wr_temp(0xbe);    //¶ÁÔÝ´æÆ÷
    low = rd_temp();  //¶ÁÈ¡µÍ8Î»
    high = rd_temp(); //¶ÁÈ¡¸ß8Î»
    temp = high;
    temp <<= 8;
    temp = temp | low;        //½«¶ÁÈ¡µÄµÍ8Î»ºÍ¸ß8Î»ºÏ²¢
    f_temp = temp * 0.0625;   //ÎÂ¶ÈÔÚ¼Ä´æÆ÷ÖÐÎª12Î» ·Ö±æÂÊÎ»0.0625¡ã
    temp = f_temp * 10 + 0.5; //¾«È·µ½Ê®·ÖÎ»£¬ËÄÉáÎåÈë
    d2 = temp / 100;          //ÏÔÊ¾Êý¾Ý£ºÊ®Î»
    d1 = temp % 100 / 10;     //ÏÔÊ¾Êý¾Ý£º¸öÎ»
    d0 = temp % 10;           //ÏÔÊ¾Êý¾Ý£ºÊ®·ÖÎ»
}
//-----------------Ö÷º¯Êý------------------------
void main()
{
    init(); //lcd³õÊ¼»¯
    while (1)
    {
        get_temp(); //»ñÈ¡ÎÂ¶È
        dat_dis();  //ÏÔÊ¾ÎÂ¶È
    }
}