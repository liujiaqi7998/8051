#ifndef _INC_24C02
#define _INC_24C02
#define uchar unsigned char
#define uint unsigned int
#endif

//���пƼ�������: 0xA0

void delay();                      //��ʱms
void iic_start();                  //�����ź�
void iic_init();                   //���߳�ʼ��
void iic_stop();                   //ֹͣ�ź�
void iic_sendByte(uchar byteData); //mcu����һ���ֽ�
uchar iic_readByte();              //��һ���ֽ�
int iic_checkACK();                //����Ӧ���ź�
void iic_sendACK(int b_ACK);       //����Ӧ����Ӧ���ź�

void AT24C02_writeByte(uchar address, uchar dataByte) //��24c02дһ�ֽ�����
{
    iic_start();
    iic_sendByte(0xa0);    //mcuд������,ǰ4λ�̶�1010,����λ��ַ0,ĩλ0��д  1010000 R/W
    iic_checkACK();        //mcu����Ӧ���ź�,����Ƿ���Ӧ��
    iic_sendByte(address); //׼����ָ����ַ��д��
    iic_checkACK();
    iic_sendByte(dataByte); //д����
    iic_checkACK();
    iic_stop();
    delay(2);
    //���ֽ�д��ʱ,24c02�ڽ��յ�ֹͣ�źź����ݲ�д���ڲ�,����Ҫʱ��
    //���������ʱ���ڲ�����Ӧ�����ϵ��κ�����,����mcu��2�������ϵĵȴ�
}

void AT24C02_writeData(uchar address, uchar numBytes, uchar *buf) //д�����ⳤ������
{
    while (numBytes--)
    {
        AT24C02_writeByte(address++, *buf++);
    }
}

void AT24C02_readData(uchar beginAddr, uchar dataSize, uchar *buf) //��ȡ���ⳤ���ֽ�
{
    iic_start();             //��ʼ�ź�
    iic_sendByte(0xa0);      //������,д
    iic_checkACK();          //����Ӧ���ź�
    iic_sendByte(beginAddr); //���͵�ַ
    iic_checkACK();          //����Ӧ���ź�
    iic_start();             //������ʼ�ź�
    iic_sendByte(0xa1);      //������,��
    iic_checkACK();          //����Ӧ���ź�
    while (dataSize--)       //��ȡdataSize���ֽ�
    {
        *buf++ = iic_readByte(); //��ȡһ�����ֽڲ����浽������buf��
        iic_sendACK(dataSize);   //����Ӧ��,��dataSizeΪ0ʱ���ͷ�Ӧ��
    }
    iic_stop(); //����ֹͣ�ź�
}