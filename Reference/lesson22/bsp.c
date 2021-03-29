/* Board Support Package (BSP) for the STM32F446RE board */
#include <stdint.h>  /* Standard integers. WG14/N843 C99 Standard */
#include "bsp.h"
#include "C:\Users\Balaji\Documents\GitHub\PaidRTOS\STM32F446RE\Module2\paid.h"
#include "stm32f4xx.h"                  /* Device header */

static uint32_t volatile l_tickCtr;

void SysTick_Handler(void) {
    ++l_tickCtr;
	 __disable_irq();
	 OS_sched();
	 __enable_irq();
}

void BSP_init(void) {
    /*SYSCTL->RCGCGPIO  |= (1U << 5);  //enable Run mode for GPIOF
    SYSCTL->GPIOHBCTL |= (1U << 5); //enable AHB for GPIOF 
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
		*/
	  __disable_irq();
		RCC->AHB1ENR|=1;
		GPIOA->MODER |= 0x400;
		SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);
    
	  /*
	    Set the SysTick interrupt priority (highest)
	   *Highest Priority is set for -> SysTick
	   *Lowest Priority is set for ->PendSV interrupt
	  */
	  NVIC_SetPriority(SysTick_IRQn,0U); 
	  __enable_irq();
}

uint32_t BSP_tickCtr(void) {
    uint32_t tickCtr;
    __disable_irq();
    tickCtr = l_tickCtr;
    __enable_irq();
    return tickCtr;
}

void BSP_delay(uint32_t ticks) {
    uint32_t start = BSP_tickCtr();
    while ((BSP_tickCtr() - start) < ticks) {
    }
}

void BSP_ledRedOn(void) {      /* Turns D13 PIN HIGH*/
    GPIOA->ODR |=0x20;
}

void BSP_ledRedOff(void) {     /* Turns D13 PIN LOW*/
    GPIOA->ODR &=~0x20;
}

void BSP_ledBlueOn(void) {     /* Turns D12 PIN HIGH*/
    GPIOA->ODR |=0x40;
}

void BSP_ledBlueOff(void) {    /* Turns D12 PIN LOW*/
    GPIOA->ODR &=~0x40;
}

void BSP_ledGreenOn(void) {    /* Turns D11 PIN HIGH*/
    GPIOA->ODR |=0x80;
}

void BSP_ledGreenOff(void) {   /* Turns D11 PIN LOW*/
    GPIOA->ODR &=~0x80;
}


void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}
