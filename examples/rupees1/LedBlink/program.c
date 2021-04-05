/*
How to set a GPIO PIN as Output
1. Enable Clock access to PORT of the PIN
2. set the PIN's mode
3. Set Output's register
******************************
*/
#include "stm32f4xx.h"                    // Device header
#define GREEN_LED_PIN (1U<<10)
#define RED_LED_PIN (1U<<12)
#define AHB1_BUS_ENABLE (1U)
#define GREEN_HIGH (1U<<5)
#define RED_HIGH (1U<<6)
#define LOW (0U)

volatile uint32_t tick;
volatile uint32_t _tick;

void GPIO_init(void);
int Red_LED(void);
int Green_LED(void);
void delaysec(uint32_t sec);
void SysTick_Handler(void);
uint32_t getTick(void);

int main(void){
	uint32_t volatile control = 0U;
	GPIO_init();
	if(control){
	Red_LED();
	}
	else{
	Green_LED();
	}
	while(1){	}                             //Not to terminate the main
}

void GPIO_init(void){
  __disable_irq();
	RCC->AHB1ENR |= AHB1_BUS_ENABLE;        //Enable Clock for AHB1 Bus
	GPIOA->MODER |= RED_LED_PIN;
	GPIOA->MODER |= GREEN_LED_PIN;          //D13 as Output
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	__enable_irq();
}

int Red_LED(void){
	while(1){
	GPIOA->ODR  = RED_HIGH;               //Make D12 HIGH
	delaysec(1);
	GPIOA->ODR  = LOW;                      //Make D12 LOW
	delaysec(1);
	}
}
int Green_LED(void){
	while(1){
	GPIOA->ODR  = GREEN_HIGH;               //Make D13 HIGH
	delaysec(1);
	GPIOA->ODR  = LOW;                      //Make D13 LOW
	delaysec(1);
	}
}

void SysTick_Handler(void){
	++tick;
}

uint32_t getTick(void){
	__disable_irq();
	_tick=tick;
	__enable_irq();
	return _tick;
}

void delaysec(uint32_t sec){
	sec *=1000;
	uint32_t temp = getTick();
	while((getTick()-temp)<sec){
	}
}
/*
void delay(int sec){
	for(;sec>0;sec--){
		for(int i=0;i<3000;i++);
	}
}
*/
