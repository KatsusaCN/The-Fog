#ifndef __DS1302_H_
#define __DS1302_H_

//---包含头文件---//
#include"15W4Kxxxx.h"
#include<intrins.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif
#define BURST_WRITE 0xBE
#define BURST_READ 0xBF
//---定义ds1302使用的IO口---//
sbit DSIO=P6^0;
sbit RST=P6^1;
sbit SCLK=P5^3;

//---定义全局函数---//
void DS1302WriteByte(uchar dat);
unsigned char DS1302ReadByte();
void Ds1302Write(uchar addr, uchar dat);
unsigned char Ds1302Read(uchar addr);
unsigned char DataLoad();

//---加入全局变量--//
extern uchar code TIME[7];	//加入全局变量
extern unsigned char idata EasterEgg;
#endif