#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "stm32f4xx.h"                  // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

//#define configUSE_TIMERS 1
#define GREEN GPIO_PIN_5
#define RED   GPIO_PIN_6

void GPIO_Init(void);

void GreenTask(void *pvParameters);
void RedTask(void *pvParameters);

int main(void){
	GPIO_Init();
	
	xTaskCreate(
							GreenTask,//Task function
							"Green LED Toggle",//Human readable
							100, //Stacksize
							NULL,//Parameter for the Task
							1,   //Priority
							NULL //Task Handler
	);
	
	xTaskCreate(
							RedTask,//Task function
							"Red LED Toggle",//Human readable
							100, //Stacksize
							NULL,//Parameter for the Task
							1,   //Priority
							NULL //Task Handler
	);
	
	vTaskStartScheduler();
	while(1){
		//Do Nothing
	}
	//return 0;
}

void GPIO_Init(void){
/*	GPIO_InitTypeDef GPIO_InitStut;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	HAL_GPIO_WritePin(GPIOA,GREEN | RED, GPIO_PIN_RESET);
	
	GPIO_InitStut.Pin = GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStut.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStut.Pull = GPIO_NOPULL;
	GPIO_InitStut.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(GPIOA,&GPIO_InitStut);
*/
	RCC->AHB1ENR |=0x1; //Enable GPIOA
	GPIOA->MODER |=0x1400; //Enable PA5,PA6
}

void GreenTask(void *pvParameters){
	//int i;
	while(1){
		//Onboard LED is connected to PA5/D13
		GPIOA->ODR |= 0x20;
		//HAL_GPIO_TogglePin(GPIOA,GREEN);
		//for(i=0;i<700000;i++);
		vTaskDelay(250 / portTICK_PERIOD_MS);
	}
}


void RedTask(void *pvParameters){
	//int i;
	while(1){
		//External LED is connected to PA6/D12
	  GPIOA->ODR |= 0x40;
		//HAL_GPIO_TogglePin(GPIOA,RED);
		//for(i=0;i<700000;i++);
		vTaskDelay(250 / portTICK_PERIOD_MS);
	}	
}

