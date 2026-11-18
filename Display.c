#include"15W4Kxxxx.h"
#include"Display.h"
const unsigned char DisNum[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
void DisplayIni()
{
	  P0M0 = 0x00; P0M1 = 0x00; 
    P1M0 = 0x00; P1M1 = 0x00; 
    P2M0 = 0x00; P2M1 = 0x00; 
    P3M0 = 0x00; P3M1 = 0x00; 
    P4M0 = 0x1E; P4M1 = 0x00; 
    P5M0 = 0x00; P5M1 = 0x00; 
    P6M0 = 0x00; P6M1 = 0x00; 
    P7M0 = 0x00; P7M1 = 0x00; 
}

void Delay1ms()	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void NumDisplay(unsigned char a,char n)
{
	n=0x10>>n;
	P2=DisNum[a];
	P4=n;
}

void Roll(char n)
{
	if(n<0 || n>3) return;
	switch(n)
	{
		case 0:
			P2=0xAD;
			P4=0x10;
			Delay1ms();
			P4=0x00;
			P2=0xDE;
			P4=0x08;
			Delay1ms();
			P4=0x00;
			break;
		case 1:
			P2=0xF3;
			P4=0x10;
			Delay1ms();
			P4=0x00;
			P2=0xAD;
			P4=0x08;
			Delay1ms();
			P4=0x00;
			P2=0xDE;
			P4=0x04;
			Delay1ms();
			P4=0x00;
			break;
		case 2:
			P2=0xF3;
			P4=0x08;
			Delay1ms();
			P4=0x00;
			P2=0xAD;
			P4=0x04;
			Delay1ms();
			P4=0x00;
			P2=0xDE;
			P4=0x02;
			Delay1ms();
			P4=0x00;
			break;
		case 3:
			P2=0xF3;
			P4=0x04;
			Delay1ms();
			P4=0x00;
			P2=0xAD;
			P4=0x02;
			Delay1ms();
			P4=0x00;
			break;
	}
}