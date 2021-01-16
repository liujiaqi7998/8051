#include "qi51arduino.h"

#define GPIO_KEY P0

uint KeyValue; //������Ŷ�ȡ���ļ�ֵ

sbit k1 = pin28;
sbit k2 = pin27;

void Keypros();
void KeyDown();

void setup()
{
}

void loop()
{
    Keypros();
}

void Keypros()
{
    if (k1 == 0)
    {
        delay(10); //��������
        if (k1 == 0)
        {
        }
        while (!k1)
            ;
    }

    if (k2 == 0)
    {
        delay(10); //��������
        if (k2 == 0)
        {
        }
        while (!k2)
            ;
    }
}

void KeyDown()
{
    char a = 0;
    GPIO_KEY = 0x0f;
    if (GPIO_KEY != 0x0f) //��ȡ�����Ƿ���
    {
        delay(1000);          //��ʱ10ms��������
        if (GPIO_KEY != 0x0f) //�ٴμ������Ƿ���
        {
            //������
            GPIO_KEY = 0X0F;
            switch (GPIO_KEY)
            {
            case (0X07):
                KeyValue = 0;
                break;
            case (0X0b):
                KeyValue = 1;
                break;
            case (0X0d):
                KeyValue = 2;
                break;
            case (0X0e):
                KeyValue = 3;
                break;
            }
            //������
            GPIO_KEY = 0XF0;
            switch (GPIO_KEY)
            {
            case (0X70):
                KeyValue = KeyValue;
                break;
            case (0Xb0):
                KeyValue = KeyValue + 4;
                break;
            case (0Xd0):
                KeyValue = KeyValue + 8;
                break;
            case (0Xe0):
                KeyValue = KeyValue + 12;
                break;
            }
            while ((a < 50) && (GPIO_KEY != 0xf0)) //��ⰴ�����ּ��
            {
                delay(1000);
                a++;
            }
        }
    }
}