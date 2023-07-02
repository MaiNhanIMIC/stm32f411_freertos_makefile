#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

#define GPIOD_BASE_ADDRESS 0x40020C00
#define GPIOA_BASE_ADDRESS 0x40020000

void led_init()
{
	uint32_t* AHB1ENR = (uint32_t*)(0x40023830);
    *AHB1ENR |= (1<<3);
	uint32_t* GPIOD_MODER  = (uint32_t*)(GPIOD_BASE_ADDRESS + 0x00);
	uint32_t* GPIOD_OTYPER = (uint32_t*)(GPIOD_BASE_ADDRESS + 0x04);
	*GPIOD_MODER &= ~(0xff << 24);
	*GPIOD_MODER |= (0b01 << 24) | (0b01 << 26) | (0b01 << 28) | (0b01 << 30);
	*GPIOD_OTYPER &= ~(0xf << 12);
}
typedef enum
{
	LED_1 = 12, LED_2, LED_3, LED_4
}led_num_t;
typedef enum
{
	LED_OFF, LED_ON
} led_state_t;
void led_ctrl(led_num_t led_num, led_state_t state)
{
	uint32_t* GPIOD_ODR  = (uint32_t*)(GPIOD_BASE_ADDRESS + 0x14);
	if(state == LED_ON)
		*GPIOD_ODR |= (1<<led_num);
	else
		*GPIOD_ODR &= ~(1<<led_num);
}
void SystemInit()
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif
	// system_tick_init();	
}
void vApplicationMallocFailedHook()
{
	// led_ctrl(LED_3, LED_ON);
}
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                        StackType_t ** ppxIdleTaskStackBuffer,
                                        uint32_t * pulIdleTaskStackSize )
{
	
}
void vApplicationTickHook()
{

}
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                        char * pcTaskName )
{

}
void vApplicationIdleHook()
{

}
void vApplicationGetTimerTaskMemory()
{

}

void func1()
{
	while(1)
	{
		led_ctrl(LED_1, LED_ON);
		vTaskDelay(1500);
		led_ctrl(LED_1, LED_OFF);
		vTaskDelay(1500);
	}
}

void func2()
{
	while(1)
	{
		led_ctrl(LED_2, LED_ON);
		vTaskDelay(configTICK_RATE_HZ);
		led_ctrl(LED_2, LED_OFF);
		vTaskDelay(configTICK_RATE_HZ);
	}
}
void func3()
{
	while(1)
	{
		led_ctrl(LED_3, LED_ON);
		vTaskDelay(1200);
		led_ctrl(LED_3, LED_OFF);
		vTaskDelay(1200);
	}
}

void func4()
{
	while(1)
	{
		led_ctrl(LED_4, LED_ON);
		vTaskDelay(1700);
		led_ctrl(LED_4, LED_OFF);
		vTaskDelay(1700);
	}
}

TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;
TaskHandle_t task4;
void main()
{
	led_init();
    xTaskCreate( func1, "task 1", configMINIMAL_STACK_SIZE, NULL, 1,  &task1);
	xTaskCreate( func2, "task 2", configMINIMAL_STACK_SIZE, NULL, 2, &task2);
	xTaskCreate( func3, "task 3", configMINIMAL_STACK_SIZE, NULL, 3, &task3);
	xTaskCreate( func4, "task 4", configMINIMAL_STACK_SIZE, NULL, 4, &task4);
	vTaskStartScheduler();
    while(1)
    {
        
 
    }
}
