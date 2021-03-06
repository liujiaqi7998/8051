#ifndef _INC_SR04
#define _INC_SR04
#define uchar unsigned char
#define uint unsigned int
#endif

sbit ECHO_port = P3 ^ 6;
sbit TRIG_port = P3 ^ 7;

void delay(unsigned int wait_time);
void delaywhile(unsigned int wait_time); //1ms ??

void StartSR04() //启动模块
{
    TRIG_port = 0;
    delaywhile(1);
    TRIG_port = 1; //启动一次模块
    delaywhile(2);
    TRIG_port = 0;
}

void SR04_Init()
{
    TMOD = 0x01; //打开定时器0
    TH0 = 0;     //复位定时器
    TL0 = 0;     //复位定时器
}

uint SR04_GetDistance()
{
    //测试距离 = (高电平时间*声速(340M/S) ) / 2;
    unsigned int time = TH0 * 256 + TL0; //得到总时间，单位us,高8位(只有低8位溢出才会用高8位)加*256低8位
    uint distance = time * 0.017;        //算得厘米(0.034/2)
    TH0 = 0;                             //
    TL0 = 0;                             //清空定时器
    return distance;
}

uint SR04_GetOnce()            //得到一次超声波测距模块的距离
{                              //
    StartSR04();               //TRIG拉高一次通知超声波模块
    while (!ECHO_port)         //
        ;                      //当Echo为零时，超声波接到消息，测距开始，等待
    TR0 = 1;                   //开启计数，打开定时器0
    while (ECHO_port)          //
        ;                      //当Echo为1计数并等待
    TR0 = 0;                   //关闭计数，关闭定时器0
    return SR04_GetDistance(); //计算
}
