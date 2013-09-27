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
#include "lcd.h"
#include "stdio.h"
#include "BUTTONS.h"

#define LED0 (1<<19)	//0x80000

//Globally define LCD Messages
const unsigned char DIVIDER[25] = "-------------------------";
const unsigned char MSG0[10] = "Lab 4 UART";
const unsigned char MSG1[16] = "SW0 = Clear Data";

volatile int RX = 0; //serial message being received
volatile int TEMP = 0;
volatile unsigned int flag = 1;
volatile unsigned char i = 0;

void Enable_Hardware(void)
{
	LPC_GPIOINT -> IO2IntEnF |= (1<<1); //detect falling edge and trigger interrupt on P2.1
}

void DisEnable_Hardware(void)
{
	LPC_GPIOINT -> IO2IntEnF &= ~(1<<1); //do not detect falling edge and trigger interrupt on P2.1
	LPC_GPIOINT -> IO2IntClr |= 0xFF; //clear hardware flags (all of them)
}

void Enable_RIT(void)
{
	LPC_RIT -> RICTRL |= (1<<3); //enable RIT interrupt
}

void DisEnable_RIT(void)
{
	LPC_RIT -> RICTRL &= ~(1<<3); //disable RIT interrupt
}

void EINT3_IRQHandler(void) //external hardware interrupt
{
	DisEnable_Hardware();

	Enable_RIT();
}

void RIT_IRQHandler(void)
{
	DisEnable_Hardware();
	LPC_GPIO1 -> FIOPIN ^= LED0; //toggle LED0

	if((flag == 3) || (flag == 5) || (flag == 7) || (flag == 9) || (flag == 11) || (flag == 13) || (flag == 15) || (flag == 17))
	{
		if((!(((LPC_GPIO2 -> FIOPIN)&(1<<1)) == (1<<1))))
		{
			TEMP += 0x80;
			//TEMP = (TEMP>>1);
		}
		TEMP = (TEMP>>1);
	}

	else if(flag != 18)
	{
		TEMP = (TEMP>>1);
	}

	else if(flag == 18)
	{
		i = 1;
		flag = 0;

		Enable_Hardware();
		DisEnable_RIT();
	}

	flag += 1;
	LPC_RIT -> RICTRL |= (1<<0);	//Clear RIT flag
}

int main(void)
{
	//LPC_GPIO2 -> FIOSET |= (1<<0); //Set pin high

	LPC_GPIO1 -> FIODIR |= LED0;
	LPC_GPIO1 -> FIOPIN &= LED0;

	//LPC_GPIO2 -> FIODIR |= (1<<1);
	//LPC_GPIO2 -> FIOPIN &= (1<<1);

	//LPC_GPIO2 -> FIODIR &= ~(0<<0);
	//LPC_GPIO2 -> FIOPIN &= (1<<0);

	lcd_init();
	fillScreen(0x001F); //fillscreen with blue color
	setBackgroundColor16(0x001F); //set background with blue color

	setColor16(ST7735_16_BLACK);
	drawString(10,10,(char*)DIVIDER);

	drawString(10,20,(char*)MSG0);
	drawString(10,30,(char*)MSG1);
	drawString(10,40,(char*)DIVIDER);

	LPC_SC -> PCONP |= (1<<16);
	LPC_RIT -> RICTRL |= (0x3);		//setup auto RST & INT CLR
	LPC_RIT -> RICOMPVAL = 1303;	//Interrupt every 52.083us

	NVIC_EnableIRQ(EINT3_IRQn);		//Enable EINT3 interrupt
	NVIC_EnableIRQ(RIT_IRQn);		//Enable RIT interrupt

	DisEnable_RIT(); //disable RIT interrupt

	LPC_GPIOINT -> IO2IntEnF |= (1<<1); //detect falling edge and trigger interrupt on P2.1
	setColor16(ST7735_16_WHITE);

	while(1)
	{
		if(i == 1)
		{
			RX = TEMP;
			TEMP = 0;
			i = 0;
		}
		drawChar(10,50,RX);
	}
	return 1;
}
