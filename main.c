#include"15W4Kxxxx.h"
#include"oled.h"
#include"pictures.h"
#include"Keyboard.h"
#include"ds1302.h"
#define Nowlevel NowLevel
unsigned char xdata RefMark=0,FrameNum=0,dic=0,page=0,PageMark=1,dat,NowLevel;
//RefMark：帧刷新标志；FrameNum：第几帧；dic：朝向；page：第几页；PageMark：翻页标志；CoverMark：封面标识；dat：存档；NowLevel：当前关卡；sel：选项标志；
unsigned char code title[][20]=
{
	{"1:2,4,5,6 and go"},
	{"2:dive further"},
	{"3:too many lies"},
	{"4:wrong at start"},
	{"5:Amnesia"}
};
unsigned char xdata map_1[]=
{
1,1,1,0,
1,0,0,0,
1,0,1,1,
0,0,0,1
};
unsigned char xdata map_2[]=
{
1,0,0,0,0,0,
0,0,1,1,1,1,
1,0,0,0,1,0,
1,1,1,0,1,0,
1,0,0,0,1,0,
0,0,1,0,0,0
};
unsigned char xdata map_3[]=
{
1,0,0,0,0,0,1,0,
1,1,0,1,1,1,1,0,
1,0,0,0,0,0,1,0,
0,0,1,1,1,0,1,0,
1,0,0,0,1,0,0,0,
1,1,1,0,1,0,1,1,
0,0,0,0,1,0,0,0,
0,1,0,1,0,0,1,1
};
unsigned char xdata map_4[]=
{
1,0,0,0,0,0,0,0,0,0,
1,1,0,1,1,1,1,1,1,1,
0,1,0,0,0,0,0,0,0,0,
0,1,0,1,0,1,1,1,0,1,
0,1,1,0,0,1,1,0,1,1,
0,0,1,0,1,0,1,0,0,0,
1,0,1,0,0,0,1,0,1,0,
0,0,1,1,1,0,0,0,0,1,
0,1,0,0,0,0,1,1,0,1,
0,0,0,1,0,1,1,1,0,0
};
unsigned char xdata map_5[]=
{
1,1,1,1,1,0,0,0,0,10,13,0,
1,0,0,0,0,0,1,1,1,1,1,15,
1,1,0,1,1,1,0,0,0,0,12,0,
0,1,0,0,0,0,0,1,1,1,1,1,
0,0,1,0,1,1,0,0,0,1,5,0,
1,0,0,0,1,0,1,1,0,1,1,0,
0,1,1,1,1,0,0,0,0,1,0,0,
0,0,0,1,1,6,1,1,1,1,0,1,
1,1,0,0,0,0,0,0,0,0,0,1,
1,0,0,1,1,1,1,1,0,1,1,1,
1,3,1,1,0,2,1,0,0,0,0,1,
0,0,0,0,0,1,1,1,1,1,1,1
};

unsigned char code map_5_code[]=
{
1,1,1,1,1,0,0,0,0,10,13,0,
1,0,0,0,0,0,1,1,1,1,1,15,
1,1,0,1,1,1,0,0,0,0,12,0,
0,1,0,0,0,0,0,1,1,1,1,1,
0,0,1,0,1,1,0,0,0,1,5,0,
1,0,0,0,1,0,1,1,0,1,1,0,
0,1,1,1,1,0,0,0,0,1,0,0,
0,0,0,1,1,6,1,1,1,1,0,1,
1,1,0,0,0,0,0,0,0,0,0,1,
1,0,0,1,1,1,1,1,0,1,1,1,
1,3,1,1,0,2,1,0,0,0,0,1,
0,0,0,0,0,1,1,1,1,1,1,1
};

unsigned char xdata *(maps[])={map_1,map_2,map_3,map_4,map_5};
char xdata x,y,CoverMark=1,sel=0;
int xdata rx,ry; 

