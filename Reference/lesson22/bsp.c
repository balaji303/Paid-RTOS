/* Board Support Package (BSP) for the EK-TM4C123GXL board */
#include <stdint.h>  /* Standard integers. WG14/N843 C99 Standard */

#include "bsp.h"
#include "stm32f4xx.h"                  // Device header


/* on-board LEDs */
#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

static uint32_t volatile l_tickCtr;

void SysTick_Handler(void) {
    ++l_tickCtr;
}

void BSP_init(void) {
    /*SYSCTL->RCGCGPIO  |= (1U << 5);  //enable Run mode for GPIOF
    SYSCTL->GPIOHBCTL |= (1U << 5); //enable AHB for GPIOF 
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
		*/
		RCC->AHB1ENR|=1;
		GPIOA->MODER |= 0x400;
		SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

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

void BSP_ledRedOn(void) {
    GPIOA->ODR |=0x20;
}

void BSP_ledRedOff(void) {
    GPIOA->ODR &=~0x20;
}

void BSP_ledBlueOn(void) {
    GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;
}

void BSP_ledBlueOff(void) {
    GPIOF_AHB->DATA_Bits[LED_BLUE] = 0U;
}

void BSP_ledGreenOn(void) {
    GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
}

void BSP_ledGreenOff(void) {
    GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
}


void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}
