#include "qi51arduino.h"

k1 = P2 ^ 7;
k2 = P2 ^ 6;

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
        delay(100); //消抖处理
        if (k1 == 0)
        {
            num++;
            if (num == 10)
            {
                num = 0;
            }
            AT24C02_writeByte(1, num); //在地址1内写入数据num
            delay(10);
            num = AT24C02_readData_Byte(1); //读取EEPROM地址1内的数据保存在num中
        }
        while (!k1)
            ;
    }

    if (k2 == 0)
    {
        delay(100); //消抖处理
        if (k2 == 0)
        {
            if (num == 0)
            {
                num = 10;
            }
            num--;
            AT24C02_writeByte(1, num); //在地址1内写入数据num
            delay(10);
            num = AT24C02_readData_Byte(1); //读取EEPROM地址1内的数据保存在num中
        }
        while (!k2)
            ;
    }
}