void Timer0_Isr(void) interrupt 1
{
	RefMark=1;
	FrameNum=(FrameNum+1)%20;
}
void Timer0_Init(void)//20帧定时器
{
	AUXR &= 0x7F;//定时器时钟12T模式
	TMOD &= 0xF0;//设置定时器模式
	TL0 = 0x00;//设置定时初始值
	TH0 = 0x4C;//设置定时初始值
	TF0 = 0;//清除TF0标志
	ET0 = 1;//使能定时器0中断
	EA = 1;
}

int Ex_x(unsigned char x)
{
	return 64-4*(Nowlevel+1-x);
}	
int Ex_y(unsigned char y)
{
	return 40-4*(Nowlevel+1-y);
}	

void main()
{
	unsigned char i,j,DuoMark;
	Timer0_Init();
	Keyinit();
	OLEDinit();
	Refresh(0);
	dat=DataLoad();
	EasterEgg=Ds1302Read(0x81);
	EasterEgg%=10;
	TR0 = 1;//定时器0开始计时
	while(1)
	{
		if(RefMark==0) continue;
		if(PageMark==1)
		{
			PicClean(0,128,64,0,0);
			PicClean(1,128,64,0,0);
		}
		switch (page)
		{
			case 0:
				if(PageMark==1)
				{
					if(EasterEgg==9)
					{
						PicWriting_Cover(0,TheFuta_1,128,32,0,16);
						PicWriting_Cover(1,TheFuta_2,128,32,0,16);
					}
					else
					{
						PicWriting_Cover(0,TheFog_1,128,32,0,16);
						PicWriting_Cover(1,TheFog_2,128,32,0,16);
					}
					//PicWriting_Cover(0,F8X16+(EasterEgg+16)*16,8,16,0,0);
					//PicWriting_Cover(1,F8X16+(EasterEgg+16)*16,8,16,0,0);
					//PicWriting_Cover(0,wall_0,4,4,0,0);
					//PicWriting_Cover(1,wall_0,4,4,0,0);
					StrWriting(0,"Press 1 to Start",0,48,0);
					StrWriting(1,"Press 1 to Start",0,48,0);
					PageMark=0;
				}
				KeyScan();
				if(key[15]==1) dat=0;
				if(key[0]==1)
				{
					if(dat==0)
					{
						page=2;
						NowLevel=1;
					}
					else if(dat<=5)
					{
						page=1;
						NowLevel=dat;
					}
					PageMark=1;
					break;
				}
				if(FrameNum/10!=CoverMark)
				{
					CoverMark=FrameNum/10;
					Refresh(CoverMark);
				}
				RefMark=0;
				break;
			case 1:
				if(PageMark==1)
				{
					dic=3;
					StrWriting(0,"MENU",48,0,0);
					StrWriting(0,"Continue",32,16,0);
					StrWriting(0,"Reset",44,32,0);
					PageMark=0;
				}
				KeyScan();
				sel=(sel+key[5]-key[1])%2;
				PicClean(0,4,4,38,38);
				PicClean(0,4,4,26,22);
				if(sel==0) PicWriting_Cover(0,mes[dic],4,4,26,22);
				else if(sel==1) PicWriting_Cover(0,mes[dic],4,4,38,38);
				if(key[0]==1)
				{
					if(sel==0)
					{
						dic=0;
						page=2;
					}
					else if(sel==1)
					{
						Ds1302Write(0xC0,0x00);
						dat=0;
						page=0;
					}
					PageMark=1;
				}
				Refresh(0);
				RefMark=0;
				break;
			case 2:
				if(PageMark==1)
				{
					Ds1302Write(0xC0,NowLevel);
					DuoMark=0;
					StrWriting(0,title[NowLevel-1],0,0,0);
					StrWriting(1,title[NowLevel-1],0,0,0);
					if(NowLevel==5)
					{
						for(i=0;i<=143;i++) map_5[i]=map_5_code[i];
					}
					for(i=0;i<NowLevel*2+4;i++)
					{
						for(j=0;j<NowLevel*2+4;j++)
						{
							if(Ex_y(j)>16)
							{
								if((i==0||i==NowLevel*2+3) || (j==0||j==NowLevel*2+3))//边缘墙体
								{
									PicWriting_Cover(0,wall_0,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
									PicWriting_Cover(1,wall_0,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
									if(j>0 && (i==0 || i==NowLevel*2+3))
									{
										PicWriting_Overlay(0,wall_1,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
										PicWriting_Overlay(1,wall_1,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
									}
									if(j<NowLevel*2+3 && (i==0 || i==NowLevel*2+3))
									{
										PicWriting_Overlay(0,wall_2,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
										PicWriting_Overlay(1,wall_2,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
									}
									if(i>0 && (j==0 || j==NowLevel*2+3))
									{
										PicWriting_Overlay(0,wall_3,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
										PicWriting_Overlay(1,wall_3,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
									}
									if(i<NowLevel*2+3 && (j==0 || j==NowLevel*2+3))
									{
										PicWriting_Overlay(0,wall_4,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
										PicWriting_Overlay(1,wall_4,4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
									}
								}
								else//战争迷雾
								{
									PicWriting_Cover(0,fogs[0],4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
									PicWriting_Cover(1,fogs[1],4,4,64-(Nowlevel+2-i)*4,40-(Nowlevel+2-j)*4);
								}
							}
						}
					}
					x=0;
					y=NowLevel*2+1;
					PageMark=0;
				}
				for(i=0;i<3;i++)
				{
					for(j=0;j<=3;j++)
					{
						if((x+i-1)>=0 && (x+i-1)<=(NowLevel*2+1) && (y+j-1)>=0 && (y+j-1)<=(NowLevel*2+1))
						{
							PicWriting_Cover(0,fogs[0],4,4,Ex_x(x+i-1),Ex_y(y+j-1));
							PicWriting_Cover(1,fogs[1],4,4,Ex_x(x+i-1),Ex_y(y+j-1));
						}
					}
				}
				KeyScan();
				if((x+(key[6]-key[4])>=0) && (x+(key[6]-key[4])<=(NowLevel*2+1)) && (maps[NowLevel-1][y*(Nowlevel+1)*2+(x+key[6]-key[4])])%2 == 0) x=x+(key[6]-key[4]);
				if((y+(key[5]-key[1])>=0) && (y+(key[5]-key[1])<=(NowLevel*2+1)) && (maps[NowLevel-1][(y+key[5]-key[1])*(Nowlevel+1)*2+x])%2 == 0) y=y+(key[5]-key[1]);
				if(key[5]!=key[1]) dic=(key[5]-key[1]+1)/2;
				if(key[6]!=key[4]) dic=2+(key[6]-key[4]+1)/2;
				if((maps[NowLevel-1][y*(Nowlevel+1)*2+x]) == 2)
				{
					maps[NowLevel-1][y*(Nowlevel+1)*2+x]=0;
					for(i=0;i<=Nowlevel*2+1;i++)
					{
						for(j=0;j<=Nowlevel*2+1;j++)
						{
							if(maps[NowLevel-1][i*(Nowlevel+1)*2+j]>=3) maps[NowLevel-1][i*(Nowlevel+1)*2+j]-=3;
						}
					}
				}
				if(maps[NowLevel-1][y*(Nowlevel+1)*2+x] == 4 || maps[NowLevel-1][y*(Nowlevel+1)*2+x] == 6)
				{
					if(DuoMark==0) DuoMark=maps[NowLevel-1][y*(Nowlevel+1)*2+x];
					else if(maps[NowLevel-1][y*(Nowlevel+1)*2+x] != DuoMark)
					{
						for(i=0;i<=Nowlevel*2+1;i++)
						{
							for(j=0;j<=Nowlevel*2+1;j++)
							{
								if(maps[NowLevel-1][i*(Nowlevel+1)*2+j] == DuoMark+3) maps[NowLevel-1][i*(Nowlevel+1)*2+j]=0;
								if(maps[NowLevel-1][i*(Nowlevel+1)*2+j] == maps[NowLevel-1][y*(Nowlevel+1)*2+x]+3) maps[NowLevel-1][i*(Nowlevel+1)*2+j]=1;
							}			
						}
					}
				}
				PicWriting_Cover(0,mes[dic],4,4,Ex_x(x),Ex_y(y));
				PicWriting_Cover(1,mes[dic],4,4,Ex_x(x),Ex_y(y));
				for(i=0;i<3;i++)
				{
					for(j=0;j<3;j++)
					{
						if(i==1 && j==1) continue;
						if((x+i-1)>=0 && (x+i-1)<=(NowLevel*2+1) && (y+j-1)>=0 && (y+j-1)<=(NowLevel*2+1))
						{
							if(maps[NowLevel-1][(y+j-1)*(Nowlevel+1)*2+x+i-1]%2 ==0)
							{
								if(x+i-1==NowLevel*2+1 && y+j-1==0)
								{
									PicWriting_Cover(0,final,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
									PicWriting_Cover(1,final,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								}
								else
								{
									PicClean(0,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
									PicClean(1,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								}
							}
							else
							{
								PicWriting_Cover(0,wall_0,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								PicWriting_Cover(1,wall_0,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								if(x+i-2>=0 && maps[NowLevel-1][(y+j-1)*(Nowlevel+1)*2+x+i-2]%2==1)
								{
									PicWriting_Overlay(0,wall_3,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
									PicWriting_Overlay(1,wall_3,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								}
								if(x+i<=(NowLevel*2+1) && maps[NowLevel-1][(y+j-1)*(Nowlevel+1)*2+x+i]%2==1)
								{
									PicWriting_Overlay(0,wall_4,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
									PicWriting_Overlay(1,wall_4,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								}
								if(y+j-2>=0 && maps[NowLevel-1][(y+j-2)*(Nowlevel+1)*2+x+i-1]%2==1)
								{
									PicWriting_Overlay(0,wall_1,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
									PicWriting_Overlay(1,wall_1,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								}
								if(y+j<=(NowLevel*2+1) && maps[NowLevel-1][(y+j)*(Nowlevel+1)*2+x+i-1]%2==1)
								{
									PicWriting_Overlay(0,wall_2,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
									PicWriting_Overlay(1,wall_2,4,4,Ex_x(x+i-1),Ex_y(y+j-1));
								}
							}
						}
					}
				}
				if(FrameNum/10!=CoverMark)
				{
					CoverMark=FrameNum/10;
				}
				if(x==NowLevel*2+1 && y==0)
				{
					if(NowLevel==5)
					{
						page=0;
					}
					else
					{
						Refresh(0);
						PicClean(1,128,64,0,0);
						rx=Ex_x(x);ry=Ex_y(y);
						CoverMark=(FrameNum-1)%20;
						for(i=1;i<=2;i++)
						{
							while(CoverMark!=(FrameNum+11)%20);
							PicClean(0,4,4,rx,ry);
							Refresh(0);
							while(CoverMark!=(FrameNum+1)%20);
							PicWriting_Cover(0,mes[dic],4,4,rx,ry);
							Refresh(0);
						}
						while(CoverMark!=(FrameNum+11)%20);
						for(;rx>=64-4*(Nowlevel+2);rx--,ry++)
						{
							PicWriting_Cover(1,mes[dic],4,4,rx,ry);
							Refresh(1);
							PicClean(1,4,4,rx,ry);
						}
						Nowlevel++;
					}
					PageMark=1;
				}
				else Refresh(CoverMark);
				RefMark=0;
				break;
		}
	}
}