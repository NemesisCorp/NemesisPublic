#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lcd.h"
#include "stdio.h"

static void LED_Task(void *pvParameters);
static void BUTTON_Task(void *pvParameters); 					// prototype for button task
static void LCD_Task(void *pvParameters);
static void TIME_Task(void *pvParameters);

#define LED_TASK_PRIORITY (tskIDLE_PRIORITY + 1) 				// assign priority to led task
#define BUTTON_TASK_PRIORITY (tskIDLE_PRIORITY + 1) 			// assign priority to button task
#define TIME_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define LCD_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

#define LED0 (1<<19)	//0x80000
#define LED1 (1<<20)
#define LED2 (1<<21)
#define LED3 (1<<22)
#define LED4 (1<<23)
#define LED5 (1<<24)
#define LED6 (1<<25)
#define LED7 (1<<26)

unsigned int sequence1[] = {LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED6, LED5, LED4, LED3, LED2, LED1, LED0};

#define mainQUEUE_LENGTH 4

static xQueueHandle xQueueButton = NULL;
static xQueueHandle xQueueTime = NULL;
static xQueueHandle xQueueRe = NULL;
static xTaskHandle TIME_Task_Handle = NULL;
static xTaskHandle LCD_Task_Handle = NULL;

const unsigned char MSG0[10] = "STOP CLOCK";
const unsigned char DIVIDER[25] = "-------------------------";
const unsigned char MSG1[7] = "LED ON:";
const unsigned char TIME[13] = "HR:MIN:SEC:MS";
const unsigned char MSG2[25] = "P0.2 = Start";
const unsigned char MSG3[25] = "P0.3 = Stop";
const unsigned char MSG4[25] = "P0.4 = Reset";

int main(void)
{
	lcd_init();
	fillScreen(0xFFFF); 									//fillscreen with white color
	setBackgroundColor16(0xFFFF); 							//set background with white color

	setColor16(ST7735_16_GREEN);
	drawString(10,10,(char*)DIVIDER);

	setColor16(ST7735_16_ORANGE);
	drawString(50,20,(char*)MSG0);							//x,y,char *string

	setColor16(ST7735_16_GREEN);
	drawString(10,30,(char*)DIVIDER);

	setColor16(ST7735_16_RED);
	drawString(10,50, (char*)MSG1);
	drawString(10,70, (char*)TIME);
	drawString(10,90, (char*)MSG2);
	drawString(10,100, (char*)MSG3);
	drawString(10,110, (char*)MSG4);

	xQueueButton = xQueueCreate(1, sizeof(uint8_t));
	xQueueRe = xQueueCreate(1, sizeof(uint8_t));
	xQueueTime = xQueueCreate(mainQUEUE_LENGTH, sizeof(unsigned int));
	xTaskCreate(LED_Task, (signed char *) "LED", configMINIMAL_STACK_SIZE, NULL, TIME_TASK_PRIORITY, NULL);
	xTaskCreate(BUTTON_Task, (signed char *) "BUTTON", configMINIMAL_STACK_SIZE, NULL, TIME_TASK_PRIORITY, NULL);
	xTaskCreate(TIME_Task, (signed char *) "TIME", configMINIMAL_STACK_SIZE, NULL, TIME_TASK_PRIORITY, &TIME_Task_Handle);
	xTaskCreate(LCD_Task, (signed char *) "LCD", configMINIMAL_STACK_SIZE, NULL, LCD_TASK_PRIORITY, NULL);
	vTaskStartScheduler(); 									// Starts task system
	while(1); // Should never reach this point, unless there is not enough FreeRTOS heap memory available for idle task to be created
}

