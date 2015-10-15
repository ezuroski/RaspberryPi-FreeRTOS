#include <FreeRTOS.h>
#include <task.h>

#include "Drivers/interrupts.h"
#include "Drivers/gpio.h"
#include "Drivers/serial.h"
#include "Drivers/tm1638.h"

#define msec *(configTICK_RATE_HZ/1000)
#define sec *(configTICK_RATE_HZ)

void task1(void *pParam)
{
	tm1638_init();
	tm1638_displaystring("testing!", 0);
	int i = 0;
	while(1)
	{
		i++;
		SetGpio(47, 1);
		vTaskDelay(1000 msec);
		SetGpio(19,i&1);SetGpio(20,i&1);SetGpio(21,i&1);
	}
}

void task2(void *pParam)
{
	serial_printtext("hello\r\n");
	int i = 0;
	while(1)
	{
		i++;
		vTaskDelay(500 msec);
		SetGpio(47, 0);
		vTaskDelay(500 msec);
	}
}


/**
 *	This is the systems main entry, some call it a boot thread.
 *
 *	-- Absolutely nothing wrong with this being called main(), just it doesn't have
 *	-- the same prototype as you'd see in a linux program.
 **/
void main(void)
{
	SetGpioFunction(47, 1);			// RDY led

	delay_us(1000000);
	serial_printtext("one\r\n");
	delay_us(1000000);
	serial_printtext("two\r\n");
	delay_us(1000000);
	serial_printtext("three\r\n");
	delay_us(1000000);
	serial_printtext("four\r\n");
	delay_us(1000000);
	serial_printtext("five\r\n");

	DisableInterrupts();
	InitInterruptController();

	xTaskCreate(task1, "LED_0", 128, NULL, 0, NULL);
	xTaskCreate(task2, "LED_1", 128, NULL, 0, NULL);

	vTaskStartScheduler();

	/*
	 *	We should never get here, but just in case something goes wrong,
	 *	we'll place the CPU into a safe loop.
	 */
	while(1) {
		;
	}
}
