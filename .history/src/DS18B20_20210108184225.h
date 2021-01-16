#ifndef _INC_DS18B20
#define _INC_DS18B20
#define uchar unsigned char
#define uint unsigned int
#endif
sbit DS18B20_pin = P2 ^ 4;

void Delay_ds18b20(uint t) //ר�ó���ȷ��ʱ10us
{
    int i;
    while (t--)
    {
        for (i = 0; i < 12; i++)
            ;
    }
}

uint int_ds18b20()
{
    int i;
    DS18B20_pin = 0; //�������ߣ�������λ�ź�
    i = 80;
    while (i > 0)
        i--;         //��ʱ480~960us
    DS18B20_pin = 1; //��������
    i = 4;
    while (i > 0)
        i--; //��ʱ15~60us
    while (DS18B20_pin)
        ; //�ȴ�����Ӧ������
    i = 70;
    while (i > 0)
        i--; //��ʱ����480us
}

//��DS18B20дһ���ֽ�

void Write_DS18B20(uint dat)
{
    int i, j;
    bit testb;
    for (j = 8; j > 0; j--)
    {
        testb = dat & 0x01;
        dat = dat >> 1;
        if (testb) //д1
        {
            DS18B20_pin = 0; //�������ߣ�����дʱ��϶
            i++;             //��ʱ����1us
            DS18B20_pin = 1; //��������
            i = 8;
            while (i > 0)
                i--; //��ʱ����60us����DS18B20����
        }
        else //д0
        {
            DS18B20_pin = 0; //�������ߣ�����дʱ��϶
            i = 8;
            while (i > 0)
                i--;         //��������60us����DS18B20����
            DS18B20_pin = 1; //��������
            i++;
            i++;
        }
    }
}

//��DS18B20��ȡһ���ֽ�

uchar Read_DS18B20()
{
    int i, j;
    bit b; //�����Ž��յ���1���ֽ�
    uchar i_b;
    uchar rdbyte;
    for (j = 8; j > 0; j--)
    {
        DS18B20_pin = 0; //�������ߣ�������ʱ϶
        i++;             //��ʱ����1us
        DS18B20_pin = 1; //�ͷ�����
        i++;
        i++;             //��һ��ʱ���������ͷ�
        b = DS18B20_pin; //��ȡ����
        i = 8;
        while (i > 0)
            i--; //��ʱ����60us
        i_b = b;
        rdbyte = (i_b << 7) | (rdbyte >> 1); //����ȡ����һλֵ����7λ����Ŷ�ȡ�����ݱ���rdbyte����1λ
    }
    return rdbyte;
}

void DS18B20_Read_id()
{
    uchar id_u1, id_u2 , id_u3 , id_u4 , id_u5 , id_u6 , id_u7 , id_u8;
    int_ds18b20();  //��ʼ������λ����ȡӦ���ź�
    Write_DS18B20(0xf0);  //��ȡid
    u1 = Read_DS18B20();  //��ȡ8λ
    u2 = Read_DS18B20();  //��ȡ8λ
    u3 = Read_DS18B20();  //��ȡ8λ
    u4 = Read_DS18B20();  //��ȡ8λ
    u5 = Read_DS18B20();  //��ȡ8λ
    u6 = Read_DS18B20();  //��ȡ8λ
    u7 = Read_DS18B20();  //��ȡ8λ
    u8 = Read_DS18B20();  //��ȡ8λ
}
//docker run -d -p 9000:9000 -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data -v /file/portainer_web:/public portainer/portainer:1.20.2

uint DS18B20_Read_tem()
{
    uchar high, low;
    uint temp;
    float f_temp;

    int_ds18b20();  //��ʼ������λ����ȡӦ���ź�
    Write_DS18B20(0xcc);  //����ROM
    Write_DS18B20(0x44);  //��ʼ�¶�ת��
    delay(1000); //�ȴ��¶�ת�����

    int_ds18b20(); //��DS18B20��λ
    Write_DS18B20(0xcc); //����ROM
    Write_DS18B20(0xbe); //���ݴ���

    low = Read_DS18B20();  //��ȡ��8λ
    high = Read_DS18B20(); //��ȡ��8λ
    temp = high;

    temp <<= 8;
    temp = temp | low;        //����ȡ�ĵ�8λ�͸�8λ�ϲ�

    f_temp = temp * 0.0625;   //�¶��ڼĴ�����Ϊ12λ �ֱ���λ0.0625��
    temp = f_temp * 10 + 0.5; //��ȷ��ʮ��λ����������
    return temp;
}