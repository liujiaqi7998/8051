#ifndef DS1302_H
#define DS1302_H
#define uchar unsigned char
#define uint unsigned int
#endif

 //这个模块内没有集成上拉电阻，使用时最好接上2
sbit CE = P2 ^ 5;;//RET,使能输入引脚，当读写时，置高位
sbit SCIO = P2 ^ 4;//IO     ，双向通信引脚，读写数据都是通过这个完成
sbit SCLK = P2 ^ 3;//SCLK，时钟信号

void DS1302_WriteByte(uchar byte)
{
    uint i;
    uint t = 0x01;
    for(i=0;i<8;i++){
        DSIO = byte & t;        
        t<<=1;
        DOWN();       //下降沿完成一个位的操作
    }
    SCLK = 1;//确保释放io引脚
}

/*------------------------------------
   Read函数
------------------------------------*/
uchar DS1302_ReadByte(uchar address)
{
    
}