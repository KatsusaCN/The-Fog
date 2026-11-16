#include"15W4Kxxxx.h"
#include"Keyboard.h"
unsigned char key[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},lock[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void Keyinit()
{
	P0M0 = 0x00; P0M1 = 0x00; 
	P1M0 = 0x00; P1M1 = 0x00; 
	P2M0 = 0x00; P2M1 = 0x00; 
	P3M0 = 0x00; P3M1 = 0x00; 
	P4M0 = 0x00; P4M1 = 0x00; 
	P5M0 = 0x00; P5M1 = 0x00; 
	P6M0 = 0x00; P6M1 = 0x00; 
	P7M0 = 0x00; P7M1 = 0x00; 
}
void KeyScan()
{
	unsigned char scan[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},i;
	KeyI1=1;KeyI2=1;KeyI3=1;KeyI4=1;
	KeyO1=0;KeyO2=1;KeyO3=1;KeyO4=1;
	if(KeyI1==0) scan[0]=1;
	if(KeyI2==0) scan[4]=1;
	if(KeyI3==0) scan[8]=1;
	if(KeyI4==0) scan[12]=1;
	KeyO1=1;KeyO2=0;
	if(KeyI1==0) scan[1]=1;
	if(KeyI2==0) scan[5]=1;
	if(KeyI3==0) scan[9]=1;
	if(KeyI4==0) scan[13]=1;
	KeyO2=1;KeyO3=0;
	if(KeyI1==0) scan[2]=1;
	if(KeyI2==0) scan[6]=1;
	if(KeyI3==0) scan[10]=1;
	if(KeyI4==0) scan[14]=1;
	KeyO3=1;KeyO4=0;
	if(KeyI1==0) scan[3]=1;
	if(KeyI2==0) scan[7]=1;
	if(KeyI3==0) scan[11]=1;
	if(KeyI4==0) scan[15]=1;
	for(i=0;i<=15;i++)
	{
		if(scan[i]==1)
		{
			key[i]=!lock[i];
			lock[i]=1;
		}
		else
		{
			key[i]=0;
			lock[i]=0;
		}
	}
}