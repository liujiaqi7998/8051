#ifndef _INC_SR04
#define _INC_SR04
#define uchar unsigned char
#define uint unsigned int
#endif
//���Ծ��� = ( �ߵ�ƽʱ�� * ����(340M/S) ) / 2;

sbit ECHO_port = P2 ^ 4;
sbit TRIG_port = P2 ^ 3;

void delay(unsigned int wait_time);
void delaywhile(unsigned int wait_time); //1ms ??

void StartSR04() //����ģ��
{
    TRIG_port = 0;
    delaywhile(1);
    TRIG_port = 1; //����һ��ģ��
    delaywhile(2);
    TRIG_port = 0;
}

void SR04_Init()
{
	TMOD|=0x01;
	TH0=0;
	TL0=0;
}



float CSB_GetOnce()//�õ�һ�γ��������ģ��ľ���
{
	CSB_Rstart();
	while(!ECHO_port);//��EchoΪ��ʱ�ȴ�
	starttime();//��������
	while(ECHO_port);//��EchoΪ1�������ȴ�
	TR0=0;//�رռ���
	return CSB_GetDistance();//����
}

