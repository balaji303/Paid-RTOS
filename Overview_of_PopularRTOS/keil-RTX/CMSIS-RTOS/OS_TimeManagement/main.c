#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header
#include "led.h"

uint32_t count1, count2;

void RedThread(void const *argument);
void GreenThread(void const *argument);
//void Thread3(void const *argument);

osThreadDef(RedThread,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);										  		//Stack size
						
osThreadDef(GreenThread,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);										  		//Stack size

/*osThreadDef(Thread3,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);											  	//Stack size*/

int main(void){
	
	osThreadCreate(osThread(RedThread),NULL);
	osThreadCreate(osThread(GreenThread),NULL);
//	osThreadCreate(osThread(Thread3),NULL);

	
 return 0;	
}


void RedThread(void const *argument){
	while(1){
	RedToggle();
	}
}

void GreenThread(void const *argument){
	while(1){
	GreenToggle();
	}
}

/*void Thread3(void const *argument){
	while(1){
	count3++;
	}
}*/

