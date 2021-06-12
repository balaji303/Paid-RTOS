#include "os.h"				//Micrium.micrium::RTOS:uC/OS 	Kernel
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common

OS_TCB ledControllerTaskTCB;
OS_ERR os_err;

void ledControllerTask(void *p_arg);

int main(void){
	OSInit(&os_err);
	OSTaskCreate(&ledControllerTaskTCB,
								"Led Controller Task",
								ledControllerTask,
								(void *)0,
									
	)
	
	return 0;
}

void ledControllerTask(void *p_arg){
	while(1){
		
		
		
	}
}
