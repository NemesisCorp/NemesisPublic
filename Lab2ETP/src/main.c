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

//Globally define LEDs
#define LED0 (1<<19)	//0x80000
#define LED1 (1<<20)
#define LED2 (1<<21)	//#define LED0_2 3670016 //111<<19

//Globally define Buttons
#define P02 (!(((LPC_GPIO0 -> FIOPIN)&(1<<2)) == (1<<2)))
#define P03 (!(((LPC_GPIO0 -> FIOPIN)&(1<<3)) == (1<<3)))

//Globally define i for wait statements
volatile unsigned long i = 0;

void TIMER0_IRQHandler(void) //software interrupt
{
	while(1)
	{
		LPC_GPIO1 -> FIOPIN ^= LED1;	//toggle LED1 using XOR
		for(i = 0; i < 900000; i++);
	}
	//DO NOT NEED TO CLEAR BIT FOR SOFTWARE INTERRUPT
}

void EINT3_IRQHandler(void) //hardware interrupt
{
	while(1)
	{
		LPC_GPIO1 -> FIOPIN ^= LED2;
		for(i = 0; i < 900000; i++);
	}
	//WOULD CLEAR BIT UNDER NORMAL CIRCUMSTANCES HOWEVER ASSIGNEMENT DOES NOT REQUIRE TO EXIT WHILE LOOP
}

int main(void)
{
	unsigned int button = 1;

	LPC_GPIO1 -> FIODIR |= LED0 + LED1 + LED2; 	//LPC_GPIO1 -> FIODIR |= LED0_2;
	LPC_GPIO1 -> FIOPIN &= LED0 + LED1 + LED2;	//LPC_GPIO1 -> FIOPIN &= LED0_2;

	NVIC_SetPriority(EINT3_IRQn, 0);
	NVIC_SetPriority(TIMER0_IRQn, 7);
	
	LPC_GPIOINT -> IO0IntEnF |= (1<<3); //Trigger interrupt on falling edge for P03

	NVIC_EnableIRQ(EINT3_IRQn);		//Enable EINT3 interrupt
	NVIC_EnableIRQ(TIMER0_IRQn);	//Enable Timer0 interrupt

	while(1)
	{
		if(button == 1)
		{
			LPC_GPIO1 -> FIOPIN ^= LED0;
			for(i = 0; i < 900000; i++);
		}

		if(button == 2)
		{
			TIMER0_IRQHandler();
		}

		if(P02)
			button = 2;
	}
	return 1;
}
