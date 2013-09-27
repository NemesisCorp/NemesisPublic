/*
===============================================================================
 Name        : main.c
 Author      : Evan Pederson
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#include "LPC17xx.h"
#include "stdio.h"
#include "I2C_SOFTWARE.h"
#include "lcd.h"
#include "BUTTONS.h"

//Globally define LCD Messages
const unsigned char DIVIDER[25] = "-------------------------";
const unsigned char MSG0[17] = "Lab 5 I2C Banging";
const unsigned char MSG1[19] = "P1.19:SDA P1.24:SCL";
const unsigned char MSG2[16] = "24LC00 EEPROM IC";
const unsigned char MSG3[18] = "Reg:0x00 Addr:0xA0";
const unsigned char MSG4[9]  = "DATA:0xAA";
const unsigned char MSG5[15] = "SLAVE READ 0xFF";
const unsigned char MSG6[14] = "P0.2 Send Data";
const unsigned char MSG7[14] = "P0.3 Read Data";

void Address(void)
{
	SDA_HIGH;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;

	SDA_HIGH;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;

	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
}

void Register(void)
{
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
	SDA_LOW;
	SCL_CLK;
}

void DataA(void)
{
	SDA_HIGH;	//1
	SCL_CLK
	SDA_LOW;	//0
	SCL_CLK;
	SDA_HIGH;	//1
	SCL_CLK;
	SDA_LOW;	//0
	SCL_CLK;

	SDA_HIGH;	//1
	SCL_CLK;
	SDA_LOW;	//0
	SCL_CLK;
	SDA_HIGH;	//1
	SCL_CLK;
	SDA_LOW;	//0
	SCL_CLK;
}

void DataF(void)
{
	SDA_HIGH;	//1
	SCL_CLK
	SDA_HIGH;	//1
	SCL_CLK;
	SDA_HIGH;	//1
	SCL_CLK;
	SDA_HIGH;	//1
	SCL_CLK;

	SDA_HIGH;	//1
	SCL_CLK;
	SDA_HIGH;	//1
	SCL_CLK;
	SDA_HIGH;	//1
	SCL_CLK;
	SDA_HIGH;	//1
	SCL_CLK;
}

void Start(void)
{
	SDA_HIGH;
	delay;
	SCL_HIGH;
	delay;
	SDA_LOW;
	delay;
	SCL_LOW;
	delay;
}

void Stop(void)
{
	SDA_LOW;
	delay;
	SCL_HIGH;
	delay;
	SDA_HIGH;
	delay;
}

void ACK(void)
{
	SDA_HIGH;
	SDA_IN;
	SCL_LOW;
	delay;
	SCL_HIGH;
	delay;
	delay;
	if((LPC_GPIO1 -> FIOPIN)&I2C_SDA)
	{
		SDA_HIGH;	//ack failed
	}
	SCL_LOW;
	//delay;
	//delay;
	SDA_OUT;
	SDA_LOW;
}

void OpenDrain(void)
{
	LPC_GPIO1 -> FIODIR |= (1<<19);
	LPC_GPIO1 -> FIODIR |= (1<<24);
	LPC_PINCON -> PINMODE_OD1 |= (1<<19);
	LPC_PINCON -> PINMODE_OD1 |= (1<<24);
}

void Init_I2C(void)
{
	SDA_HIGH;
	SCL_HIGH;
}

int main(void)
{
	lcd_init();
	fillScreen(0xFFFF); 				//fillscreen with white color
	setBackgroundColor16(0xFFFF); 		//set background with white color

	setColor16(ST7735_16_BLACK);		//Set Text Color

	drawString(10,10,(char*)DIVIDER);
	drawString(10,20,(char*)MSG0);
	drawString(10,30,(char*)MSG1);
	drawString(10,40,(char*)MSG2);
	drawString(10,50,(char*)DIVIDER);

	setColor16(ST7735_16_RED);

	drawString(10,60,(char*)MSG3);
	drawString(10,70,(char*)MSG4);
	drawString(10,80,(char*)MSG5);
	drawString(10,100,(char*)MSG6);
	drawString(10,110,(char*)MSG7);

	OpenDrain();

	Init_I2C();					//idle SCL and SDA lines high

	while(1)
	{
		if(P02)								//write data
		{
			Start();
			Address();
			ACK();
			Register();
			ACK();
			DataF();
			ACK();
			Stop();
		}

		if(P03)								//read data
		{
			Start();
			Address();
			ACK();
			Register();
			ACK();
			Stop();
			Start();
			Address();
			ACK();
			DataF();
			ACK();
			Stop();
		}
	}
	return 1;
}
