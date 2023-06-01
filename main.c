#include <STC15F2K60S2.H>
#include "onewire.h"
unsigned char shumaguanduanma[17] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};//16 mie
unsigned char shumaguan[8] = {16,16,16,16, 16,16,16,16};
unsigned int temp_dat = 0,temp_H;
int n = 0;
unsigned int display_time = 0;

void else_init()
{
	P0 = 0x00; P2&=0x1f; P2|=0xa0; P0 = 0x00; P2&=0x1f; P0 = 0x00;	
	P0 = 0XFF; P2&=0x1f; P2|=0x80; P0 = 0xff; P2&=0x1f; P0 = 0XFF;	
}

void Timer0Init(void)		//1??@12.000MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0x20;		//??????
	TH0 = 0xD1;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
	ET0 = 1;
	EA = 1;
}


void ds18b20()
{
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);
	Delay_OneWire(200);
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);
	temp_dat = Read_DS18B20();
	temp_H = Read_DS18B20();
	temp_dat = ((temp_H<<8)|temp_dat);
	temp_dat = temp_dat*6.25;//TURN 100 UP
}

void display()
{
	P0 = 0XFF; P2&=0x1f; P2|=0XE0; if(n==2)P0 = ~(shumaguanduanma[shumaguan[n]]|0x80);else P0 = ~shumaguanduanma[shumaguan[n]];  P2&=0x1f; P0 = 0XFF;	//DUAN
	P0 = 0XFF; P2&=0x1f; P2|=0XC0; P0 = 0x01<<n; P2&=0x1f; P0 = 0XFF; //WEI
	n++;
	if(n>7)n=0;
}

void main()
{
	else_init();
	Timer0Init();	
	while(1)
	{
		ds18b20();
		shumaguan[1] = temp_dat%10000/1000;
		shumaguan[2] = temp_dat%1000/100;
		shumaguan[3] = temp_dat%100/10;
		shumaguan[4] = temp_dat%10;
	}
}

void timer0() interrupt 1
{
	display_time++;
	if(display_time>=2)
	{
		display();
		display_time = 0;
	}
}


