#ifndef KEYBOARD_H
#define KEYBOARD_H
sbit KeyI1 =P3^2;
sbit KeyI2 =P3^4;
sbit KeyI3 =P5^1;
sbit KeyI4 =P3^6;
sbit KeyO4 =P3^3;
sbit KeyO3 =P5^0;
sbit KeyO2 =P3^5;
sbit KeyO1 =P3^7;
extern unsigned char key[16],lock[16];
void Keyinit();
void KeyScan();
#endif