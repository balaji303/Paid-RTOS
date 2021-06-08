#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "led.h"

uint32_t count1, count2;

void RedThread(void const *argument);
void GreenThread(void const *argument);


osThreadDef(RedThread,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);										  		//Stack size
						
osThreadDef(GreenThread,										// Name of the thread
						osPriorityNormal,           // Priority Level
						1,													//No. of Instance
						0);										  		//Stack size

int main(void){
	LedInit();
	osThreadCreate(osThread(RedThread),NULL);
	osThreadCreate(osThread(GreenThread),NULL);
	
 return 0;	
}


void RedThread(void const *argument){
	while(1){
	RedToggle();
	osDelay(500);
	}
}

void GreenThread(void const *argument){
	while(1){
	GreenToggle();
	osDelay(500);
	}
}

