#include "qi51arduino.h"
#include "lcd12864.h"
#include "DS1302.h"

sbit IRIN = P3 ^ 2;

uchar code IC_DAT[] = {
    ""};

void IrInit()
{
    IT0 = 1;  //�½��ش���
    EX0 = 1;  //���ж�0����
    EA = 1;   //�����ж�
    IRIN = 1; //��ʼ���˿�
}

void setup()
{
    IrInit();

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
    if (IRIN == 0)   //ȷ���Ƿ���Ľ��յ���ȷ���ź�
    {
        err = 1000; //1000*10us=10ms,����˵�����յ�������ź�
        /*������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ������ó��������ʱ
		�������������*/
        while ((IRIN == 0) && (err > 0)) //�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ
        {
            delaywhile(1);
            err--;
        }
        if (IRIN == 1) //�����ȷ�ȵ�9ms�͵�ƽ
        {
            err = 500;
            while ((IRIN == 1) && (err > 0)) //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
            {
                delaywhile(1);
                err--;
            }
            for (k = 0; k < 4; k++) //����4������
            {
                for (j = 0; j < 8; j++) //����һ������
                {
                    err = 60;
                    while ((IRIN == 0) && (err > 0)) //�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
                    {
                        delaywhile(1);
                        err--;
                    }
                    err = 500;
                    while ((IRIN == 1) && (err > 0)) //����ߵ�ƽ��ʱ�䳤�ȡ�
                    {
                        delaywhile(10); //0.1ms
                        Time++;
                        err--;
                        if (Time > 30)
                        {
                            return;
                        }
                    }
                    IrValue[k] >>= 1; //k��ʾ�ڼ�������
                    if (Time >= 8)    //����ߵ�ƽ���ִ���565us����ô��1
                    {
                        IrValue[k] |= 0x80;
                    }
                    Time = 0; //����ʱ��Ҫ���¸�ֵ
                }
            }
        }
        if (IrValue[2] != ~IrValue[3])
        {
            return;
        }
    }
}