static void BUTTON_Task(void *pvParameters)						//Start/Stop/Reset
{
	uint8_t start = 1;											//random data
	uint8_t stop = 2;
	uint8_t reset = 3;
	uint8_t led = 4;
	uint8_t data = 0;
	portTickType xNextWakeTime; 								//necessary for vtaskdelayuntil
	xNextWakeTime = xTaskGetTickCount(); 						//necessary for vtaskdelayuntil

	while(1)
	{
		if(!(((LPC_GPIO0 -> FIOPIN)&(1<<2))>>2)) 				// IF button 1 pressed
		{
			data = start;
			xQueueSend(xQueueButton, &data, 0); 				// Send Data to LCD task
			vTaskDelay(250); 									// Debounce delay ~250ms
		}

		if(!(((LPC_GPIO0 -> FIOPIN)&(1<<3))>>3)) 				// IF button 2 pressed
		{
			data = stop;
			xQueueSend(xQueueButton, &data, 0); 				// Send Data to LCD task
			vTaskDelay(250); 									// Debounce delay ~250ms
		}

		if(!(((LPC_GPIO0 -> FIOPIN)&(1<<4))>>4)) 				// IF button 3 pressed
		{
			data = reset;
			xQueueSend(xQueueButton, &data, 0); 				// Send Data to LCD task
			vTaskDelay(250); 									// Debounce delay ~250ms
		}

		if(!(((LPC_GPIO0 -> FIOPIN)&(1<<5))>>5)) 				// IF button 4 pressed
		{
			data = led;
			xQueueSend(xQueueButton, &data, 0); 				// Send Data to LCD task
			vTaskDelay(250); 									// Debounce delay ~250ms
		}
		vTaskDelayUntil(&xNextWakeTime, 10); 					// Delay for 10ms
	}
}

static void LED_Task(void *pvParameters)
{
	unsigned int j_one = 0;
	uint8_t data = 0;
	Setup_LED();
	uint8_t LED_Sequence_ON = 1;

	while(1)
	{
		if(xQueueReceive(xQueueButton, &data, 0)) 				// If new data in queue, do something
		{
			LED_Sequence_ON = !LED_Sequence_ON; 			// Toggle Sequence on/off
		}
		if(LED_Sequence_ON)
		{
			LPC_GPIO1 -> FIOPIN = ~sequence1[j_one];
			j_one++;
			if(j_one == 15)
			j_one = 0;
		}
		else
		{
			LPC_GPIO1 -> FIOPIN = sequence1; 					// LED off;
		}
		vTaskDelay(500); 									//Delay for ~500ms
	}
}

static void TIME_Task(void *pvParameters)					//static function keeps track of time
{
	volatile unsigned int millisec = 0;
	volatile unsigned int sec = 0;
	volatile unsigned int min = 0;
	volatile unsigned int hr = 0;

	portTickType xNextWakeTime;
	xNextWakeTime = xTaskGetTickCount();
	unsigned int data = 0;
	uint8_t reset = 0;

	while(1)
	{
		vTaskDelayUntil(&xNextWakeTime, 10);
		millisec++;

		if(millisec == 100)
		{
			sec++;
			millisec = 0;
		}
		if(sec == 60)
		{
			min++;
			sec = 0;
		}
		if(min == 60)
		{
			hr++;
			min = 0;
		}
		if(hr == 24)
		{
			xQueueReset(xQueueTime);
			hr = 0;
		}

		if(xQueueReceive(xQueueRe, (uint8_t *) &reset, 0))
		{
			millisec = 0;
			sec = 0;
			min = 0;
			hr = 0;
			xQueueReset(xQueueTime);
		}

		xQueueSend(xQueueTime, (unsigned int*) &millisec, 0);
		xQueueSend(xQueueTime, (unsigned int*) &sec, 0);
		xQueueSend(xQueueTime, (unsigned int*) &min, 0);
		xQueueSend(xQueueTime, (unsigned int*) &hr, 0);
	}
}

static void LCD_Task(void *pvParameters)
{
	volatile unsigned int millisec = 0;
	volatile unsigned int sec = 0;
	volatile unsigned int min = 0;
	volatile unsigned int hr = 0;

	const unsigned char array[25];

	uint8_t data = 0;
	uint8_t reset = 5;

	while(1)
	{
		vTaskDelay(50);
		xQueueReceive(xQueueTime, (unsigned int *) &millisec, 0);
		xQueueReceive(xQueueTime, (unsigned int *) &sec, 0);
		xQueueReceive(xQueueTime, (unsigned int *) &min, 0);
		xQueueReceive(xQueueTime, (unsigned int *) &hr, 0);
		sprintf((unsigned char*) array,"%u:%u:%u:%u", (unsigned int*) hr, (unsigned int*) min, (unsigned int*) sec,(unsigned int*) millisec);
		drawString(10,80,(unsigned char*) array);

		if(xQueueReceive(xQueueButton, &data, 0))
		{
			if(data == 2)
			{
				vTaskSuspend(TIME_Task_Handle);
			}

			if(data == 1)
			{
				vTaskResume(TIME_Task_Handle);
			}

			if(data == 3)
			{
				xQueueSend(xQueueRe, (uint8_t *) &reset, 0);
			}
		}
	}
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
