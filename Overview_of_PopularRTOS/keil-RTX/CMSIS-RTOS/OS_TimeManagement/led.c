#include "led.h"

void LedInit(void){
	RCC->AHB1ENR |=0x1; //Enable GPIOA
	GPIOA->MODER |=0x1400; //Enable PA5,PA6
	
}

void RedToggle(void){
	//External LED is connected to PA6/D12
	GPIOA->ODR ^= 0x40;
}

void GreenToggle(void){
	//Onboard LED is connected to PA5/D13
	GPIOA->ODR ^= 0x20;	
}
