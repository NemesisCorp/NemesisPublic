/*
===============================================================================
 Name        : main.c
 Author      : Evan Pederson
 Version     : 1.00.00
 Copyright   : Copyright (C) 
 Description : Test Development Board's LED0 through LED7 on Port 1 and
 	 	 	   TACT Switches PO.2 through PO.5
===============================================================================
*/
#include "LPC17xx.h"

/**
void EINT_IRQHandler(void)
{
	LPC_GPIOINT -> IO0IntClr |= (1<<2);
}
**/

//Globally define LEDs
#define LED0 (1<<19)	//0x80000
#define LED1 (1<<20)
#define LED2 (1<<21)
#define LED3 (1<<22)
#define LED4 (1<<23)
#define LED5 (1<<24)
#define LED6 (1<<25)
#define LED7 (1<<26)

//Globally define TACT Switches
#define P02 (!(((LPC_GPIO0 -> FIOPIN)&(1<<2)) == (1<<2)))
#define P03 (!(((LPC_GPIO0 -> FIOPIN)&(1<<3)) == (1<<3)))
#define P04 (!(((LPC_GPIO0 -> FIOPIN)&(1<<4)) == (1<<4)))
#define P05 (!(((LPC_GPIO0 -> FIOPIN)&(1<<5)) == (1<<5)))

//Globally define data buffers
unsigned int sequence1[] = {LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED6, LED5, LED4, LED3, LED2, LED1, LED0};
unsigned int sequence2[] = {LED1, LED3, LED5, LED7, LED5, LED3, LED1};
unsigned int sequence3[] = {LED0, LED2, LED4, LED6, LED4, LED2, LED0};

void Setup_LED();

int main(void)
{
//	LPC_GPIOINT -> IO0IntEnF |= (1<<2);
//	NVIC_EnableIRQ(EINT3_IRQn);

	volatile unsigned long i = 0;
	volatile unsigned long j_one = 0;
	volatile unsigned long j_two = 0;
	volatile unsigned long j_three = 0;
	unsigned int button = 1;

	Setup_LED();

	while(1)
	{
		if(button == 1)
		{
			LPC_GPIO1 -> FIOPIN = ~sequence1[j_one];
			j_one++;
			if(j_one == 15)
				j_one = 0;
			for(i = 0; i < 900000; i++);
			//LPC_GPIOINT -> IO0IntClr |= (1<<2);
		}

		if(button == 2)
		{
			LPC_GPIO1 -> FIOPIN = ~sequence2[j_two];
			j_two++;
			if(j_two == 7)
				j_two = 0;
			for(i = 0; i < 900000; i++);
		}

		if(button == 3)
		{
			LPC_GPIO1 -> FIOPIN = ~sequence3[j_three];
			j_three++;
			if(j_three == 7)
				j_three = 0;
			for(i = 0; i < 900000; i++);
		}

		if(button == 4)
		{
			LPC_GPIO1 -> FIOPIN = sequence1[j_one];
			j_one++;
			if(j_one == 15)
				j_one = 0;
			for(i = 0; i < 900000; i++);
		}

		if(P02)
			button = 1;

		if(P03)
			button = 2;

		if(P04)
			button = 3;

		if(P05)
			button = 4;
	}

	return 1;
}

void Setup_LED()
{
	LPC_GPIO1 -> FIODIR |= LED0;
	LPC_GPIO1 -> FIOPIN &= LED0;

	LPC_GPIO1 -> FIODIR |= LED1;
	LPC_GPIO1 -> FIOPIN &= LED1;

	LPC_GPIO1 -> FIODIR |= LED2;
	LPC_GPIO1 -> FIOPIN &= LED2;

	LPC_GPIO1 -> FIODIR |= LED3;
	LPC_GPIO1 -> FIOPIN &= LED3;

	LPC_GPIO1 -> FIODIR |= LED4;
	LPC_GPIO1 -> FIOPIN &= LED4;

	LPC_GPIO1 -> FIODIR |= LED5;
	LPC_GPIO1 -> FIOPIN &= LED5;

	LPC_GPIO1 -> FIODIR |= LED6;
	LPC_GPIO1 -> FIOPIN &= LED6;

	LPC_GPIO1 -> FIODIR |= LED7;
	LPC_GPIO1 -> FIOPIN &= LED7;
}

