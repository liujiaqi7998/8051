#ifndef _INC_QI51ARDUINO
#define _INC_QI51ARDUINO
#define uchar unsigned char
#define uint unsigned int
#endif
#include <reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <intrins.h>
#include <string.h>


sbit pin1 = P1 ^ 0;
sbit pin2 = P1 ^ 1;
sbit pin3 = P1 ^ 2;
sbit pin4 = P1 ^ 3;
sbit pin5 = P1 ^ 4;
sbit pin6 = P1 ^ 5;
sbit pin7 = P1 ^ 6;
sbit pin8 = P1 ^ 7;

sbit pin11 = P3 ^ 0;
sbit pin12 = P3 ^ 1;
sbit pin13 = P3 ^ 2;
sbit pin14 = P3 ^ 3;
sbit pin15 = P3 ^ 4;
sbit pin16 = P3 ^ 5;
sbit pin17 = P3 ^ 6;


void loop();
void setup();
void Serial_begin(bit btl);
void delay(unsigned int wait_time);
void main(void);

void delay(unsigned int wait_time) //1ms ??
{
	unsigned int i, j;
	for (j = wait_time; j > 0; j--)
		for (i = 112; i > 0; i--)
			_nop_;
}
void delaymicroseconds(unsigned int wait_time) //1ms ??
{
	if (wait_time == 0)
		return;
	wait_time = wait_time / 10;
	while (wait_time--)
		;
}
void Serial_begin(bit btl)
{
	TMOD = 0x20;
	SCON = 0x50;
	TH1 = btl;
	TL1 = TH1;
	PCON = 0x00;
	EA = 1;
	ES = 1;
	TR1 = 1;
}

/*????jb????*/
void main(void)
{
	setup();
	while (1)
	{
		loop();
	}
}
