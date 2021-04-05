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

uint32_t red_stack[40];
uint32_t green_stack[40];

uint32_t *sp_red = &red_stack[40];
uint32_t *sp_green = &green_stack[40];

void GPIO_init(void);
int Red_LED(void);
int Green_LED(void);
void delaysec(uint32_t sec);
void SysTick_Handler(void);
uint32_t getTick(void);

int main(void){
	GPIO_init();
/****Red LED Stack****/
	/*xPSR*/
	*(--sp_red) = (1u<<24);                 //Denotes THUMB Instruction
	/*PC*/
	*(--sp_red) = (uint32_t)&Red_LED;       //Point to the next address
	/*LR*/
	*(--sp_red) =  0xDEADBEEFU;
	/*R12*/
	*(--sp_red) =  0xDEADBEEFU;
	/*R3*/
	*(--sp_red) =  0xDEADBEEFU;  
	/*R2*/
	*(--sp_red) =  0xDEADBEEFU;
	/*R1*/
	*(--sp_red) =  0xDEADBEEFU;
	/*R0*/
	*(--sp_red) =  0xDEADBEEFU;
	
	
/****Green LED Stack****/
	/*xPSR*/
	*(--sp_green) = (1u<<24);                 //Denotes THUMB Instruction
	/*PC*/
	*(--sp_green) = (uint32_t)&Green_LED;       //Point to the next address
	/*LR*/
	*(--sp_green) =  0xDEADBEEFU;
	/*R12*/
	*(--sp_green) =  0xDEADBEEFU;
	/*R3*/
	*(--sp_green) =  0xDEADBEEFU;  
	/*R2*/
	*(--sp_green) =  0xDEADBEEFU;
	/*R1*/
	*(--sp_green) =  0xDEADBEEFU;
	/*R0*/
	*(--sp_green) =  0xDEADBEEFU;
	
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
