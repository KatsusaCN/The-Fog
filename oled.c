#include"15W4Kxxxx.h"
#include"oled.h"
#include"pictures.h"
unsigned char xdata frame[8][128],cache[8][128];
unsigned char (*FrameIndex[2])[128]={frame,cache};
void ByteWriting(unsigned char dat,unsigned char cmd)
{
	unsigned char i;
	OLED_DC=cmd;
	OLED_CS=0;
	for(i=0;i<8;i++)
	{
		OLED_SCLK=0;
		if(dat & 0x80) OLED_IN=1;
		else OLED_IN=0;
		OLED_SCLK=1;
		dat<<=1;
	}
	OLED_CS=1;
}

void Refresh(U8 mark)
{
	unsigned char i,j;
	ByteWriting(0x20,0);
	ByteWriting(0x00,0);//水平寻址模式
	ByteWriting(0x21,0);
	ByteWriting(0x00,0);
	ByteWriting(0x7F,0);//列地址范围
	ByteWriting(0x22,0);
	ByteWriting(0x00,0);
	ByteWriting(0x07,0);//页地址范围
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=127;j++)
		{
			ByteWriting(FrameIndex[mark][i][j],1);
		}
	}
}

void PicWriting_Cover(U8 mark,U8 code *pic,U8 lin,U8 han,int x,int y)
{
	unsigned char adx,ady,tem,bitt,i,npag;
	for(ady=0;ady<han;ady++)
	{
		for(adx=0;adx<lin;adx++)
		{
			if(x+adx>=0 && x+adx<=127 && y+ady>=0 && y+ady<=63)
			{
				npag=ady/8;
				bitt=(pic[npag*lin+adx]>>(ady%8)) & 1;
				if(bitt==1)
				{
					tem=bitt<<((y+ady)%8);
					FrameIndex[mark][(y+ady)/8][x+adx] |= tem;
				}
				else
				{
					tem=0xFE;
					for(i=0;i<((y+ady)%8);i++)
					{
						tem<<=1;
						tem+=1;
					}
					FrameIndex[mark][(y+ady)/8][x+adx] &= tem;
				}
			}
		}
	}
}

void PicWriting_Overlay(U8 mark,U8 code *pic,U8 lin,U8 han,int x,int y)
{
	unsigned char adx,ady,tem,bitt,npag;
	for(ady=0;ady<han;ady++)
	{
		for(adx=0;adx<lin;adx++)
		{
			if(x+adx>=0 && x+adx<=127 && y+ady>=0 && y+ady<=63)
			{
				npag=ady/8;
				bitt=(pic[npag*lin+adx]>>(ady%8)) & 1;
				tem=bitt<<((y+ady)%8);
				FrameIndex[mark][(y+ady)/8][x+adx] |= tem;
			}
		}
	}
}

void PicClean(U8 mark,U8 lin,U8 han,int x,int y)
{
	unsigned char adx,ady,tem,i;
	for(ady=0;ady<han;ady++)
	{
		for(adx=0;adx<lin;adx++)
		{
			if(x+adx>=0 && x+adx<=127 && y+ady>=0 && y+ady<=63)
			{
				tem=0xFE;
				for(i=0;i<((y+ady)%8);i++)
				{
					tem<<=1;
					tem+=1;
				}
				FrameIndex[mark][(y+ady)/8][x+adx] &= tem;
			}
		}
	}
}

void StrWriting(U8 mark,U8 *str,int x,int y,U8 mode)
{
	unsigned char i=0;
	while(str[i]!='\0')
	{
		if(mode==1) PicWriting_Cover(mark,F8X16+(str[i]-32)*16,8,16,x+i*8,y);
		else PicWriting_Overlay(mark,F8X16+(str[i]-32)*16,8,16,x+i*8,y);
		i++;
	}
}

void OLEDinit()
{
	unsigned char i,j;
	OLED_RES=1;
	Delay50ms();
	OLED_RES=0;
	Delay50ms();
	OLED_RES=1;
	ByteWriting(0xAE,0);//--turn off oled panel
	ByteWriting(0x00,0);//---set low column address
	ByteWriting(0x10,0);//---set high column address
	ByteWriting(0x40,0);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	ByteWriting(0x81,0);//--set contrast control register
	ByteWriting(0xCF,0); // Set SEG Output Current Brightness
	ByteWriting(0xA1,0);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	ByteWriting(0xC8,0);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	ByteWriting(0xA6,0);//--set normal display
	ByteWriting(0xA8,0);//--set multiplex ratio(1 to 64)
	ByteWriting(0x3f,0);//--1/64 duty
	ByteWriting(0xD3,0);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	ByteWriting(0x00,0);//-not offset
	ByteWriting(0xd5,0);//--set display clock divide ratio/oscillator frequency
	ByteWriting(0x80,0);//--set divide ratio, Set Clock as 100 Frames/Sec
	ByteWriting(0xD9,0);//--set pre-charge period
	ByteWriting(0xF1,0);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	ByteWriting(0xDA,0);//--set com pins hardware configuration
	ByteWriting(0x12,0);
	ByteWriting(0xDB,0);//--set vcomh
	ByteWriting(0x40,0);//Set VCOM Deselect Level
	ByteWriting(0x20,0);//-Set Page Addressing Mode (0x00/0x01/0x02)
	ByteWriting(0x00,0);//
	ByteWriting(0x8D,0);//--set Charge Pump enable/disable
	ByteWriting(0x14,0);//--set(0x10) disable
	ByteWriting(0xA4,0);// Disable Entire Display On (0xa4/0xa5)
	ByteWriting(0xA6,0);// Disable Inverse Display On (0xa6/a7) 
	ByteWriting(0xAF,0);//--turn on oled panel
	ByteWriting(0xAF,0); /*display ON*/ 
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=127;j++)
		{
			frame[i][j]=0;
		}
	}
	Refresh(0);
}

void Delay50ms()	//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 26;
	k = 223;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}