/*
===============================================================================
 Name        : main.c
 Author      : Evan Pederson
 Version     :
 Copyright   : Copyright (C)
 Description : Lab3
===============================================================================
*/

#include "LPC17xx.h"
#include "lcd.h"
#include "stdio.h"

//Globally define Buttons
#define P02 (!(((LPC_GPIO0 -> FIOPIN)&(1<<2)) == (1<<2)))
#define P03 (!(((LPC_GPIO0 -> FIOPIN)&(1<<3)) == (1<<3)))

//Globally define LCD Messages
const unsigned char MSG0[10] = "STOP CLOCK";
const unsigned char DIVIDER[25] = "-------------------------";

//Globally define i for wait statements
volatile unsigned long i = 0;
volatile unsigned int millisecond = 0;
volatile unsigned int second = 0;
volatile unsigned int minute = 0;
volatile unsigned int hour = 0;


void RIT_IRQHandler(void)	//Timer
{
	millisecond++;

	if(millisecond == 1000)
	{
		second++;
		millisecond = 0;
	}

	if(second == 60)
	{
		minute++;
		second = 0;
	}

	if(minute == 60)
	{
		hour++;
		minute = 0;
	}

	if(hour == 24)
		hour = 0;

	LPC_RIT -> RICTRL |= (1<<0);
}

void TIMER0_IRQHandler(void) //software interrupt
{
	while(1)
	{
		for(i = 0; i < 900000; i++);
	}
	//DO NOT NEED TO CLEAR BIT FOR SOFTWARE INTERRUPT
}

void EINT3_IRQHandler(void) //hardware interrupt
{
	LPC_RIT -> RICTRL ^= (1<<3);
	for(i = 0; i < 900000; i++);
	LPC_GPIOINT -> IO0IntClr |= (1<<3);
}

int main(void)
{
	lcd_init();
	fillScreen(0xFFFF); //fillscreen with white color
	setBackgroundColor16(0xFFFF); //set background with white color

	setColor16(ST7735_16_GREEN);
	drawString(10,10,DIVIDER);

	setColor16(ST7735_16_ORANGE);
	drawString(50,20,MSG0);	//x,y,char *string

	setColor16(ST7735_16_GREEN);
	drawString(10,30,DIVIDER);

	LPC_SC -> PCONP |= (1<<16);
	LPC_RIT -> RICTRL |= (0x3);		//setup auto RST & INT CLR
	LPC_RIT -> RICOMPVAL = 25000;	//Interrupt every 1ms

	unsigned char array[25];

	unsigned int button = 1;

	NVIC_SetPriority(RIT_IRQn, 0);
	NVIC_SetPriority(EINT3_IRQn, 5);
	NVIC_SetPriority(TIMER0_IRQn, 7);
	LPC_GPIO0 -> FIOCLR3 |= (1<<3);
	LPC_GPIOINT -> IO0IntEnF |= (1<<3); //Trigger interrupt on falling edge for P03

	NVIC_EnableIRQ(EINT3_IRQn);		//Enable EINT3 interrupt
	NVIC_EnableIRQ(TIMER0_IRQn);	//Enable Timer0 interrupt
	NVIC_EnableIRQ(RIT_IRQn);		//Enable RIT interrupt

	while(1)
	{
		setColor16(ST7735_16_RED);
		sprintf(array, "HR:MIN:SEC:MS");
		drawString(10,50,array);
		sprintf(array, "%u:%u:%u:%u", hour, minute, second, millisecond);
		drawString(10,60,array);

		setColor16(ST7735_16_BLACK);
		sprintf(array, "P0.2 = Reset");
		drawString(10,80,array);
		sprintf(array, "P0.3 = Start/Stop");
		drawString(10,90,array);

		setColor16(ST7735_16_BLUE);
		sprintf(array, "Nate is not BO$$ :(");
		drawString(10,110,array);

		if(button == 2)
		{
			millisecond = 0;
			second = 0;
			minute = 0;
			hour = 0;
			button = 1;
		}

		if(P02)
		{
			button = 2;

		}
	}
	return 1;
}
