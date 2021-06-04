#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header

uint32_t count1, count2, count3;

void Thread1(void const *argument);
void Thread2(void const *argument);
void Thread3(void const *argument);

osThreadDef(Thread1,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);										  		//Stack size
						
osThreadDef(Thread2,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);										  		//Stack size

osThreadDef(Thread3,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);											  	//Stack size

int main(void){
	
	osThreadCreate(osThread(Thread1),NULL);
	osThreadCreate(osThread(Thread2),NULL);
	osThreadCreate(osThread(Thread3),NULL);

	
 return 0;	
}


void Thread1(void const *argument){
	while(1){
	count1++;
	}
}

void Thread2(void const *argument){
	while(1){
	count2++;	
	}
}

void Thread3(void const *argument){
	while(1){
	count3++;
	}
}

