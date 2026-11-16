#ifndef OLED_H
#define OLED_H
typedef unsigned char U8;
sbit OLED_CS=P1^2;
sbit OLED_DC=P1^3;
sbit OLED_IN=P1^4;
sbit OLED_SCLK=P1^5;
sbit OLED_RES=P7^4;
extern unsigned char xdata frame[8][128],cache[8][128];
extern unsigned char (*FrameIndex[2])[128];
void ByteWriting(unsigned char dat,unsigned char cmd);
void Refresh(U8 mark);
void PicWriting_Cover(U8 mark,U8 code *pic,U8 lin,U8 han,int x,int y);
void PicWriting_Overlay(U8 mark,U8 code *pic,U8 lin,U8 han,int x,int y);
void PicClean(U8 mark,U8 lin,U8 han,int x,int y);
void StrWriting(U8 mark,U8 *str,int x,int y,U8 mode);
void OLEDinit();
void Delay50ms();
#endif