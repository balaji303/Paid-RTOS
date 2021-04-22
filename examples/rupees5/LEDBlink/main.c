#include "OS_Kernel.h"

#define QUANTA 10 //This makes each thread runs for 10 milli second
#define GREEN_LED_PIN (1U<<10)
#define RED_LED_PIN (1U<<12)
#define AHB1_BUS_ENABLE (1U)
#define GREEN_HIGH (1U<<5)
#define RED_HIGH (1U<<6)


void Task0(void);
void Task1(void);
void GPIO_init(void);
void Red_LED(void);
void Green_LED(void);
void delay(uint32_t sec);


int main(void){
	
	OsKernelInit();
	GPIO_init();
	OsKernelAddThread(&Task0,&Task1);
	OsKernelLaunch(QUANTA);
	
	return 0;
}

void Task0(void){
	while(1){
    Green_LED();
	}
}

void Task1(void){
	while(1){
    Red_LED();
	}	
}

void GPIO_init(void){
  __disable_irq();
	RCC->AHB1ENR |= AHB1_BUS_ENABLE;       //Enable Clock for AHB1 Bus
	GPIOA->MODER |= RED_LED_PIN;
	GPIOA->MODER |= GREEN_LED_PIN;         //D13 as Output
	__enable_irq();
}

void Red_LED(void){

	GPIOA->ODR  |= RED_HIGH;               //Make D12 HIGH
	delay(1000);
	GPIOA->ODR  &= ~RED_HIGH;              //Make D12 LOW
	delay(1000);
	
}
void Green_LED(void){
	
	GPIOA->ODR  |= GREEN_HIGH;              //Make D13 HIGH
	delay(1000);
	GPIOA->ODR  &= ~GREEN_HIGH;             //Make D13 LOW
	delay(1000);
	
}

void delay(uint32_t sec){
	for(;sec>0;sec--){
		for(int i=0;i<3000;i++);
	}
}


